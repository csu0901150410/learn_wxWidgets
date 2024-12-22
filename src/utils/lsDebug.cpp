#include <iostream>
#include <cstdarg>
#include <cstdio>

#include <windows.h>

#include "lsDebug.h"

// 匿名namespace，仅当前文件可见，类似C的static具有文件级作用域
namespace
{
    FILE *static_g_logTarget = nullptr;
}

lsDebug::lsGaobo lsDebug::garbo;

lsDebug::lsDebug()
{
}

lsDebug::~lsDebug()
{
    try
    {
        if (nullptr != static_g_logTarget)
        {
            if (stderr != static_g_logTarget
                && stdout != static_g_logTarget)
                fclose(static_g_logTarget);// 定向到了文件，需要关闭
        }
    }
    catch(...)
    {
        std::cerr << "lsDebug::" << __func__ << ":: Failed to close stream!";
    }
}

lsDebug *lsDebug::instance()
{
    static lsDebug *uniqueInstance = nullptr;
    if (nullptr == uniqueInstance)
    {
        uniqueInstance = new lsDebug;
        static_g_logTarget = stdout;
    }
    return uniqueInstance;
}

/**
 * 输出日志到stdout
 */
void lsDebug::print(const char *format...)
{
    va_list ap;
    va_start(ap, format);
    vfprintf(static_g_logTarget, format, ap);
    fprintf(static_g_logTarget, "\n");

    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, ap);
    printf(buffer, "\n");

    va_end(ap);
    fflush(static_g_logTarget);

    OutputDebugStringA(buffer);
}
