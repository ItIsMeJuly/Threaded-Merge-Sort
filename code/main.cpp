#include "FileStructure.h"
#include "List.h"

#include <iostream>

void PrintList(List& list)
{
    Value* temp = list.GetHead();
    while (temp != nullptr)
    {
        std::cout << temp->GetText() << "\n";
        temp = temp->GetNext();
    }
}


int main()
{
    Log log;
    FileStructure filestructure(log);
    List list(log);

    filestructure.LoadFile("data/mediumlist.txt", list);

    // to compare bigger lists: delete next 2 lines, write program's output to
    // file and compare that file to sorted file in data dir
    // list.Print();
    // std::cout << "\n\n";

    list.Sort();
    PrintList(list);


    return 0;
}
