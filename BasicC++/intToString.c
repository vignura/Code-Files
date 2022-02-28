#include <stdio.h>
#include <stdint.h>

static void intToString(uint32_t number, char *string, uint32_t length)
{
	printf("length: %d\n", length);
    if(string != NULL && length > 0)
    {
        uint32_t index = 0;

        // extract the digits
        while(number > 0 && index < length)
        {            
            string[index] = (number % 10) + '0';
            number = number / 10;
            index++;
        }

        // reverse the string
        for (uint32_t i = 0; i < index / 2; i++)
        {
            char temp = 0;
            temp = string[i];
            string[i] = string[index -1 -i];
            string[index -1 -i] = temp;
        }

        // terminate with null
        string[index] = '\0';
    }
}

int main(int argc, char const *argv[])
{
	char msg[128] = {0};
	intToString(1001123, msg, sizeof(msg));
	printf("number: %s\n", msg);
	return 0;
}