#include "config.h"

void cpu_halt(void)
{
  asm("halt");
}