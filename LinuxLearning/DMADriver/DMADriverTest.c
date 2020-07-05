#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

#define BUFFER_SIZE 		256
#define DEV_FILE			"/dev/SimpleDMA"

char buffer[BUFFER_SIZE] = {0};

int main(int argc, char const *argv[])
{
	int fd = 0;
	int ret = 0;

	printf("opening %s... ", DEV_FILE);
	fd = open(DEV_FILE, O_RDWR);
	if(fd < 0)
	{
		printf("Failed\n");
		perror("open");
		return errno;
	}
	printf("OK\n");

	printf("Enter a string to send to device: ");
	scanf("%[^\n]%*c", buffer);
	// sprintf(buffer, "Test");
	printf("Writing to device: %s\n", buffer);

	ret = write(fd, buffer, strlen(buffer));
	if(ret < 0)
	{
		perror("write Failed");
		return errno;
	}

	memset(buffer, 0, sizeof(buffer));
	printf("Press ENTER to read back from device");
	getchar();

	printf("Reading from device...\n");
	ret = read(fd, buffer, sizeof(buffer));
	if(ret < 0)
	{
		perror("read Failed");
		return errno;
	}

	printf("Read: %s\n", buffer);

	return 0;
}
