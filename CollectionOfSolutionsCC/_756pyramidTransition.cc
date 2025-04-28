#include "Solution.h"

bool Leetcode701_800::Soltuion::pyramidTransition(string bottom, vector<string>& allowed)
{
    // 简单的想法是按层进行处理
    // 基于当前行作为 "底行"，尝试往上构建三角形
    // 直到 "底行" 不再拥有可以往上进行三角形构建的足够的积木为止
    // 这种思路基本上决定了本题使用的方案：BFS
    queue<string> q;
    // 我们需要一种高效的查询允许的字符串的结构，转储成哈希结构
    unordered_map<string, unordered_set<char>> hAllowed;
    for(const auto& allow : allowed)
    {
        // 我们记录采用下面的结构：
        // [两字符前缀 p] : {c1, c2, ...}
        // 代表以 p 为前缀的元素，后面可以添加 c1, c2, ... 等元素
        hAllowed[allow.substr(0, 2)].insert(allow[2]);
    }
    q.push(bottom);
    // 注意，我们需要记录 bottom 的初始长度，后续进行层更新时，只有那些长度等于 len-1 的新层可以被添加到队列中等待下一步处理
    int len = bottom.size();
    // backtrack 函数，接受一个样板字符串，以及上面定义的这个 len 变量（用于判断 "下一层" 字符串的合法性）
    // 返回一个字符串数组，这个数组中保存所有可能生成的 "下一层"
    // idx 代表当前 board 中前缀串的下标，path 代表当前回溯的状态信息
    function<void(vector<string>&, const string&, string&, int, int)> backtrack = [&](vector<string>& res, const string& board, string& path, int len, int idx) -> void
    {
        // path 是路径字符串，用于深入回溯树
        // 先定义一个回溯结尾
        if(idx == board.size()-1)
        {
            // idx == board.size()-1，说明当前已经完整遍历了所有可能的前缀，我们可以返回 res 作为 board 所有可能产生的下一层结果了
            return;
        }
        // 否则，我们取出 board.substr(idx, 2) 这个前缀串
        // 并在 hAllowed 中进行搜索，取出所有可能的字符拼接到 path 中
        string prefix = board.substr(idx, 2);
        for(const auto& suffix : hAllowed[prefix])
        {
            path.push_back(suffix);
            // 另一个回溯的中间结尾是：如果 path.size() == len-1，那么说明我们已经成功构造出了一个新的层可能
            // 把这个结果添加到 res 中，同时不要进一步递归
            if(path.size() == len-1)
            {
                res.push_back(path);
                // 直接在这里回溯，不要深入递归了
                path = path.substr(0, path.size()-1);
                continue;
            }
            // 之后是递归步
            backtrack(res, board, path, len, idx+1);
            // 回溯
            path = path.substr(0, path.size()-1);
        }
        // 遍历完成，结束函数即可
    };
    // 填写完成，接下来我们可以按层对 cur 进行遍历
    // 注意退出条件，如果当前要处理的 "下一层" 长度不足 1 了，也说明我们的处理可以结束了
    while(!q.empty() && len >= 1)
    {
        // 按层进行遍历
        int n = q.size();
        // 存储所有已经添加过的 "下一层" 内容，防止重复添加
        unordered_set<string> visited;
        for(int i = 0; i < n; ++i)
        {
            // 用一个 tmp 来保存结果
            // 取出 "当前层" 状态字符串
            auto& str = q.front();
            // 每次遍历相邻的两个字符组成的前缀，检查 hAllowed 结构中是否有可以组合的结果
            vector<string> res;
            string path;
            // 这里对 str 的处理比较复杂，我们可能需要一个额外的类似 backtrack 的函数来进行处理
            // 回到上面定义一下这个函数  
            backtrack(res, str, path, len, 0);
            // 处理完成，res 中就保存了所有可能的下一层结果
            for(const auto& s : res)
            {
                if(visited.count(s))
                {
                    continue;
                }
                visited.insert(s);
                // 可行的结果，压入队列中等待下一层处理
                q.push(s);
            }
            q.pop();
        }
        --len;
    }
    // 如果 len == 0，说明我们可以拿到一个合法的三角形
    // 否则说明不可能
    return len == 0;
}