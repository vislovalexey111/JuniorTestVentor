#include "Queue.h"

const uint16 Min(const uint16 a, const uint16 b)
{
	return (a < b) ? a : b;
}

Queue::Queue(uint16 iSize) : hData(NULL), Head(0), Tail(iSize), Size(iSize)
{
	// We are making empty queue with allocated memory of "Size", not the queue with data, that have the size = "Size"
	// In this case "Size" is just a maximum amount of data that we can pass to the queue. Because the Tail is unsigned int,
	// it is better to make it point to index AFTER last element and refer to last element as array[Tail - 1].
	if(Size > 0) 
		hData = (uint8*)calloc(Size, sizeof(uint8));

	// In case of memory allocation error, we setting the size to 0
	if (!hData)
		Size = 0;
}

Queue::~Queue(void)
{
	if (!hData)
		return;

	free(hData);
	hData = NULL;
}

uint16 Queue::Put(uint8* Data, uint16 iSize)
{
	uint16 actualSize = (Tail < Head) ? (Size - Head + Tail + 2) : (Tail - Head);
	// If we do not have enugh space to put all the data - we do not put the data at all. 
	if (!hData || !Data || (actualSize > Size && Tail != Size))
		return 0;
	


	



	
	
	memcpy(hData + iSize, hData, Tail);
	Tail += iSize;

	memcpy(hData, Data, actualSize);
	
	return actualSize;
}

uint16 Queue::GetSize(void)
{
	if (!hData || Tail == Size)
		return 0;

	return Tail;
}

uint16 Queue::Get(uint8* Data, uint16 iSize)
{
	if (!Data || !hData || !iSize || Tail == Size)
		return 0;

	uint16 actualSize = 1;
	uint16 remainingData = 0;

	if (Tail < Head) {
		actualSize += iSize - Head;
		if (Head + iSize > Size)
		{
			remainingData = Min((Head + iSize) % Size, Tail + 1);
			memcpy(Data + actualSize, &hData, remainingData);
		}
	}
	else
		actualSize += Tail - Head;

	memcpy(Data, &hData[Head], actualSize);
	actualSize += remainingData;

	return actualSize;
}

uint16 Queue::Clear(uint16 iSize)
{
	if (!hData || !iSize|| Tail == Size)
		return 0;
	
	uint16 actualSize = 1;
	

	return actualSize;
}