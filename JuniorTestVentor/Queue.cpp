#include "Queue.h"

const uint16 Min(const uint16 a, const uint16 b)
{
	return (a < b) ? a : b;
}

Queue::Queue(uint16 iSize) : hData(NULL), Head(0), Tail(0), Size(0)
{
	// If specified size is bigger than 0 - creating empty queue and allocating memory of
	// iSize + 1 bytes, so we can control data overflow.
	if (iSize > 0)
	{
		hData = (uint8*)calloc(++iSize, sizeof(uint8));
		if (hData) Size = iSize;
	}
}

Queue::~Queue(void)
{
	if (hData)
	{
		free(hData);
		hData = NULL;
	}
}

uint16 Queue::Put(uint8* Data, uint16 iSize)
{
	// Returning 0 in case we don't have: data source/destination, data to put or engough space in our queue.
	// Adding 1 to required space - 1 byte of control memory overflow.
	if (!hData || !Data || !iSize || this->GetSize() + iSize + 1 > Size)
		return 0;
	
	uint16 transferSize = Min(iSize, Size - (Tail + 1));

	// Transfering data, that we can put before buffer boundary.
	memmove(&hData[(Tail + this->GetSize() + 1) % Size], Data, transferSize);
	Head = (Head + iSize) % Size;

	// Transfering data to the queue after buffer boundary (if we didn't transfer all tha data)
	if (transferSize != iSize)
		memmove(hData, Data + transferSize, iSize - transferSize);

	return iSize;
}

uint16 Queue::GetSize(void)
{
	// Returning 0 if our queue is empty.
	if (!hData || Tail == Head) return 0;

	// Returning (data before boundary) + (data after boundary).
	if (Tail > Head) return (Size - Tail) + Head;

	return Head - Tail;
}

uint16 Queue::Get(uint8* Data, uint16 iSize)
{
	// Returning 0 if we don't have data source/destination or we have have nothing to copy.
	if (!Data || !hData || !iSize || Tail == Head)
		return 0;

	uint16 transferSize = Min(this->GetSize(), iSize); 
	uint16 bufferScopedSize = Min(transferSize, Size - (Tail + 1));
	
	// Getting all data before buffer boundary.
	memmove(Data, &hData[(Tail + 1) % Size], bufferScopedSize);

	// Getting data after buffer boundary (if we didn't get all the data)
	if (bufferScopedSize != transferSize)
		memmove(Data + bufferScopedSize, hData, transferSize - bufferScopedSize);

	return transferSize;
}

uint16 Queue::Clear(uint16 iSize)
{
	// Returning 0 if we don't have data source, the queue is empty or the clear size is 0.
	if (!hData || !iSize || Tail == Head)
		return 0;

	const uint16 notClearedSize = this->GetSize();

	if (iSize >= notClearedSize) Tail = Head; // Setting queue emptyness indicator, if we cleared everything.
	else Tail = (Tail + iSize) % Size;

	// returning difference between queue data before and after.
	return notClearedSize - this->GetSize();
}