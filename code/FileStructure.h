#ifndef FILESTRUCTURE_H
#define FILESTRUCTURE_H

#include "List.h"
#include "Log.h"

#include <string>

class FileStructure
{
public:
    FileStructure(Log& log);
    // post: FileStructure object is properly initialised

    FileStructure(const FileStructure&) = delete;
    FileStructure& operator=(const FileStructure&) = delete;

    void LoadFile(const std::string& filename, List& list);
    // post: if file with filename exists, its data is read, decoded and stored
    // in a
    //       proper key/value tree.

    void SaveFile(List& head, const std::string& filename) const;
    // post: if a file with filename can be created, head is recursively written
    // it

private:
    Log& log;

    std::string GetNextWord(const char* start, char** current, size_t size) const;
};

#endif
