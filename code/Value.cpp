#include "Value.h"

Value::Value(const std::string& word)
    : word(word)
    , next(nullptr)
{
}

Value::~Value()
{
}

const std::string& Value::GetText() const
{
    return word;
}

void Value::SetText(const std::string& value)
{
    word = value;
}

Value* Value::GetNext()
{
    return next;
}

void Value::SetNext(Value* value)
{
    next = value;
}
