/********************************/
/* Created by FXLY, with VSCode */
/********************************/

#ifndef HUFFMAN_HUFFMAN_FXLY
#define HUFFMAN_HUFFMAN_FXLY

#include <vector>
#include <map>

class Huffman {
   typedef unsigned char info;//information 
   private:
    int root;
    std::vector<int> lson, rson;
    std::vector<info> value;
   public:
    Huffman(std::map<info,int>);
};

#endif  // HUFFMAN_HUFFMAN_FXLY
