#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Kruskal
{
    int father[100001];

    int find(int i)
    {
        if (i != father[i])
        {
            father[i] = find(father[i]);
        }
        return father[i];
    }

    bool combine(int x, int y)
    {
        int fx = find(x);
        int fy = find(y);
        if (fx != fy)
        {
            father[fx] = fy;
            return true;
        }
        return false;
    }

    void build(int n)
    {
        for (int i = 1; i <= n; i++)
        {
            father[i] = i;
        }
    }

public:
    long long MST(int n, vector<vector<int>>& lines)
    {
        sort(lines.begin(), lines.end(), [&](vector<int>& a, vector<int>& b)
            {
                return a[2] < b[2];
            });
        build(n);
        int linecnt = 0;
        long long ans = 0;
        for (auto& line : lines)
        {
            if (combine(line[0], line[1]))
            {
                linecnt++;
                ans += (long long)line[2];
            }
            if (linecnt == n - 1)break;
        }
        return linecnt == n - 1 ? ans : -1;
    }
};

struct cmp
{
    bool operator() (pair<int, int>& p1, pair<int, int>& p2)
    {
        return p1.second > p2.second;
    }
};

class Prim
{
    vector<vector<pair<int, int>>> graph;
    bool visited[100001];

    priority_queue < pair<int, int>, vector<pair<int, int>>, cmp> q;

public:

    long long MST(int n, vector<vector<int>>& lines)
    {
        graph.resize(n + 1);
        for (auto& line : lines)
        {
            int& x = line[0];
            int& y = line[1];
            int& w = line[2];
            graph[x].push_back({ y,w });
            graph[y].push_back({ x,w });
        }

        for (auto& line : graph[1])
        {
            q.push(line);
        }
        visited[1] = true;
        long long ans = 0;
        int Nodecnt = 1;

        while (!q.empty())
        {
            auto cur = q.top();
            q.pop();
            if (!visited[cur.first])
            {
                ans += cur.second;
                Nodecnt++;
                visited[cur.first] = true;
                for (auto& line : graph[cur.first])
                {
                    q.push(line);
                }
            }
            if (Nodecnt == n)break;
        }
        return Nodecnt == n ? ans : -1;
    }
};


vector<vector<int>> relations;
vector<int> favorite;

int main()
{
    int n, m;
    cin >> n >> m;
    relations.resize(m);
    int x, y, k;
    for (int i = 0; i < m; i++)
    {
        cin >> x >> y >> k;
        relations[i] = { x,y,k };
    }
    long long ans;
    auto solution = new Prim;
    ans = solution->MST(n, m, relations);
    if (ans == -1)cout << "orz";
    else cout << ans;
}