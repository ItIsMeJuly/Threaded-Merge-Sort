#ifndef VALUE_H
#define VALUE_H

#include <string>

class Value
{
public:
    Value(const std::string& word);
    // post: Value is properly initialised with word as value
    virtual ~Value();
    // empty virtual destructor

    Value(const Value&) = delete;
    Value& operator=(const Value&) = delete;

    const std::string& GetText() const;
    // post: current value is returned

    void SetText(const std::string& value);
    // post: value is updated with new value

    Value* GetNext();
    // post: pointer to next value is returned

    void SetNext(Value* value);
    // post: pointer to next value is set

private:
    std::string word;
    Value* next;
};

#endif
