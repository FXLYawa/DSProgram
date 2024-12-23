/********************************/
/* Created by FXLY, with VSCode */
/********************************/

#ifndef HUFFMAN_HUFFMAN_FXLY
#define HUFFMAN_HUFFMAN_FXLY

#include <vector>
#include <map>
#include <string>
#include "Exception.h"

class Huffman {
   typedef unsigned char info;//information 
   private:
    int root;
    std::vector<int> lson, rson;
    std::vector<info> value;
    std::map<info,std::string> mp; 
    void dfs(int,std::string);
   public:
    Huffman(std::map<info,int>);
    int GetCompressedFile(std::string,std::string);
};

#endif  // HUFFMAN_HUFFMAN_FXLY
