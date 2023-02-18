#include "Log.h"
#include "ProgrammingError.h"

#include <cstring>

// Disabling both of these bools will result in Klocwork errors
// (disabled file ptr is not initialised in constructor: this is not a problem because it
//  is also never used.)
static const bool DebugEnabled = true;
static const bool TraceEnabled = true;

Log::Log()
{
    if (DebugEnabled || TraceEnabled)
    {
        logfile = fopen("log.txt", "w");
        if (logfile == nullptr)
        {
            throw ProgrammingError("could not open log.txt");
        }
    }
}

Log::~Log()
{
    if (DebugEnabled || TraceEnabled)
    {
        fclose(logfile);
        logfile = NULL;
    }
}

void Log::Debug(const char* fmt, ...)
{
    if (DebugEnabled)
    {
        va_list args;
        va_start(args, fmt);
        Write("DEBUG", fmt, args);
        va_end(args);
    }
}

void Log::Trace(const char* fmt, ...)
{
    if (TraceEnabled)
    {
        va_list args;
        va_start(args, fmt);
        Write("TRACE", fmt, args);
        va_end(args);
    }
}

void Log::Write(const char* type, const char* fmt, va_list ap)
{
    const size_t MaxLength = 1000;
    char message[MaxLength];

    size_t typelen = strlen(type);
    size_t msglen = sprintf(message, "%s ", type);
    msglen += vsnprintf(message + typelen + 1, MaxLength, fmt, ap);
    
/* ------------------------------------------------- */
/* --- This part of the code may not be changed! --- */
/* ------------------------------------------------- */
/* - */  for (size_t i = 0; i < msglen; i++)    /* - */
/* - */  {                                      /* - */
/* - */      fprintf(logfile, "%c", message[i]);/* - */
/* - */  }                                      /* - */
/* - */  fprintf(logfile, "\n");                /* - */
/* ------------------------------------------------- */
}
