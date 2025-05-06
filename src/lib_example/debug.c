#include <nds.h>
#include <malloc.h>
#include <unistd.h>

#define SYM_PUBLIC __attribute__((visibility ("default")))

extern u8 *fake_heap_end;   // current heap start 
extern u8 *fake_heap_start;   // current heap end 

u8* getHeapStart()
{ 
   return fake_heap_start; 
}

u8* getHeapEnd()
{ 
   return (u8*)sbrk(0); 
}

u8* getHeapLimit()
{ 
   return fake_heap_end; 
}

// returns the amount of used memory in bytes 
SYM_PUBLIC int getMemUsed()
{
   struct mallinfo mi = mallinfo(); 
   return mi.uordblks; 
}

// returns the amount of free memory in bytes 
SYM_PUBLIC int getMemFree()
{
   struct mallinfo mi = mallinfo(); 
   return mi.fordblks + (getHeapLimit() - getHeapEnd()); 
}