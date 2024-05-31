#include "../isa.h"

ISA_LOG_REGISTER(IsaTest);

int
main(void)
{
    IsaLogInfo("Hello module!");
    IsaLogInfoNoModule("Hello no module!");
    IsaAssert((0 == 1) ? 0 : 0);

    return 0;
}
