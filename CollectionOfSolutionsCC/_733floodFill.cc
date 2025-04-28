#include "Solution.h"

vector<vector<int>> Leetcode701_800::Soltuion::floodFill(vector<vector<int>>& image, int sr, int sc, int color)
{
    // 简单的 DFS 类问题，我们直接写就行
    const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int m = image.size(), n = image[0].size();
    vector<vector<int>> vis(m, vector<int>(n, 0));
    function<void(int, int, const int&)> dfs = [&](int i, int j, const int& src) -> void
    {
        // 我们首先需要对本格进行渲染
        image[i][j] = color;
        // 之后递归遍历四个方向，进行处理 (只有当相邻像素颜色不同时才修改)
        for(int k = 0; k < 4; ++k)
        {
            // 注意检查相邻格子的合法性
            int nxti = i+dirs[k][0], nxtj = j+dirs[k][1];
            if(nxti >= 0 && nxti < m && nxtj >= 0 && nxtj < n && image[nxti][nxtj] == src && !vis[nxti][nxtj])
            {
                vis[nxti][nxtj] = 1;
                dfs(nxti, nxtj, src);
            }
        }
        // 处理完成，返回即可
    };
    int src = image[sr][sc];
    dfs(sr, sc, src);
    return image;
}