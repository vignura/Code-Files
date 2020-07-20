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

#define MAPPED_SIZE 	64
// #define DDR_RAM_PHYS  	0xb3400000
#define DDR_RAM_PHYS  	0xb4405c00


int main(int argc, char const *argv[])
{
	int i = 0;
	int fdmem = 0;
	int *map = NULL;
	const char memDevice[] = "/dev/mem";
	unsigned long ulPhyAddress = 0;
	unsigned long ulMapSize = 0;
	unsigned long ulReadsize = 0;

	/* get the physical address */
	if(argc < 4)
	{
		printf("usage:%s [base address HEX] [bytes to map] [bytes to display]\n", argv[0]);
		return 0;
	}

	sscanf(argv[1], "%x", &ulPhyAddress);
	printf("base address: 0x%x\n", ulPhyAddress);
	sscanf(argv[2], "%d", &ulMapSize);
	printf("Map Size: %d\n", ulMapSize);
	sscanf(argv[3], "%d", &ulReadsize);
	printf("Read Size: %d\n", ulReadsize);

	if(ulReadsize > ulMapSize)
	{
		printf("Read size should be less than or equal to Map size\n");
		return 0;
	}

	/* open /dev/mem and error checking */
	fdmem = open( memDevice, O_RDWR | O_SYNC );

	if (fdmem < 0){
		printf("Failed to open the /dev/mem !\n");
		return 0;
	}
	else{
		printf("open /dev/mem successfully !\n");
	}

	/* mmap() the opened /dev/mem */
	map = (int *)(mmap(0, ulMapSize, PROT_READ|PROT_WRITE, MAP_SHARED, fdmem, ulPhyAddress));
	if(map == MAP_FAILED)
	{
		perror("mmap");
		return 0;
	}

	/* use 'map' pointer to access the mapped area! */
	for (i = 0; i < (ulReadsize / sizeof(int)); i++){
		printf("[%04x]: 0x%08x\n", ((i +1) * sizeof(int)), map[i]);
	}

	/* unmap the area & error checking */
	if (munmap(map,MAPPED_SIZE)==-1){
		perror("Error un-mmapping the file");
	}

	/* close the character device */
	close(fdmem);

	return 0;
}
