#include "Solution.h"

struct status
{
    string board;
    string hand;
    status(string _board, string _hand) : board(_board), hand(_hand) {}
};
// 采用仿函数对 status 的哈希函数和等价函数进行重载
// status 的哈希函数
struct hashFunc
{
    size_t operator() (const status& a) const 
    {
        auto hasher = hash<string>();
        // 采用最简单的哈希值计算方法即可
        return hasher(a.board) ^ hasher(a.hand);
    }
};
// status 的等价函数
struct equalFunc
{
    bool operator() (const status& a, const status& b) const
    {
        // 同时比较，两个维度均相等的状态才是等价的
        return a.board == b.board && a.hand == b.hand;
    }
};
int Leetcode401_500::Soltuion::findMinStep(string board, string hand)
{
    // 看到 "最少" 两个字就不难想到这题本质是 BFS 了
    // 我们思考这样一个问题：如何一步一步地 "游玩" 这个游戏？
    // 我们需要定义这样一个 "状态量"：
    /*
        struct status
        {
            string board;   // board 代表的是此状态下桌面剩下的球的集合
            string hand;    // hand 代表的是此状态下手上还持有的球的集合
        };
    */
    // 使用 BFS 通常需要一个队列来保存状态信息，本题我们也用一个队列来保存一组指向 status 对象的指针
    queue<status*> q;
    // 哈希集合 memo，用于记录已经探查过的 status 状态，防止重复添加到队列中
    unordered_set<status, hashFunc, equalFunc> memo;
    // 把最开始的状态做成一个对象，把对应的指针存到队列 q 中
    // 注意内存泄漏问题
    status* cur = new status(board, hand);
    q.push(cur);
    memo.insert(status(board, hand));
    // 这里使用了官解的调用函数，特此做下引用声明
    function<string(const string&)> evaluate = [&](const string& board) -> string
    {
        string res;
        vector<pair<char, int>> st;
        
        for (auto c : board) {
            while (!st.empty() && c != st.back().first && st.back().second >= 3) {
                st.pop_back();
            }
            if (st.empty() || c != st.back().first) {
                st.push_back({c,1});
            } else {
                st.back().second++;
            }
        }
        if (!st.empty() && st.back().second >= 3) {
            st.pop_back();
        }
        for (int i = 0; i < st.size(); ++i) {
            for (int j = 0; j < st[i].second; ++j) {
                res.push_back(st[i].first);
            }
        }
        return res;
    };
    int step = 0;
    while(!q.empty())
    {
        int n = q.size();
        // 走一步
        ++step;
        for(int k = 0; k < n; ++k)
        {
            // 最外面是基本的 BFS 模版，当队列中没有需要进一步探查的状态时，我们就可以结束 BFS 遍历了
            // 思考一下如何进行 BFS 探查
            // 首先我们肯定要取出队头的一个状态，同时注意：最朴素的 BFS 遍历一定会导致很多重复状态的遍历，所以我们需要一种剪枝的策略，防止重复添加和检查相同的状态
            // 因为状态包含两个维度的信息：board 和 hand，所以我们应该需要一个 pair 的哈希表，或者，我们可以直接重载一下 status 的哈希函数，之后直接用 unordered_set 即可
            // 这里采用重载 status 哈希函数的做法
            // 先获取一个队头的状态
            status* cur = q.front();
            // 对这个状态的下一状态进行枚举
            // 基本枚举逻辑为：从 hand 中取出一个球
            // 内层循环枚举把这个球插入到 board 中哪个位置上
            int lenH = cur->hand.size(), lenB = cur->board.size();
            for(int i = 0; i < lenH; ++i)
            {
                // 按照官解的思路做出的剪枝1
                // 如果当前选择的球的颜色和前一个球相同，那么不用重复检查了
                if(i > 0 && cur->hand[i] == cur->hand[i-1])
                {
                    continue;
                }
                // 内层循环枚举插入的下标
                // 注意可以尾接，所以 lenB 也要考虑到
                for(int j = 0; j <= lenB; ++j)
                {
                    // 按照官解的思路做出的剪枝2
                    // 如果存在一组连续相同颜色的球，那么我们只在这组序列的开头尝试插入，其它位置不考虑了
                    if(j > 0 && cur->board[j-1] == cur->hand[i])
                    {
                        continue;
                    }
                    // 按照官解的思路做出的剪枝3
                    // 
                    bool choose = false;
                    if(j < lenB && cur->board[j] == cur->hand[i])
                    {
                        choose = true;
                    }
                    if(j > 0 && j < lenB && cur->board[j-1] == cur->board[j] && cur->board[j] != cur->hand[i])
                    {
                        choose = true;
                    }
                    if(!choose)
                    {
                        continue;
                    }
                    // 我们需要一个调用函数，给定插入位置 j，原串 board，以及插入到球颜色 cur->hand[i]，需要一个类似循环的调用方法来判断插入后的最终结果字符串
                    // 假设定义函数名为 evaluate
                    // 我们在循环外进行一下定义
                    string newBoard = evaluate(cur->board.substr(0, j)+cur->hand[i]+cur->board.substr(j));
                    // 删掉 hand[i] 这个字符
                    string newHand = cur->hand.substr(0, i)+cur->hand.substr(i+1);
                    // 如果此时 newBoard 的长度变成了 0，那么说明我们已经完成了操作，可以返回最少的步数了
                    if(newBoard.size() == 0)
                    {
                        return step;
                    }
                    status nxtStatus = status(newBoard, newHand);
                    // 注意防止重复添加，我们使用 memo 检查这个 [newBoard, newHand] 对是否添加过
                    if(!memo.count(nxtStatus))
                    {
                        q.push(new status(newBoard, newHand));
                        memo.insert(nxtStatus);
                    }
                }
            }
            // 弹出刚刚检查的对象，之后 unique_ptr 会自动进行内存清理
            q.pop();
            // 利用 cur 释放内存
            delete cur;
        }
    }
    return -1;
}