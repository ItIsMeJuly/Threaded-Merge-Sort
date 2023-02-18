#ifndef LOG_H
#define LOG_H

#include <cstdarg>
#include <cstdio>

class Log
{
public:
    Log();
    ~Log();
    Log(Log const&) = delete;
    Log& operator=(Log const&) = delete;

    virtual void Debug(const char* fmt, ...);
    virtual void Trace(const char* fmt, ...);

private:
    FILE* logfile;
    void Write(const char* type, const char* fmt, va_list ap);
};

#endif
