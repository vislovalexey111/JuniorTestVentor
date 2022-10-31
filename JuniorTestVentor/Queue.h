#ifndef _QUEUE_H
#define _QUEUE_H

#include <cstdint>
#include <cstdlib>
#include <cstdio>

#define uint8 uint8_t
#define uint16 uint16_t

class Queue
{
private:
	uint16 Head;
	uint16 Tail;
	uint16 Size;
	uint8* hData;
public:
	Queue(uint16 iSize);
	~Queue(void);

	uint16 Put(uint8* Data, uint16 iSize);
	uint16 GetSize(void);
	uint16 Get(uint8* Data, uint16 iSize);
	uint16 Clear(uint16 iSize);
};

#endif // _QUEUE_H