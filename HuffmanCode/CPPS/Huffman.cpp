#include "..//Header//Huffman.h"

#include <queue>
#include <array>

Huffman::Huffman(std::map<info, int> data_weight) {
    typedef std::array<int,3> node;// 节点权重，子节点数量，节点编号  
    int n = data_weight.size();
    value.resize(2 * n);
    lson.resize(2 * n);
    rson.resize(2 * n);
    std::priority_queue<node,std::vector<node>,std::greater<node>> q;
    int cnt = 0;
    for (auto& t : data_weight){
        value[++cnt]=t.first;
        q.push({t.second,1,cnt});
    }
    while (q.size() >= 2) {
        node tmp{0,1,++cnt};
        tmp[0]+=q.top()[0];
        tmp[1]+=q.top()[1];
        lson[cnt]=q.top()[2];
        q.pop();
        tmp[0]+=q.top()[0];
        tmp[1]+=q.top()[1];
        rson[cnt]=q.top()[2];
        q.pop();
        q.push(tmp);
    }
    root=q.top()[2];
}