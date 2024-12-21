/********************************/
/* Created by FXLY, with VSCode */
/********************************/

#ifndef GRAPH_GRAPH_FXLY
#define GRAPH_GRAPH_FXLY

#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

struct Edge {  // 路
    std::string from;
    std::string to;
    int length;
};

struct Node {  // 地点
    std::string type;
    std::string name;
    int VisitTime;
    friend std::ostream& operator<<(std::ostream&, const Node&);
};
std::ostream& operator<<(std::ostream&, const Node&);

struct GraphException {  // 图相关报错信息
    std::string message;
};

class Graph {
   private:
    std::map<std::string, int> NameToID;  // 地点名字与编号的映射 从0开始
    // 用类型检索地点，考虑到通常来说类型的数量远少于地点，故不离散化
    std::map<std::string, std::set<int>> TypeToID;
    std::vector<Node> nodes;       // 记录点的数据
    std::vector<int> IsDeleted;  // 记录某一个节点是否被删除F
    // 存储图信息，用set保证复杂度,first为终点，second为长度
    std::vector<std::set<std::pair<int, int>>> graph;

   public:
    // Group operations   defined in Graph.cpp
    void AddNode(const Node&);                                // 加入一个点
    Node GetNode(const std::string&);                         // 获得特定点的信息
    void ShowAllNodes();                                      // 输出所有点
    void ShowTypeNodes(const std::string&);                   // 输出特定类型的所有点
    void DeleteNode(const std::string&);                      // 删除一个点
    void StoreNodes(const std::string&);                      // 将点存储到文件
    void AddEdge(const Edge&);                                // 加入一条边
    Edge GetEdge(const std::string&, const std::string&);     // 获取一条边的信息
    void ShowAllEdges();                                      // 输出所有边
    void DeleteEdge(const std::string&, const std::string&);  // 删除一条边
    void StoreEdges(const std::string&);                      // 将边存储到文件

    // Group Algorithm   defined in Algorithm.cpp
    void GetEulerCircle();//寻找欧拉回路
    int  GetShortestPath(const std::string&,const std::string&);//查找两点间的最短路
    bool IsConnected(); //判断图是否连通  若不连通 询问是否加边
    void Kruskal();//生成最小生成树
    int GetLimitedShortestPath(const std::vector<std::string>&);//计算拓扑受限的最短路
    std::vector<std::string> GetCutNodes();//找到图上的割点

    friend void init(Graph&);
};

#endif  // GRAPH_GRAPH_FXLY