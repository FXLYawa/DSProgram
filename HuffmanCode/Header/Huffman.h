/********************************/
/* Created by FXLY, with VSCode */
/********************************/

#ifndef HUFFMAN_HUFFMAN_FXLY
#define HUFFMAN_HUFFMAN_FXLY

#include <map>
#include <string>
#include <vector>

class Huffman {
    typedef unsigned char info;  // information
   private:
    int root,pos;
    std::vector<int> lson, rson;
    std::vector<info> value;
    std::map<info, std::string> mp;
    void dfs(int, std::string);
    bool move(bool);
    info get();
   public:
    Huffman(std::map<info, int>);
    int GetCompressedFile(std::string, std::string);
    void GetDeCompressedFile(std::string, std::string);
};

#endif  // HUFFMAN_HUFFMAN_FXLY
