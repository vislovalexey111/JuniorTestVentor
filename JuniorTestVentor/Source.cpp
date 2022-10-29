#include "Queue.h"

void PrintArray(const char* dataArrayName, const uint8* dataArray, const uint16 dataArraySize);
void FillArrayWithNumbers(uint8* dataArray, const uint16 dataArraySize, const int step);

// Testing implemented Queue data structure
int main()
{
	const uint16 queueSize = 8;
	Queue queue(8);
	uint16 smallDataSize = queueSize / 2;
	uint8* smallData = (uint8*)calloc(smallDataSize, sizeof(uint8));

	if (!smallData)
		return 0;

	uint16 bigDataSize = queueSize * 3;
	uint8* bigData = (uint8*)calloc(bigDataSize, sizeof(uint8));
	
	if (!bigData)
		return 0;
	
	FillArrayWithNumbers(smallData, smallDataSize, 1);
	FillArrayWithNumbers(bigData, bigDataSize, 3);

	// Trying to put big amount of data.
	printf("Data bytes transfered from big array: %hu\n", queue.Put(bigData, bigDataSize));
	printf("Queue size is %hu after trying to put %hu elements\n", queue.GetSize(), bigDataSize);

	// Putting small amount of data
	printf("\nData bytes transfered from small array: %hu\n", queue.Put(smallData, smallDataSize));
	printf("Queue size is %hu after trying to put %hu elements\n", queue.GetSize(), smallDataSize);

	// Transfering data frome queue to Big data array and printing results
	printf("\nTransfered bytes from queue to big data array: %hhu\n", queue.Get(bigData, bigDataSize));
	PrintArray("Big array", bigData, bigDataSize);

	// Transfering data frome queue to Small data array and printing results
	printf("\nTransfered bytes from queue to small data array: %hhu\n", queue.Get(smallData, smallDataSize));
	PrintArray("Small array", smallData, smallDataSize);
	printf("\n");

	// Clearing last 2 elements from the queue
	queue.Clear(2);
	printf("Queue size is %hu after clearing 2 elements\n", queue.GetSize());

	// Putting new "smallData" elements to the head of the queue
	queue.Put(smallData, smallDataSize);
	printf("Queue size is %hu after trying to put %hu elements\n", queue.GetSize(), smallDataSize);

	queue.Clear(2);
	printf("Queue size is %hu after clearing 2 elements\n", queue.GetSize());

	queue.Put(smallData, smallDataSize);
	printf("Queue size is %hu after trying to put %hu elements\n", queue.GetSize(), smallDataSize);

	queue.Clear(2);
	printf("Queue size is %hu after clearing 2 elements\n", queue.GetSize());

	queue.Clear(3);
	printf("Queue size is %hu after clearing 3 elements\n", queue.GetSize());

	// Releasing memory we no longer need
	free(bigData);
	free(smallData);
	bigData = NULL;
	smallData = NULL;

	getchar();
	return 0;
}	

void PrintArray(const char* dataArrayName, const uint8* dataArray, const uint16 dataArraySize)
{
	if (!dataArray || !dataArrayName)
		return;

	printf("%s data: ", dataArrayName);

	for (int i = 0; i < dataArraySize; i++)
		printf("%hhu ", dataArray[i]);
	printf("\n");
}

void FillArrayWithNumbers(uint8* dataArray, const uint16 dataArraySize, const int step)
{
	if (!dataArray)
		return;

	for (int i = 0; i < dataArraySize; i++)
		dataArray[i] = (i + 1) * step;
}