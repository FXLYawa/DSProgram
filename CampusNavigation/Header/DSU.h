/********************************/
/* Created by FXLY, with VSCode */
/********************************/

#ifndef DSU_DSU_FXLY
#define DSU_DSU_FXLY

#include <vector>

#include "Graph.h"

class DSU {
   private:
    // 父亲，以集合大小作为秩
    std::vector<int> father, rank;

   public:
    DSU(int);
    void init(int);
    // 查找根节点并路径压缩
    int find(int);
    // 合并两个集合
    void merge(int, int);
    // 检查两个节点是否属于同一集合
    bool issame(int, int);
    friend bool Graph::IsConnected();
};

#endif  // DSU_DSU_FXLY
