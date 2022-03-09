#include <errno.h>
#include <fcntl.h> 
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

#define BUFFER_SIZE 256


int set_interface_attribs (int fd, int speed, int parity)
{
    struct termios tty;
    memset (&tty, 0, sizeof tty);
    if (tcgetattr (fd, &tty) != 0)
    {
        printf ("error %d from tcgetattr\n", errno);
        return -1;
    }

    cfsetospeed (&tty, speed);
    cfsetispeed (&tty, speed);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
    // disable IGNBRK for mismatched speed tests; otherwise receive break
    // as \000 chars
    tty.c_iflag &= ~IGNBRK;         // disable break processing
    tty.c_lflag = 0;                // no signaling chars, no echo,
                                    // no canonical processing
    tty.c_oflag = 0;                // no remapping, no delays
    tty.c_cc[VMIN]  = 0;            // read doesn't block
    tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

    tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                    // enable reading
    tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
    tty.c_cflag |= parity;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr (fd, TCSANOW, &tty) != 0)
    {
            printf ("error %d from tcsetattr\n", errno);
            return -1;
    }
    return 0;
}

void set_blocking (int fd, int should_block)
{
    struct termios tty;
    memset (&tty, 0, sizeof tty);
    if (tcgetattr (fd, &tty) != 0)
    {
        printf ("error %d from tggetattr\n", errno);
        return;
    }

    tty.c_cc[VMIN]  = should_block ? 1 : 0;
    tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

    if (tcsetattr (fd, TCSANOW, &tty) != 0)
            printf ("error %d setting term attributes\n", errno);
}

int init_serial_port(char *portname)
{
    int fd = open (portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0)
    {
        printf ("error %d opening %s: %s\n", errno, portname, strerror (errno));
        return -1;
    }
    // set speed to 115,200 bps, 8n1 (no parity)
    set_interface_attribs (fd, B115200, 0);
    // set non blocking
    set_blocking (fd, 0);

    return fd;
}

void run_terminal(int fd)
{
    char buf[BUFFER_SIZE] = {0};

    while (1)
    {
        // read data from terminal if available
        int n = read (fd, buf, sizeof(buf));
        if(n > 0)
        {
            printf ("%s", buf);
            continue; // keep reading while there is data
        }
        
        // memset buffer
        memset(buf, 0, sizeof(buf));

        // get data from user
        fgets(buf, sizeof(buf), stdin);
        // send the data
        write(fd, buf, strlen(buf));

        // memset buffer
        memset(buf, 0, sizeof(buf));
    }
}

void send_command(int fd, char *cmd)
{
    char buf[BUFFER_SIZE] = {0};

    while (1)
    {
        // read and discard any data from terminal
        int n = read (fd, buf, sizeof(buf));
        if(n > 0)
        {
            continue;
        }
        
        // memset buffer
        memset(buf, 0, sizeof(buf));
        break;
    }
    // send the command
    write(fd, cmd, strlen(cmd));
}

int main(int argc, char const *argv[])
{
    if(argc < 2)
    {
        printf("usage: %s <serial port>\n", argv[0]);
        return 0;
    }

    int fd = init_serial_port((char*)argv[1]);
    if(fd < 0)
    {
        printf ("error: init_serial_port failed!\n");
    }
    else
    {
        #if 1
            run_terminal(fd);
        #else
            while(1)
            {
                usleep(500 * 1000);
                send_command(1, "zdo leave 0xEDC7 0X00 0X00");
            }
        #endif
    }

    return 0;
}