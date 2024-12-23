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
#include "Exception.h"

namespace File_Readers {
    typedef unsigned char info;
    std::map<info, int> SourceFileCount(std::string);
    
};  // namespace File_Readers

#endif  // READFILE_READFILE_FXLY