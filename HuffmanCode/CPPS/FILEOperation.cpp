/********************************/
/* Created by FXLY, with VSCode */
/********************************/

#include "..//Header//FILEOperation.h"

#include <cassert>

/* 从文件中记录字符频率
 * @param file_path: 输入文件路径
 * @return: 字符统计频率
 */
std::map<unsigned char, int> File_Readers::SourceFileCount(std::string file_path) {
    std::map<info, int> res;
    std::ifstream fin(file_path, std::ios::in | std::ios::binary);
    assert(fin.good());
    char c;
    while ((c = fin.get()) != EOF) res[c]++;
    fin.close();
    return res;
}