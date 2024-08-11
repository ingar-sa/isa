#include "../isa.h"

int
main(void)
{
    do
    {
        if((4 >= (3U) ? 1 : 0))
        {
            i64 Ret = Isa__WriteLogNoModule__("INF", __func__, "Hello");
            if(Ret)
            {
                printf("%s", "\n\nERROR WHILE LOGGING\n\n");
                (void)((!!(0)) || (_wassert(L"0", L".\\test_isa.c", (unsigned)(8)), 0));
            }
        }
    } while(0);
    do
    {
        if(!(0))
        {
            if(1 > 0)
            {
                do
                {
                    if((4 >= (1U) ? 1 : 0))
                    {
                        i64 Ret = Isa__WriteLogNoModule__("ERR", __func__,
                                                          "Need to figure out how to use this without any args!");
                        if(Ret)
                        {
                            printf("%s", "\n\nERROR WHILE LOGGING\n\n");
                            (void)((!!(0)) || (_wassert(L"0", L".\\test_isa.c", (unsigned)(9)), 0));
                        }
                    }
                } while(0);
            }
            (void)((!!(0)) || (_wassert(L"0", L".\\test_isa.c", (unsigned)(9)), 0));
        }
    } while(0);
    do
    {
        if(!(0))
        {
            if(1 > 0)
            {
                do
                {
                    if((4 >= (1U) ? 1 : 0))
                    {
                        i64 Ret = Isa__WriteLogNoModule__("ERR", __func__);
                        if(Ret)
                        {
                            printf("%s", "\n\nERROR WHILE LOGGING\n\n");
                            (void)((!!(0)) || (_wassert(L"0", L".\\test_isa.c", (unsigned)(10)), 0));
                        }
                    }
                } while(0);
            }
            (void)((!!(0)) || (_wassert(L"0", L".\\test_isa.c", (unsigned)(10)), 0));
        }
    } while(0);
    return 0;
}
