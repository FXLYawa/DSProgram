/********************************/
/* Created by FXLY, with VSCode */
/********************************/

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "..//Header//Algorithm.h"
#include "..//Header//Exception.h"
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
                  << "4.退出程序" << std::endl
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
            std::cout << "请输入您要的比较文件名字,使用绝对地址的格式,并对\\进行转义\n";
            std::string a, b;
            std::cin >> a;
            std::cout << std::endl;
            std::cout << "文件2:";
            std::cin >> b;
            std::cout << std::endl;
            Compare(a, b);
        } else {
            std::cout << "感谢您的使用,再见!\nmade by \\FXLY_awa/" << std::endl;
            std::cout << "文件1:";
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
    for (auto &t : res) {
        fout << t.first << "," << t.second << '\n';
        SourceBitCount += t.second;
    }
    fout.close();
    std::cout << "统计完成,结果存储在 " + name + ".csv" << std::endl;
    std::cout << "开始文件压缩" << std::endl;
    Huffman tree(res);
    CpFileBitcount = tree.GetCompressedFile(program_path + "\\Input\\" + file_name, program_path + "\\Result\\" + file_name);
    std::cout << "压缩完成,结果存储在 " +file_name << std::endl;
    return (double)SourceBitCount / CpFileBitcount;
}
void Decompress(std::string file_name) {
    // TODO
}
void Compare(std::string first_file_path, std::string second_file_path) {
    // TODO
}