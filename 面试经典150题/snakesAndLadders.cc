#include <iostream>
#include <unordered_set>
#include <queue>

class Solution
{
public:
    int snakesAndLadders(vector<vector<int>>& board)
    {
        // 比较经典的 BFS 类问题
        // 我们可以定义下面的 BFS 状态：
        // 我们只需要在队列中记录一组广搜到的格子即可
        // 一旦某一条路径走到了目的地 n^2 格，我们就可以直接结束循环了
        // 注意在遍历的过程中检查是否有重复结点添加的问题，如果有的结点已经添加过了，那么我们就不能重复添加
        // 用一个哈希集合尝试进行去重
        unordered_set<int> memo;
        // 用一个队列来完成模拟流程
        queue<int> q;
        // 本题一个稍微难思考的点就在于矩阵坐标和实际的方格序号之间的映射问题
        // 为了简化问题，我们可以把上面的二维矩阵按题目要求压缩成一维数组
        // 这样处理问题会更方便
        int n = board.size();
        // 二维压缩成一维就是 n^2 个元素
        vector<int> conv(n*n, 0);
        int size = conv.size();
        int k = 0, row = 0;
        for(int i = n-1; i >= 0; --i)
        {
            // 如果当前 row 是偶数行，那么我们把开头设置为第 0 列
            // 否则，把开头设置为第 n-1 列
            int j = row % 2 ? n-1 : 0;
            // 当 j 超出当前列第范围时就结束当前列的循环
            while(j != -1 && j != n)
            {
                conv[k++] = board[i][j];
                // 注意，如果 row 为偶数，那么我们往右走
                // 否则，我们往左走
                j += row % 2 ? -1 : 1;    
            }
            ++row;
        }
        q.push(1);
        // 之后我们只需要对这个一维的数组进行处理即可
        bool reached = false;
        // 记录走出的最少投掷次数
        int steps = 0;
        while(!q.empty() && !reached)
        {
            // 我们按步数分层，按层进行遍历即可
            int n = q.size();
            for(int i = 0; i < n; ++i)
            {
                // 取出一个位置
                int idx = q.front();
                // 尝试进行扩散
                for(int k = 1; k < 7 && idx+k <= size; ++k)
                {
                    // 尝试走出下一步
                    int nxt = idx+k;
                    // 如果遇到一个格子的值非 -1，那么就把 nxt 修改为那个格子的值
                    if(conv[nxt-1] != -1)
                    {
                        nxt = conv[nxt-1];
                    }
                    // 最后，如果这个格子已经被探查过了，我们不再进一步探查
                    if(memo.find(nxt) != memo.end())
                    {
                        continue;
                    }
                    // 没探查过，我们就把它加入到队列中
                    // 但是注意，如果这个格子是终点，我们不加入队列，而是修改 reached 标记，并退出循环
                    if(nxt == size)
                    {
                        reached = true;
                        break;
                    }
                    q.push(nxt);
                    memo.insert(nxt);
                }
                // 探查完了一个结点，我们弹出一个即可
                q.pop();
            }
            ++steps;
        }
        return reached ? steps : -1;
    }
};

/*

[[2,-1,-1,-1,-1],
 [-1,-1,-1,-1,-1],
 [-1,-1,-1,-1,-1],
 [-1,-1,-1,-1,-1],
 [-1,-1,-1,-1,-1]
]

*/