#include "Driver_k.h"
#include "DMA_Fun.h"

struct dma_chan *g_DMACH[MAX_DMA_CHANNELS] = {0}; 

int DMA_Init(void)
{
	int error = 0;
	int iCHNo = 0;

	// only 3 out of 4 DMA channels are accessable through dma_find_channel
	for(iCHNo = 0; iCHNo < MAX_DMA_CHANNELS; iCHNo++)
	{
		dmaengine_get();

		// find DMA Channel
		switch(iCHNo)
		{
			case 0:
				g_DMACH[iCHNo] = dma_find_channel(DMA_MEMCPY);
			break;

			case 1:
				g_DMACH[iCHNo] = dma_find_channel(DMA_ASYNC_TX);
			break;

			case 2:
				g_DMACH[iCHNo] = dma_find_channel(DMA_INTERRUPT);
			break;
		}

		printk("DMA %d channal address: %#x\n", iCHNo, (unsigned long)g_DMACH[iCHNo]);
		if(g_DMACH[iCHNo] != NULL)
		{
			#if 1
				printk(KERN_INFO "DMA Device: %X\n", g_DMACH[iCHNo]->device);
				printk(KERN_INFO "DMA cookie: %X\n", g_DMACH[iCHNo]->cookie);
				printk(KERN_INFO "DMA Channel ID: %X\n", g_DMACH[iCHNo]->chan_id);
				printk(KERN_INFO "DMA client count: %X\n", g_DMACH[iCHNo]->client_count);
				printk(KERN_INFO "DMA Table count: %X\n", g_DMACH[iCHNo]->table_count);

			#endif
		}
		else
		{
			printk(KERN_ALERT "dma_request_channel Failed for %d channel\n", iCHNo);
			return DMA_FAILURE;
		}
	}

	return 0;
}

int DMA_Init_1(void)
{
	
}
