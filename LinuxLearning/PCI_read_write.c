/* 
	Rference: https://stackoverflow.com/questions/9662193/how-to-accessif-possible-kernel-space-from-user-space
	kernel parameter: iomem=relaxed
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAPPED_SIZE 	256

int main(int argc, char const *argv[])
{
	int i = 0;
	int fdmem = 0;
	int *map = NULL;	
	const char memDevice[] = "/dev/mem";

	unsigned long ulMMCFGBase = 0;
	unsigned long ulPhyAddress = 0;
	
	int iRetVal = 0;
	unsigned int uiBus = 0;
	unsigned int uiDev = 0;
	unsigned int uiFun = 0;

	unsigned int uiRW = 0;	
	unsigned int uiOffset = 0;
	unsigned int uiData = 0;

	/* get input from user */
	if(argc < 3)
	{
		printf("usage:%s [MMCONFIG Base HEX] [PCI Device [bb:dd.f] HEX] \n", argv[0]);
		return 0;
	}

	/* extract inputs */
	iRetVal = sscanf(argv[1], "%x", &ulMMCFGBase);
	if(iRetVal != 1)
	{
		printf("error: invalid MMCONFIG base address\n");
		return 0;
	}
	printf("MMCONFIG base: 0x%x\n", ulMMCFGBase);
	
	iRetVal = sscanf(argv[2], "%x:%x.%x", &uiBus, &uiDev, &uiFun);
	if(iRetVal != 3)
	{
		printf("error: invalid PCI device\n");
		return 0;
	}
	printf("PCI Device: %02x:%02x:%x\n", uiBus, uiDev, uiFun);
	
	/* compute the physical address */
	ulPhyAddress |= (ulMMCFGBase | (uiBus << 20) | (uiDev << 15) | (uiFun << 12));
	printf("Physical Address: 0x%08x\n", ulPhyAddress);

	/* open /dev/mem and error checking */
	fdmem = open( memDevice, O_RDWR | O_SYNC );

	if (fdmem < 0){
		printf("Failed to open the /dev/mem !\n");
		perror("open");
		return 0;
	}
	else{
		printf("open /dev/mem successfully !\n");
	}

	/* mmap() the opened /dev/mem */
	map = (int *)(mmap(0, MAPPED_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fdmem, ulPhyAddress));
	if(map == MAP_FAILED)
	{
		perror("mmap");
		return 0;
	}

	do{

		printf("1. Read\n2. Write\n: ");
		scanf("%d", &uiRW);

		printf("Dword Offset: ");
		scanf("%x", &uiOffset);

		if(uiRW == 1)
		{
			uiData = map[uiOffset];
			printf("Data: 0x%08x\n", uiData);
		}
		else
		{
			printf("Data: ");
			scanf("%x", &uiData);
			map[uiOffset] = uiData;
		}
		
	}while(1);

	/* unmap the area & error checking */
	if (munmap(map,MAPPED_SIZE)==-1){
		perror("Error un-mmapping the file");
	}

	/* close the character device */
	close(fdmem);

	return 0;
}
