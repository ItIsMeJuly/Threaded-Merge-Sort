#ifndef RUNTIME_ERROR_H
#define RUNTIME_ERROR_H

#include <stdexcept>

class ProgrammingError : public std::runtime_error
{
public:
    ProgrammingError(const char* what_arg)
        : std::runtime_error(what_arg)
    {
    }
    const char* what() const noexcept override
    {
        return std::runtime_error::what();
    }
};

#endif
