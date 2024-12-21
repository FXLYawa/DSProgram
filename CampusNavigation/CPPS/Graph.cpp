/********************************/
/* Created by FXLY, with VSCode */
/********************************/

#include "..\\Header\\Graph.h"

#include <cassert>

std::ostream& operator<<(std::ostream& out, const Node& p) {
    out << p.name << " " << p.type << " " << p.VisitTime;
    return out;
}

void Graph::AddNode(const Node& p) {
    if (NameToID.count(p.name)) throw GraphException{"名为 " + p.name + " 的节点已经存在"};
    int number = nodes.size();  // 分配编号
    NameToID[p.name] = number;
    TypeToID[p.type].insert(number);
    IsDeleted.push_back(0);
    nodes.push_back(p);
    graph.push_back({});
}

Node Graph::GetNode(const std::string& name) {
    if (NameToID.count(name))
        return nodes[NameToID[name]];
    else
        throw GraphException{"不存在名为 " + name + " 的节点"};
}

void Graph::ShowAllNodes() {
    std::cout << "顶点名称, 顶点类型, 建议游览时间:" << std::endl;
    for (int i = 0; i < nodes.size(); i++) {
        if (!IsDeleted[i]) std::cout << nodes[i] << std::endl;
    }
}

void Graph::ShowTypeNodes(const std::string& type) {
    if (TypeToID.count(type)) {
        std::cout << "顶点名称, 顶点类型, 建议游览时间:" << std::endl;
        for (auto& i : TypeToID[type]) {
            std::cout << nodes[i] << std::endl;
        }
    } else {
        throw GraphException{"不存在 " + type + " 类型的节点"};
    }
}

void Graph::DeleteNode(const std::string& name) {
    if (NameToID.count(name)) {
        int id = NameToID[name];
        IsDeleted[id] = 1;
        for (auto& v : graph[id])  // 删除指向p的边
            graph[v.first].erase({id, v.second});

        graph[id].clear();  // 删除p指出的边
        NameToID.erase(name);
        TypeToID[nodes[id].type].erase(id);
    } else {
        throw GraphException{"不存在名为 " + name + " 的节点"};
    }
}

void Graph::StoreNodes(const std::string& path) {
    std::ofstream fout(path);
    assert(fout.good());
    for (int i = 0; i < nodes.size(); i++) {
        if (!IsDeleted[i]) fout << nodes[i].name << "," << nodes[i].type << "," << nodes[i].VisitTime << std::endl;
    }
    fout.close();
}

void Graph::AddEdge(const Edge& e) {
    int u, v;
    if (NameToID.count(e.from)) {
        u = NameToID[e.from];
        if (IsDeleted[u]) throw GraphException{"不存在名为 " + e.from + " 的节点"};
    } else {
        throw GraphException{"不存在名为 " + e.from + " 的节点"};
    }
    if (NameToID.count(e.to)) {
        v = NameToID[e.to];
        if (IsDeleted[v]) throw GraphException{"不存在名为 " + e.to + " 的节点"};
    } else {
        throw GraphException{"不存在名为 " + e.to + " 的节点"};
    }
    graph[u].insert({v, e.length});  // 建立双向边
    graph[v].insert({u, e.length});
}

Edge Graph::GetEdge(const std::string& from, const std::string& to) {
    if (NameToID.count(from) == 0 || NameToID.count(to) == 0) {
        throw GraphException{"不存在从 " + from + " 到 " + to + " 的边"};
    }
    int u = NameToID[from], v = NameToID[to];
    auto it = graph[u].lower_bound({v, -1});
    if (it == graph[u].end() || (*it).first != v) {
        throw GraphException{"不存在从 " + from + " 到 " + to + " 的边"};
    } else {
        return {from, to, (*it).second};
    }
}

void Graph::ShowAllEdges() {
    std::cout << "起点,终点,距离:" << std::endl;
    for (int i = 0; i < nodes.size(); i++) {
        if (IsDeleted[i]) continue;
        // 让边均从编号大的指向小的，保证不重复
        for (auto v : graph[i]) {
            if (v.first >= i) break;
            std::cout << nodes[i].name << " " << nodes[v.first].name << " " << v.second << std::endl;
        }
    }
}

void Graph::DeleteEdge(const std::string& from, const std::string& to) {
    int u, v;
    if (NameToID.count(from)) {
        u = NameToID[from];
        if (IsDeleted[u]) throw GraphException{"不存在名为 " + from + " 的节点"};
    } else
        GraphException{"不存在名为 " + from + " 的节点"};
    if (NameToID.count(to)) {
        v = NameToID[to];
        if (IsDeleted[v]) throw GraphException{"不存在名为 " + to + " 的节点"};
    } else
        GraphException{"不存在名为 " + to + " 的节点"};
    auto it = graph[u].lower_bound({v, -1});
    if (it == graph[u].end() || (*it).first != v) {
        throw GraphException{"不存在从 " + from + " 到 " + to + " 的边"};
    } else {
        graph[u].erase(it);
        it = graph[v].lower_bound({u, -1});
        graph[v].erase(it);
    }
}

void Graph::StoreEdges(const std::string& path) {
    std::ofstream fout(path);
    assert(fout.good());
    for (int i = 0; i < nodes.size(); i++) {
        if (IsDeleted[i]) continue;
        // 让边均从编号大的指向小的，保证不重复
        for (auto v : graph[i]) {
            if (v.first >= i) break;
            std::cout << nodes[i].name << "," << nodes[v.first].name << "," << v.second << std::endl;
        }
    }
    fout.close();
}