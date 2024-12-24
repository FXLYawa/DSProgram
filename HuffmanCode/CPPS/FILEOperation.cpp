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

/* 文件hash
 * @param file_path: 输入文件路径
 * @return: 文件的hash值
 */
unsigned long long File_Readers::gethash(std::string file_path) {
    unsigned long long res;
    std::ifstream fin(file_path, std::ios::in | std::ios::binary);
    assert(fin.good());
    char c;
    while (fin) res = res * hash + (unsigned char)fin.get();
    fin.close();
    return res;
}

/* 从CSV文件中读取字符频率
 * @param file_path: 输入文件路径
 * @return: 字符统计频率
 */
std::map<unsigned char, int> File_Readers::CSVFileRead(std::string file_path) {
    std::map<info, int> res;
    std::ifstream fin(file_path, std::ios::in | std::ios::binary);
    assert(fin.good());
    char c;
    int cnt = 0;
    // while ((c = fin.get()) != EOF) {
    while(fin){
        c=fin.get();
        if(fin.get()!=',')break;
        for (int i = 1; i <= 4; i++) cnt = (cnt << 8) + (unsigned char)fin.get();
        fin.get();
        res[c] = cnt;
    }
    return res;
}

void File_Readers::ShowTypeCount(std::string file_path){
    std::ifstream fin(file_path, std::ios::in | std::ios::binary);
    assert(fin.good());
    char c;
    int cnt = 0;
    // while ((c = fin.get()) != EOF) {
    while(fin){
        c=fin.get();
        if(fin.get()!=',')break;
        for (int i = 1; i <= 4; i++) cnt = (cnt << 8) + (unsigned char)fin.get();
        fin.get();
        std::cout<<c<<","<<cnt<<std::endl;
    }
}