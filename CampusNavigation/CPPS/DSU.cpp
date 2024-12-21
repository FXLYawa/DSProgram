/********************************/
/* Created by FXLY, with VSCode */
/********************************/

#include "..\\Header\\DSU.h"

DSU::DSU(int n) {
    father.assign(n + 1, 0);
    rank.assign(n + 1, 1);
    for (int i = 0; i <= n; i++) father[i] = i;
}

void DSU::init(int n) {
    father.assign(n + 1, 0);
    rank.assign(n + 1, 1);
    for (int i = 0; i <= n; i++) father[i] = i;
}

int DSU::find(int x) {
    if (father[x] == x)
        return x;
    else
        return father[x] = find(father[x]);
}

void DSU::merge(int x, int y) {
    int u = find(x), v = find(y);
    if (u != v) {
        if (rank[u] >= rank[v])
            father[v] = u, rank[u] += rank[v];
        else
            father[u] = v, rank[v] += rank[u];
    }
}

bool DSU::issame(int x, int y) { return find(x) == find(y); }