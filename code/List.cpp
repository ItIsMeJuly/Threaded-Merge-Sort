#include "List.h"
#include <thread>

#define SAFE_VALUE_TEXT(ptr) \
    ptr == nullptr ? "nullptr" : ptr->GetText().c_str()

unsigned int threadCount = 0;

List::List(Log& log)
    : head(nullptr)
    , log(log)
{
}

List::~List()
{
    while (head != nullptr)
    {
        Value* temp = head;
        head = head->GetNext();
        delete temp;
        temp = nullptr;
    }
}

void List::Add(const std::string& word)
{
    // log.Trace("%s << word = \"%s\"", __FUNCTION__, word.c_str());

    Value* temp = new Value(word);
    temp->SetNext(head);
    head = temp;

    // log.Trace("%s >>", __FUNCTION__);
}

Value* List::GetHead()
{
    // log.Trace("%s >> head = \"%s\"", __FUNCTION__, SAFE_VALUE_TEXT(head));
    return head;
}

void List::SetHead(Value* value)
{
    // log.Trace("%s >> head = \"%s\"", __FUNCTION__, SAFE_VALUE_TEXT(value));
    head = value;
}

void List::Sort()
{
    log.Trace("%s << head = \"%s\"", __FUNCTION__, SAFE_VALUE_TEXT(head));
    head = SortList(head);
    log.Trace("%s >> head = \"%s\"", __FUNCTION__, SAFE_VALUE_TEXT(head));
}

Value* List::SortList(Value* currentHead)
{
    log.Trace("%s << currentHead = \"%s\"", __FUNCTION__, SAFE_VALUE_TEXT(currentHead));

    Value* left = nullptr;
    Value* right = nullptr;

    if ((currentHead == nullptr) || (currentHead->GetNext() == nullptr))
    {
        // done
        log.Trace("%s >> currentHead = \"%s\"", __FUNCTION__, SAFE_VALUE_TEXT(currentHead));
        return currentHead;
    }

    // split task in 2 halves
    SplitList(currentHead, &left, &right);

    if(threadCount < 5000)
    {
        std::thread leftThread([&]
                               {
        log.Debug("%s -- sort left part, left = \"%s\"", __FUNCTION__, SAFE_VALUE_TEXT(left));
        left = SortList(left);
        threadCount++; });
        
        std::thread rightThread([&]
                                {
        log.Debug("%s -- sort right part, right = \"%s\"", __FUNCTION__, SAFE_VALUE_TEXT(right));
        right = SortList(right);
        threadCount++; });

        leftThread.join();
        rightThread.join();
    }
    else
    {
        log.Debug("%s -- sort left part, left = \"%s\"", __FUNCTION__, SAFE_VALUE_TEXT(left));
        left = SortList(left);
        
        log.Debug("%s -- sort right part, right = \"%s\"", __FUNCTION__, SAFE_VALUE_TEXT(right));
        right = SortList(right);
    }

    // merge the sorted lists
    Value* newHead = MergeLists(left, right);

    log.Trace("%s >> newHead = \"%s\"", __FUNCTION__, SAFE_VALUE_TEXT(newHead));
    return newHead;
}

void List::SplitList(Value* head, Value** left, Value** right)
{
    log.Trace("%s << head = \"%s\"", __FUNCTION__, SAFE_VALUE_TEXT(head));
    if ((head == nullptr) || (head->GetNext() == nullptr))
    {
        // done
        *left = head;
        *right = nullptr;
    }
    else
    {
        Value* slow = head;           // slow advances 1 node per cycle
        Value* fast = head->GetNext();// fast advances 2 nodes per cycle
        while (fast != nullptr)
        {
            fast = fast->GetNext();
            if (fast != nullptr)
            {
                slow = slow->GetNext();
                fast = fast->GetNext();
            }
        }

        // slow is now just before mid of the list
        *left = head;
        *right = slow->GetNext();
        slow->SetNext(nullptr);
    }

    log.Trace("%s >> *left = \"%s\", *right = \"%s\"", __FUNCTION__, SAFE_VALUE_TEXT((*left)), SAFE_VALUE_TEXT((*right)));
}

Value* List::MergeLists(Value* left, Value* right)
{
    log.Trace("%s << left = \"%s\", right = \"%s\"", __FUNCTION__, SAFE_VALUE_TEXT(left), SAFE_VALUE_TEXT(right));

    Value* head = left;
    if (right != nullptr)
    {
        if (left == nullptr)// left list is empty
        {
            log.Trace("%s >> right = \"%s\"", __FUNCTION__, SAFE_VALUE_TEXT(right));
            return right;
        }

        Value* current = left;

        if (right->GetText() < left->GetText())
        {
            head = right;
            current = right;
            right = right->GetNext();
        }
        else
        {
            left = left->GetNext();
        }

        while ((left != nullptr) && (right != nullptr))
        {
            if (left->GetText() <= right->GetText())
            {
                current->SetNext(left);
                current = left;
                left = left->GetNext();
            }
            else
            {
                current->SetNext(right);
                current = right;
                right = right->GetNext();
            }
        }

        // either left or right is not done,
        // else the while loop would have ended earlier
        if (left != nullptr)
        {
            current->SetNext(left);
        }
        else if (right != nullptr)
        {
            current->SetNext(right);
        }
        else
        {
            // done
        }
    }

    log.Trace("%s >> head = \"%s\"", __FUNCTION__, SAFE_VALUE_TEXT(head));
    return head;
}
