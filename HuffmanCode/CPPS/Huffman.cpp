/********************************/
/* Created by FXLY, with VSCode */
/********************************/

#include "..//Header//Huffman.h"

#include <array>
#include <cassert>
#include <fstream>
#include <queue>

#include "..//Header//Cryption.h"

Huffman::Huffman(std::map<info, int> data_weight) {
    typedef std::array<int, 3> node;  // 节点权重，子节点数量，节点编号
    int n = data_weight.size();
    value.resize(2 * n);
    lson.resize(2 * n);
    rson.resize(2 * n);
    std::priority_queue<node, std::vector<node>, std::greater<node>> q;
    int cnt = 0;
    for (auto& t : data_weight) {
        value[++cnt] = t.first;
        q.push({t.second, 1, cnt});
    }
    while (q.size() >= 2) {
        node tmp{0, 1, ++cnt};
        tmp[0] += q.top()[0];
        tmp[1] += q.top()[1];
        lson[cnt] = q.top()[2];
        q.pop();
        tmp[0] += q.top()[0];
        tmp[1] += q.top()[1];
        rson[cnt] = q.top()[2];
        q.pop();
        q.push(tmp);
    }
    root = pos = q.top()[2];
    dfs(root, "");
}

void Huffman::dfs(int u, std::string s) {
    if (lson[u] + rson[u] == 0) {
        mp[value[u]] = s;
        return;
    }
    dfs(lson[u], s + '0');
    dfs(rson[u], s + '1');
}

int Huffman::GetCompressedFile(std::string source_file, std::string result_file) {
    int CpFileBitcount = 0;
    std::ifstream fin(source_file, std::ios::in | std::ios::binary);
    std::ofstream fout(result_file, std::ios::out | std::ios::binary);
    assert(fin.good());
    assert(fout.good());
    char c;
    Cryption::EnCryption cryp;
    while (fin) {
        c = fin.get();
        if(c==EOF&&fin.peek()==EOF)break;
        std::string s = mp[c];
        for (auto t : s)
            if (cryp.push(t == '1')) fout << cryp.get(), CpFileBitcount++;
    }
    fin.close();
    fout.close();
    return CpFileBitcount;
}

void Huffman::GetDeCompressedFile(std::string source_file, std::string result_file) {
    std::ifstream fin(source_file, std::ios::in | std::ios::binary);
    std::ofstream fout(result_file, std::ios::out | std::ios::binary);
    assert(fin.good());
    assert(fout.good());
    char c;
    Cryption::DeCryption cryp;
    while (fin) {
        char c=fin.get();
        char t = cryp.get(c);
        if(c==EOF&&fin.peek()==EOF)break;
        for (int i = 7; ~i; i--)
            if (move((t >> i) & 1)) fout << get();
    }
    fin.close();
    fout.close();
}

bool Huffman::move(bool way) {
    if (way)
        pos = rson[pos];
    else
        pos = lson[pos];
    return lson[pos] + rson[pos] == 0;
}

unsigned char Huffman::get() {
    info res = value[pos];
    pos = root;
    return res;
}