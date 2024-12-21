/********************************/
/* Created by FXLY, with VSCode */
/********************************/

#include <algorithm>
#include <functional>
#include <queue>
#include <stack>

#include "..\\Header\\DSU.h"
#include "..\\Header\\Graph.h"

void Graph::GetEulerCircle() {  // 输出欧拉回路
    int n = nodes.size();
    DSU dsu(n);
    for (int i = 0; i < n; i++) {
        if (IsDeleted[i]) continue;
        for (auto v : graph[i]) {
            if (v.first >= i) break;  // 小到大即可,降低复杂度
            dsu.merge(i, v.first);
        }
    }
    int t = -1;
    for (int i = 0; i < n; i++) {
        if (!graph[i].empty()) {
            if (graph[i].size() % 2) throw GraphException{"欧拉回路不存在"};
            if (t == -1) {
                t = dsu.find(i);
            } else if (t != dsu.find(i)) {
                throw GraphException{"欧拉回路不存在"};
            }
        }
    }
    // fleury求欧拉回路
    std::vector<std::pair<int, int>> edges;  // first为to,second指向下一条边
    std::vector<int> head(n, -1);
    for (int i = 0; i < n; i++) {
        if (IsDeleted[i]) continue;
        for (auto v : graph[i]) {
            if (v.first >= i) break;
            edges.push_back({v.first, head[i]});
            head[i] = edges.size() - 1;
            edges.push_back({i, head[v.first]});
            head[v.first] = edges.size() - 1;
        }
    }
    std::vector<int> EulerRoad, vis(edges.size());
    std::stack<int> st;
    std::function<void(int)> dfs = [&](int u) {
        st.push(u);
        for (int i = head[u]; ~i; i = edges[i].second) {
            if (vis[i]) continue;
            vis[i] = vis[1 ^ i] = 1;
            dfs(edges[i].first);
            break;
        }
    };
    int s = 0;
    while (graph[s].empty()) s++;
    st.push(s);
    while (!st.empty()) {
        int flag = 0, u = st.top();
        st.pop();
        for (int i = head[u]; ~i; i = edges[i].second) {
            if (vis[i]) continue;
            flag = 1;
            break;
        }
        if (!flag)
            EulerRoad.push_back(u);
        else
            dfs(u);
    }

    std::cout << "找到一条欧拉路:" << std::endl;
    for (int i = 0; i < EulerRoad.size() - 1; i++) std::cout << nodes[EulerRoad[i]].name << " ---->";

    std::cout << nodes[EulerRoad.back()].name << std::endl;
}

int Graph::GetShortestPath(const std::string& from, const std::string& to) {  // 返回最短路长度
    if (NameToID.count(from) == 0 || IsDeleted[NameToID[from]]) throw GraphException{"不存在名为 " + from + " 的节点"};
    if (NameToID.count(to) == 0 || IsDeleted[NameToID[to]]) throw GraphException{"不存在名为 " + to + " 的节点"};
    // Dijkstra
    int n = nodes.size();
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;
    std::vector<int> distance(n, 0x7f7f7f7f), vis(n);
    int s = NameToID[from];
    distance[s] = 0, q.push({0, s});
    while (!q.empty()) {
        int u = q.top().second;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto ed : graph[u]) {
            int v = ed.first, w = ed.second;
            if (distance[v] > distance[u] + w) {
                distance[v] = distance[u] + w;
                q.push({distance[v], v});
            }
        }
    }
    int t = NameToID[to];
    if (distance[t] == 0x7f7f7f7f) throw GraphException{from + " 与 " + to + " 不连通"};
    return distance[t];
}

bool Graph::IsConnected() {  // 判断连通性,若不连通,询问是否加边
    int n = nodes.size();
    DSU dsu(n);
    for (int i = 0; i < n; i++) {
        if (IsDeleted[i]) continue;
        for (auto v : graph[i]) {
            if (v.first >= i) break;  // 小到大即可,降低复杂度
            dsu.merge(i, v.first);
        }
    }
    std::set<int> st;
    for (auto i : dsu.father) {
        if (IsDeleted[i])
            continue;
        else
            st.insert(i);
    }
    if (st.size() <= 1) return true;
    std::cout << "图不连通,是否加边[y/n]:";
    char choice;
    std::cin >> choice;
    std::cout << std::endl;
    if (choice == 'n') return false;
    std::cout << "请给以下边赋权值" << std::endl;
    auto it = st.begin();
    int u = *st.begin();
    while (++it != st.end()) {
        Edge e{nodes[u].name, nodes[*it].name, 0};
        std::cout << e.from << " <---> " << e.to << ":";
        std::cin >> e.length;
        AddEdge(e);
        std::cout << std::endl;
    }
    return true;
}

void Graph::Kruskal() {  // 输出最小生成树 边和总权值
    if (!IsConnected()) {
        std::cout << "图不连通,无最小生成树" << std::endl;
        return;
    }
    std::vector<std::array<int, 3>> edges;
    int sum = 0;
    int n = nodes.size();
    DSU dsu(n);
    for (int i = 0; i < n; i++) {
        if (IsDeleted[i]) continue;
        for (auto v : graph[i]) {
            if (v.first >= i) break;  // 小到大即可,降低复杂度
            edges.push_back({v.second, i, v.first});
        }
    }
    std::sort(edges.begin(), edges.end());
    std::cout << "以下是属于最小生成树的边:" << std::endl;
    for (auto& e : edges) {
        if (dsu.issame(e[1], e[2])) continue;
        dsu.merge(e[1], e[2]);
        sum += e[0];
        std::cout << nodes[e[1]].name << " <---> " << nodes[e[2]].name << std::endl;
    }
    std::cout << "最小生成树的总权值为:" << sum << std::endl;
}

int Graph::GetLimitedShortestPath(const std::vector<std::string>& topo) {  // 返回拓扑受限的最短路长度
    if (topo.size() <= 1) throw GraphException{"所给序列太短"};
    int sum = 0;
    for (int i = 0, j = 1; j < topo.size(); i++, j++) {
        sum += GetShortestPath(topo[i], topo[j]);
        sum+=nodes[NameToID[topo[i]]].VisitTime;
    }
    sum+=nodes[NameToID[topo.back()]].VisitTime;
    return sum;
}

std::vector<std::string> Graph::GetCutNodes() {  // 计算割点并返回
    int n = nodes.size();
    std::vector<int> dfn(n), low(n), fa(n, -1), cut(n);
    int dfncnt = 0;
    std::function<void(int)> tarjan = [&](int u) {
        dfn[u] = low[u] = ++dfncnt;
        int cnt = 0;
        for (auto e : graph[u]) {
            int v = e.first;
            if (dfn[v]) {
                if (v != fa[u]) low[u] = std::min(low[u], dfn[v]);
                continue;
            }
            cnt++, fa[v] = u;
            tarjan(v);
            low[u] = std::min(low[u], low[v]);
            if (fa[u] == -1 && cnt > 1 || fa[u] != -1 && dfn[u] <= low[v]) cut[u] = 1;
        }
    };
    for (int i = 0; i < n; i++) {
        if (IsDeleted[i] || dfn[i]) continue;
        tarjan(i);
    }
    std::vector<std::string> res;
    for (int i = 0; i < n; i++) {
        if (IsDeleted[i] || !cut[i]) continue;
        res.push_back(nodes[i].name);
    }
    return res;
}
