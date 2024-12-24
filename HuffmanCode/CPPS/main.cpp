/********************************/
/* Created by FXLY, with VSCode */
/********************************/

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "..//Header//FILEOperation.h"
#include "..//Header//Huffman.h"

// 程序所在路径(初始化使用
const std::string program_path{"E:\\work_tool\\document\\school\\DSProgram\\HuffmanCode"};

double Compress(std::string);
void Decompress(std::string);
void Compare(std::string, std::string);

int main() {
    std::cout << "基于Huffman的文件压缩系统!" << std::endl;
    while (true) {
        int choice{0};
        std::cout << "请选择您要进行的操作：" << std::endl
                  << "1.压缩文件" << std::endl
                  << "2.解压文件" << std::endl
                  << "3.验证解压结果" << std::endl
                  << "4.查看编码字符统计" << std::endl
                  << "5.退出程序" << std::endl
                  << "请输入操作前的数字：";
        std::cin >> choice;
        if (choice == 1) {
            std::cout << "请输入您要压缩的文件名字:";
            std::string s;
            std::cin >> s;
            double res = Compress(s);
            std::cout << "该文件的压缩率为:" << res << std::endl;
        } else if (choice == 2) {
            std::cout << "请输入您要解压的文件名字:";
            std::string s;
            std::cin >> s;
            Decompress(s);
        } else if (choice == 3) {
            std::cout << "请输入您要的比较文件名字,使用绝对地址的格式\n";
            std::string a, b;
            std::cout << "文件1:";
            std::cin >> a;
            std::cout << "文件2:";
            std::cin >> b;
            Compare(a, b);
        } else if (choice == 4) {
            std::cout << "请输入您要查看的文件名字(后缀名为csv):";
            std::string s;
            std::cin >> s;
            File_Readers::ShowTypeCount(program_path + "\\Result\\" + s);
        } else {
            std::cout << "感谢您的使用,再见!\nmade by \\FXLY_awa/" << std::endl;
            break;
        }
    }
}

double Compress(std::string file_name) {
    int SourceBitCount = 0, CpFileBitcount = 0;
    std::cout << "正在统计词频" << std::endl;
    auto res = File_Readers::SourceFileCount(program_path + "\\Input\\" + file_name);
    std::string name;
    for (auto c : file_name) {
        if (c == '.')
            break;
        else
            name.push_back(c);
    }
    std::ofstream fout(program_path + "\\Result\\" + name + ".csv", std::ios::out | std::ios::binary);
    assert(fout.good());
    typedef unsigned char info;
    for (auto &t : res) {
        fout << (info)t.first << (info)',';
        for (int i = 24; i != -8; i -= 8) fout << (info)((info)(t.second >> i) | 0);
        fout << (info)'\n';
        SourceBitCount += t.second;
    }
    fout.close();
    std::cout << "统计完成,结果存储在 " + name + ".csv" << std::endl;
    std::cout << "开始文件压缩" << std::endl;
    Huffman tree(res);
    CpFileBitcount = tree.GetCompressedFile(program_path + "\\Input\\" + file_name, program_path + "\\Result\\" + file_name);
    std::cout << "压缩完成,结果存储在 " + file_name << std::endl;
    return (double)SourceBitCount / CpFileBitcount;
}
void Decompress(std::string file_name) {
    std::cout << "开始文件解压" << std::endl;
    std::string name;
    for (auto c : file_name) {
        if (c == '.')
            break;
        else
            name.push_back(c);
    }
    auto res = File_Readers::CSVFileRead(program_path + "\\Result\\" + name + ".csv");
    Huffman tree(res);
    tree.GetDeCompressedFile(program_path + "\\Result\\" + file_name, program_path + "\\DeCpFile\\" + file_name);
    std::cout << "解压完成,结果存储在 /DeCpfile/" + file_name << std::endl;
}
void Compare(std::string first_file_path, std::string second_file_path) {
    unsigned long long first = File_Readers::gethash(first_file_path), second = File_Readers::gethash(second_file_path);
    if (first == second)
        std::cout << "两份文件内容相同" << std::endl;
    else
        std::cout << "两份文件内容不同" << std::endl;
}