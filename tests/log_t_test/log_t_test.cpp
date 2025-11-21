#include "../../core/log.h"
#include<string>
int main()
{
    log_t testlog;
    testlog.init();
    for (int i = 0; i < 8; i++)
    {
       testlog.log("Cant Sleep Clown WIll Eat Me");
    }
    
}