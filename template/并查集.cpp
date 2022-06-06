#include<bits/stdc++.h>
//并查集模板
//简单的，平时用这个就可以了
int p[200010];
int find(int x) {
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

void merge(int a, int b) {
    int pa = find(a), pb = find(b);
    if(pa == pb) return;
    p[pa] = pb;
}

//初始化
for(int i=1;i<=n;i++)
{
    p[i]=i;
}

int main()
{
    return 0;
}

/*----------------------------------------*/
//封装的可以知道并查集个数的，但是注意是从0开始的,如果需要从一开始注意最后连通分量个数要减一。
class UnionFind {
public:
    vector<int> parent;
    vector<int> size;
    int n;
    // 当前连通分量数目
    int setCount;
    
public:
    UnionFind(int _n): n(_n), setCount(_n), parent(_n), size(_n, 1) {
        iota(parent.begin(), parent.end(), 0);//这个函数就是fill递增的数。
    }
    
    int findset(int x) {
        return parent[x] == x ? x : parent[x] = findset(parent[x]);
    }
    
    bool unite(int x, int y) {
        x = findset(x);
        y = findset(y);
        if (x == y) {
            return false;
        }
        if (size[x] < size[y]) {
            swap(x, y);
        }
        parent[y] = x;
        size[x] += size[y];
        --setCount;
        return true;
    }
    
    bool connected(int x, int y) {
        x = findset(x);
        y = findset(y);
        return x == y;
    }
};

