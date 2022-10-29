#include "Queue.h"

const uint16 Min(const uint16 a, const uint16 b)
{
	return (a < b) ? a : b;
}

Queue::Queue(uint16 iSize) : hData(NULL), Head(0), Size(iSize)
{
	// We are making empty queue with allocated memory of "Size", not the queue with data, that have the size = "Size"
	// In this case "Size" is just a maximum amount of data that we can pass to the queue. Because the Tail is unsigned int,
	// it is better to make Tail index equal to initial Size, so we can understand that queue data is empty. 
	if(Size > 0) 
		hData = (uint8*)calloc(Size, sizeof(uint8));

	// In case of memory allocation error, we setting the size to 0
	Size = (!hData && Size > 0) ? 0 : Size;
	Tail = Size;
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
	// If we do not have enugh space to put all the data - we do not put the data at all. 
	if (!hData || !Data || !iSize || this->GetSize() + iSize > Size)
		return 0;

	uint16 remainingData = iSize - Head - (Tail == Size);
	Tail = (Tail == Size) ? Head : Tail;

	if (Tail < Head || Head >= iSize) 
	{
		Head -= iSize;
		memcpy(&hData[Head], Data, iSize);
	}
	else 
	{
		memcpy(hData, Data + remainingData, iSize - remainingData);
		Head = Size - remainingData;
		memcpy(&hData[Head], Data, remainingData);
	}

	return iSize;
}

uint16 Queue::GetSize(void)
{
	if (!hData || Tail == Size)
		return 0;

	return ((Tail < Head) ? (Size - Head + Tail) : (Tail - Head)) + 1;
}

uint16 Queue::Get(uint8* Data, uint16 iSize)
{
	if (!Data || !hData || !iSize || Tail == Size)
		return 0;
	
	uint16 transferSize = 0;

	if (Tail < Head) {
		transferSize = Min(iSize, Size - Head);
		
		if (transferSize < iSize)
		{
			uint16 remainingSize = Min(iSize - transferSize, Tail + 1);
			memcpy(Data + transferSize, hData, remainingSize);
		}
	}
	else
		transferSize = Min(this->GetSize(), iSize);

	memcpy(Data, &hData[Head], transferSize);
	return Min(this->GetSize(), iSize);
}

uint16 Queue::Clear(uint16 iSize)
{
	if (!hData || !iSize|| Tail == Size)
		return 0;
	
	const uint16 initialSize = this->GetSize();

	if (iSize >= initialSize)
		Tail = Size;
	else if (Tail < Head)
		Tail = (iSize > Tail) ? ((Size + Tail) - iSize) : (Tail - iSize);
	else
		Tail -= iSize;

	return initialSize - this->GetSize();
}