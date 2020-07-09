/* 
	Rference: https://stackoverflow.com/questions/9662193/how-to-accessif-possible-kernel-space-from-user-space
	kernel parameter: iomem=relaxed
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>

#define MAPPED_SIZE 	64
#define DDR_RAM_PHYS  	0xdfbf0000

int main()
{
	int i = 0;
	int fdmem = 0;
	int *map = NULL;
	const char memDevice[] = "/dev/mem";

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
	map= (int *)(mmap(0, MAPPED_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fdmem, DDR_RAM_PHYS));

	/* use 'map' pointer to access the mapped area! */
	for (i = 0; i < 16; i++){
		printf("content: 0x%x\n", *(map+i));
	}

	/* unmap the area & error checking */
	if (munmap(map,MAPPED_SIZE)==-1){
		perror("Error un-mmapping the file");
	}

	/* close the character device */
	close(fdmem);

	return 0;
}
