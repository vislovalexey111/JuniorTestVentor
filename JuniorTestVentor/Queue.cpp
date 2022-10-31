#include "Queue.h"

const uint16 Min(const uint16 a, const uint16 b)
{
	return (a < b) ? a : b;
}

Queue::Queue(uint16 iSize) : hData(NULL), Head(0), Size(iSize)
{
	// If memory size was specified - creating empty "Queue" and allocating memory of that size.
	if (Size > 0)
		hData = (uint8*)calloc(Size, sizeof(uint8));

	// The "Tail" is a variable of "uint16_t" type, so we can't set it to -1 to indicate emptiness of the queue.
	// However, we can set it equal to memory size (because in non-empty queue won't have a "Tail" index equal to "Size".
	Tail = Size;
}

Queue::~Queue(void)
{
	free(hData);
	hData = NULL;
}

uint16 Queue::Put(uint8* Data, uint16 iSize)
{
	// Returning 0 in cases if we don't have data source/destination, we didn't specified
	// size of the data transfer or we don't have enough space in the current queue.
	if (!hData || !Data || !iSize || this->GetSize() + iSize > Size)
		return 0;

	// Checking, if our queue is empty to add data correctly.
	uint16 isEmpty = (Tail == Size);
	Tail = (isEmpty) ? Head : Tail;
	Head = (Head + iSize - isEmpty) % Size;

	for (uint16 i = 0, h = Head; i < iSize; i++)
	{
		hData[h] = Data[i];
		h = (h == 0) ? (Size - 1) : (h - 1); // If we crossed the border - setting the correct index.
	}

	return iSize;
}

uint16 Queue::GetSize(void)
{
	// Returning 0 if our queue is empty.
	if (!hData || Tail == Size)
		return 0;

	// If the data crossing the boderd, returning:  (size of data berfore border) + (size of data after border).
	if (Tail > Head)
		return (Size - Tail) + (Head + 1);

	return Head - Tail + 1;
}

uint16 Queue::Get(uint8* Data, uint16 iSize)
{
	// Retrning 0, if we don't have data source/destination, size of transfer is not specified or our queue is empty.
	if (!Data || !hData || !iSize || Tail == Size)
		return 0;

	uint16 transferSize = Min(this->GetSize(), iSize);

	for (uint16 i = 0, h = Head; i < transferSize; i++)
	{
		Data[i] = hData[h];
		h = (h == 0) ? (Size - 1) : (h - 1); // If we crossed the border - setting the correct index.
	}

	return transferSize;
}

uint16 Queue::Clear(uint16 iSize)
{
	// No need to clear data from the tail if the size to clear was not specified or the queue is empty.
	if (!hData || !iSize || Tail == Size)
		return 0;

	const uint16 initialSize = this->GetSize();

	// If the data to clear is bigger or equal to our queue size - setting the queue emptiness indicator.
	if (iSize >= initialSize)
		Tail = Size;
	// If both data and clear size crossing the border - setting the "Tail" index after the border.
	else if (Tail > Head && Tail + iSize >= Size)
		Tail = (Tail + iSize) % Size;
	else
		Tail += iSize;

	// Returning difference between initial and current sizes of the queue.
	return initialSize - this->GetSize();
}