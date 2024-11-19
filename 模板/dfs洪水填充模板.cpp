class Solution {
public:
    int n;
    int m;
    int numIslands(vector<vector<char>>& grid) {
        n = grid.size();
        m = grid[0].size();
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] == '1')
                {
                    dfs(i, j, grid);
                    ans++;
                }
            }
        }
        return ans;
    }

    void dfs(int x, int y, vector<vector<char>>& grid)
    {
        if (x < 0 || x >= n || y < 0 || y >= m)return;
        if (grid[x][y] != '1')return;
        grid[x][y] = 0;
        dfs(x - 1, y, grid);
        dfs(x + 1, y, grid);
        dfs(x, y - 1, grid);
        dfs(x, y + 1, grid);
    }
};