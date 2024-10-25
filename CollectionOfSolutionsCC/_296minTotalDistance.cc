#include "Solution.h"

// 暴力使用有序集合，卡在了最后一个全1的样例上 TLE 了。。。
int Leetcode201_300::Solution::minTotalDistance(vector<vector<int>>& grid)
{
    // 本题依然可以用一个简单的有序集合完成，只是我们可能会需要重载一下有序集合的比较规则
    struct cmp 
    {
        bool operator() (const vector<int>& a, const vector<int>& b)
        {
            // 定义为小顶堆
            return a[2] > b[2];
        }
    };
    priority_queue<vector<int>, vector<vector<int>>, cmp> minQ;
    int m = grid.size(), n = grid[0].size();
    // 先进行一轮预处理，为了计算曼哈顿距离，我们需要知道所有朋友家的位置坐标
    // 用一个数对数组存储即可
    vector<pair<int, int>> memo;
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(grid[i][j] == 1)
            {
                memo.push_back(make_pair<int&, int&>(i, j));
            }
        }
    }
    int cnt = memo.size();
    // 正式开始算法过程
    // 对于所有位置，我们都需要检查其到三个朋友家的曼哈顿距离和
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            int dist = 0;
            // 计算到所有朋友家的曼哈顿距离和，并压入三元组到小优先队列中
            for(int k = 0; k < cnt; ++k)
            {
                dist += (abs(i-memo[k].first)+abs(j-memo[k].second));
            }
            minQ.push({i, j, dist});
        }
    }
    // 添加完成，我们只需要返回队列头部的那个三元组对应的坐标即可，它是距离最小的那个坐标
    return minQ.top()[2];
}

// 题解区找到了 morisa 大神的解法，只能说是数学至上主义者的胜利
// 很巧妙，画一画图，稍微思考一下，就会感叹自己智商还是太低了hhhhh
int minTotalDistance(vector<vector<int>>& grid)
{
	vector<int> X, Y;
	int row = grid.size(), col = grid[0].size();
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			if (grid[i][j] == 1)
			{
				X.emplace_back(i);
				Y.emplace_back(j);
			}
		}
	}
	sort(X.begin(), X.end());
	sort(Y.begin(), Y.end());
	int n = X.size();
	int m = n >> 1;
	int r = 0;
	for (int i = 0; i < m; ++i)
	{
		r += X[n - i - 1] - X[i] + Y[n - i - 1] - Y[i];
	}
	return r;
}