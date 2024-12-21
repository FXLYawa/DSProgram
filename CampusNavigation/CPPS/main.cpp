/********************************/
/* Created by FXLY, with VSCode */
/********************************/

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "..\\Header\\DSU.h"
#include "..\\Header\\Graph.h"

// 文件路径(初始化使用)
const std::string dataID{"\\data_5"};
const std::string nodes_path{"E:\\work_tool\\document\\school\\DSProgram\\CampusNavigation\\TestData" + dataID + "\\nodes.csv"};
const std::string edges_path{"E:\\work_tool\\document\\school\\DSProgram\\CampusNavigation\\TestData" + dataID + "\\edges.csv"};
// const std::string nodes_path{"..\\TestData" + dataID + "\\nodes.csv"};
// const std::string edges_path{"..\\TestData" + dataID + "\\edges.csv"};

void init(Graph&);

int main() {
    Graph graph;  // 初始化一个无向图。
    init(graph);
    std::cout << "欢迎使用校园导航系统！" << std::endl;
    while (true) {
        int choice{0};
        std::cout << "请选择您要进行的操作：" << std::endl
                  << "1.顶点相关操作" << std::endl
                  << "2.边相关操作" << std::endl
                  << "3.从文件中重新加载点与边" << std::endl
                  << "4.获取欧拉回路" << std::endl
                  << "5.求任意两点间的最短距离" << std::endl
                  << "6.求最小生成树" << std::endl
                  << "7.求解拓扑受限时的最短路径" << std::endl
                  << "8.寻找校内交通瓶颈" << std::endl
                  << "9.退出程序" << std::endl
                  << "请输入操作前的数字：";
        std::cin >> choice;
        if (choice == 1) {
            while (true) {  // 顶点相关操作
                std::cout << "顶点相关操作：" << std::endl
                          << "1.输出特定顶点信息" << std::endl
                          << "2.输出所有顶点信息" << std::endl
                          << "3.添加一个顶点" << std::endl
                          << "4.删除一个顶点" << std::endl
                          << "5.存储顶点到文件中" << std::endl
                          << "6.输出特定类别的节点信息" << std::endl
                          << "7.回到上一级菜单" << std::endl
                          << "请输入操作前的数字：";
                std::cin >> choice;
                if (choice == 1) {
                    std::string name;
                    std::cout << "请输入顶点名称:";
                    std::cin >> name;
                    try {
                        Node p{graph.GetNode(name)};
                        std::cout << "顶点名称:" << p.name << std::endl;
                        std::cout << "顶点类型:" << p.type << std::endl;
                        std::cout << "建议游览时间:" << p.VisitTime << std::endl;
                    } catch (GraphException& s) {
                        std::cout << s.message << std::endl;
                    }
                } else if (choice == 2) {
                    graph.ShowAllNodes();
                } else if (choice == 3) {
                    std::cout << "请输入顶点名称，顶点类型，建议游览时间(空格分隔):";
                    Node p;
                    std::cin >> p.name >> p.type >> p.VisitTime;
                    try {
                        graph.AddNode(p);
                    } catch (GraphException& s) {
                        std::cout << s.message << std::endl;
                    }
                } else if (choice == 4) {
                    std::string name;
                    std::cout << "请输入顶点名称:";
                    std::cin >> name;
                    try {
                        graph.DeleteNode(name);
                    } catch (GraphException& s) {
                        std::cout << s.message << std::endl;
                    }
                } else if (choice == 5) {
                    std::cout << "请输入目标存储文件地址:";
                    std::string path;
                    std::cin >> path;
                    std::cout << "正在将顶点存储到" << path << "中..." << std::endl;
                    graph.StoreNodes(path);
                    std::cout << "存储成功！" << std::endl;
                } else if (choice == 6) {
                    std::string type;
                    std::cout << "请输入顶点类别:";
                    std::cin >> type;
                    try {
                        graph.ShowTypeNodes(type);
                    } catch (GraphException& s) {
                        std::cout << s.message << std::endl;
                    }
                } else
                    break;
            }
        } else if (choice == 2) {  // 边相关操作
            while (true) {
                std::cout << "边相关操作：" << std::endl
                          << "1.输出特定边信息" << std::endl
                          << "2.输出所有边信息" << std::endl
                          << "3.添加一条边" << std::endl
                          << "4.删除一条边" << std::endl
                          << "5.存储边到文件中" << std::endl
                          << "6.回到上一级菜单" << std::endl
                          << "请输入操作前的数字：";
                std::cin >> choice;
                if (choice == 1) {
                    std::string from, to;
                    std::cout << "请输入边的起点与终点(空格分隔):";
                    std::cin >> from >> to;
                    try {
                        Edge e = graph.GetEdge(from, to);
                        std::cout << from << " <---> " << to << " 距离为:" << e.length << std::endl;
                    } catch (GraphException& s) {
                        std::cout << s.message << std::endl;
                    }
                } else if (choice == 2) {
                    graph.ShowAllEdges();
                } else if (choice == 3) {
                    std::cout << "请输入起点名称,终点名称,距离(空格分隔):";
                    Edge e;
                    std::cin >> e.from >> e.to >> e.length;
                    try {
                        graph.AddEdge(e);
                    } catch (GraphException s) {
                        std::cout << s.message << std::endl;
                    }
                } else if (choice == 4) {
                    std::cout << "请输入起点名称,终点名称(空格分隔):";
                    std::string from, to;
                    std::cin >> from >> to;
                    try {
                        graph.DeleteEdge(from, to);
                    } catch (GraphException s) {
                        std::cout << s.message << std::endl;
                    }
                } else if (choice == 5) {
                    std::cout << "请输入目标存储文件地址:";
                    std::string path;
                    std::cin >> path;
                    std::cout << "正在边存储到" << path << "中..." << std::endl;
                    graph.StoreEdges(path);
                    std::cout << "存储成功！" << std::endl;
                } else
                    break;
            }
        } else if (choice == 3) {  // 从文件中重新加载点与边
            init(graph);
        } else if (choice == 4) {  // 获取欧拉回路
            try {
                graph.GetEulerCircle();
            } catch (GraphException s) {
                std::cout << s.message << std::endl;
            }
        } else if (choice == 5) {  // 求任意两点间的最短距离
            std::cout << "请输入两个地点(使用空格分开):" << std::endl;
            std::string from, to;
            std::cin >> from >> to;
            try {
                int length = graph.GetShortestPath(from, to);
                std::cout << from << "和" << to << "之间的最短距离为：" << length << std::endl;
            } catch (GraphException& s) {
                std::cout << s.message << std::endl;
            }

        } else if (choice == 6) {  // 求最小生成树
            if (graph.IsConnected()) {
                graph.Kruskal();
            }
        } else if (choice == 7) {  // 求解拓扑受限时的最短路径
            std::cout << "请输入您希望的拓扑序,第一行输入一个数字为地点数量,第二行输入地点为拓扑序列" << std::endl;
            int n;
            std::vector<std::string> place;
            std::cin >> n;
            while (n--) {
                std::string t;
                std::cin >> t;
                place.push_back(t);
            }
            try {
                std::cout << "该限制下的最短距离为:" << graph.GetLimitedShortestPath(place) << std::endl;
            } catch (GraphException s) {
                std::cout << s.message << std::endl;
            }
        } else if (choice == 8) {  // 寻找校内交通瓶颈(即图上的割点)
            try {
                auto res = graph.GetCutNodes();
                if (res.empty()) {
                    std::cout << "校内交通很顺畅,无明显瓶颈" << std::endl;
                } else {
                    std::cout << "校内交通瓶颈在以下地点:" << std::endl;
                    for (auto& v : res) std::cout << v << std::endl;
                }
            } catch (GraphException s) {
                std::cout << s.message << std::endl;
            }
        } else {
            std::cout << "感谢您的使用,再见!\nmade by \\FXLY_awa/" << std::endl;
            break;
        }
    }
    return 0;
}

/* 从文件中读取顶点信息
 * @param path: 顶点文件路径
 * @return: 包含读取到的所有顶点的std::vector
 */
std::vector<Node> read_nodes(std::string path) {
    std::ifstream fin(path);
    assert(fin.good());
    std::vector<Node> nodes;
    std::string line;
    while (std::getline(fin, line)) {
        if (line.empty()) continue;
        for (auto& c : line)
            if (c == ',') c = ' ';  // 便于构造输入流
        std::istringstream sin(line);
        Node tmp;
        sin >> tmp.name >> tmp.type >> tmp.VisitTime;
        nodes.push_back(tmp);
    }
    fin.close();
    return nodes;
}

/* 从文件中读取边信息
 * @param path: 顶点文件路径
 * @return: 包含读取到的所有顶点的std::vector
 */
std::vector<Edge> read_edges(std::string path) {
    std::ifstream fin(path);
    assert(fin.good());
    std::vector<Edge> edges;
    std::string line;
    while (std::getline(fin, line)) {
        if (line.empty()) continue;
        for (auto& c : line)
            if (c == ',') c = ' ';  // 便于构造输入流
        std::istringstream sin(line);
        Edge tmp;
        sin >> tmp.from >> tmp.to >> tmp.length;
        edges.push_back(tmp);
    }
    fin.close();
    return edges;
}

void init(Graph& graph) {
    graph.graph.clear();
    graph.TypeToID.clear();
    graph.nodes.clear();
    graph.IsDeleted.clear();
    graph.NameToID.clear();
    std::vector<Node> nodes{read_nodes(nodes_path)};
    std::vector<Edge> edges{read_edges(edges_path)};
    for (auto& p : nodes) {
        try {
            graph.AddNode(p);
        } catch (GraphException) {
            continue;
        }
    }
    for (auto& e : edges) {
        try {
            graph.AddEdge(e);
        } catch (GraphException) {
            continue;
        }
    }
}
