#include "FileStructure.h"

#include <fstream>
#include <iostream>
#include <string.h>

FileStructure::FileStructure(Log& log)
    : log(log)
{
}

void FileStructure::LoadFile(const std::string& filename, List& list)
{
    log.Trace("%s << filename = %s", __FUNCTION__, filename.c_str());

    uint64_t counter = 0;
    std::ifstream file(filename.c_str(), std::ios::binary | std::ios::ate);
    if (file.is_open())
    {
        size_t size = file.tellg();
        char* start = new char[size];
        if (start != nullptr)
        {
            char* current = start;

            file.seekg(0, std::ios::beg);
            file.read(start, size);
            file.close();

            std::string word("");

            word = GetNextWord(start, &current, size);
            while (word != "")
            {
                counter++;
                list.Add(word);
                word = GetNextWord(start, &current, size);
            }

            delete[] start;
            start = nullptr;    // This results in Klocwork issue: never used after
            current = nullptr;  // assignment code is still here because it is
        }                       // required by our coding standard. With good reason!
    }

    log.Trace("%s >> read %lu words from %s", __FUNCTION__, counter, filename.c_str());
}

void FileStructure::SaveFile(List& list, const std::string& filename) const
{
    log.Trace("%s << filename = %s", __FUNCTION__, filename.c_str());

    uint64_t counter = 0;
    std::ofstream ofile(filename.c_str(), std::ios::binary);
    if (ofile.is_open())
    {
        Value* temp = list.GetHead();
        std::string filebuffer = "";
        while (temp != nullptr)
        {
            counter++;
            filebuffer += temp->GetText() + "\n";
            temp = temp->GetNext();
        }

        size_t size = filebuffer.size();
        const char* buffer = filebuffer.c_str();
        ofile.write(buffer, size);

        ofile.close();
    }

    log.Trace("%s >> wrote %lu words to %s", __FUNCTION__, counter, filename.c_str());
}


std::string FileStructure::GetNextWord(const char* start, char** current, size_t size) const
{
    std::string word("");

    if (start != nullptr)
    {
        char* temp = *current;
        size_t currentSize = temp - start;
        while ((currentSize < size) && (*temp != '\n'))
        {
            temp++;
            currentSize = temp - start;
        }
        if (currentSize < size)
        {
            *temp = '\0';
            word = *current;
            *current = temp + 1;
        }
    }

    return word;
}
