#include "../isa.h"

ISA_LOG_REGISTER(IsaTest);

int
main(void)
{
    IsaLogInfo("Hello, logging!");
    IsaAssert(0, "Need to figure out how to use this without any args!");
    // IsaAssert(0);
    return 0;
}
