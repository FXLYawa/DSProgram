/********************************/
/* Created by FXLY, with VSCode */
/********************************/

#ifndef READFILE_READFILE_FXLY
#define READFILE_READFILE_FXLY

#include <fstream>
#include <iostream>
#include <map>
#include <vector>

#include "..//Header//Huffman.h"

namespace File_Readers {
    typedef unsigned char info;
    const unsigned long long hash=0x1F351F35;
    std::map<info, int> SourceFileCount(std::string);
    unsigned long long gethash(std::string); 
    std::map<info, int> CSVFileRead(std::string);
    void ShowTypeCount(std::string);
};  // namespace File_Readers

#endif  // READFILE_READFILE_FXLY