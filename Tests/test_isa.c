#include "isa.h"

#include <stdio.h>
ISA_LOG_REGISTER(IsaTest);

int
main(void)
{
    IsaLogInfo("Hello, logging!");
    return 0;
}
