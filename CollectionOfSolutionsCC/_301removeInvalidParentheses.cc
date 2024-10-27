#include "Solution.h"

// 简单的暴力 BFS，不带记忆化，TLE
vector<string> Leetcode301_400::Solution::removeInvalidParentheses(string s)
{
    // 最简单的方法就是直接回溯
    // 为了减少不必要的过度深入，我们可以应用类似 BFS 的方法来进行算法优化
    // 定义一个 BFS 的合法标记 (全局变量)
    // 回顾 BFS 的定义，我们可以发现：如果我们在某一层中找到了一个合法的括号删除方案，那么删除这一层对应的括号次数就是我们最少需要删除的括号数了
    // 下一层就不用再深入了
    bool valid = false;
    unordered_set<string> res;
    // 返回值为 str 是否是一个合法的括号字符串
    function<bool(const string&)> isValid = [&](const string& str) -> bool
    {
        // 我们可以使用下面的方法代替传统的栈方法
        // 定义一个变量，记录当前检查过的左侧子串中，还未匹配的左括号个数
        int left = 0, n = str.size();
        for(int i = 0; i < n; ++i)
        {
            if(str[i] == '(')
            {
                ++left;
            }
            else if(str[i] == ')')
            {
                // 如果是一个右括号，我们需要判断这个右括号左侧是否还有未匹配的左括号
                if(--left < 0)
                {
                    return false;
                }
            }
        }
        // 检查完成，我们还需要确保剩下未匹配的左括号是零个
        return left == 0;
    };
    queue<string> q;
    // 添加第一个字符串到队列中
    q.push(s);
    while(!q.empty())
    {
        int m = q.size();
        for(int k = 0; k < m; ++k)
        {
            // 取出当前字符串
            string cur = q.front();
            cout << cur << endl;
            q.pop();
            if(isValid(cur))
            {
                valid = true;
                res.insert(cur);
            }
            int n = cur.size();
            // 检查所有可能的下一层字符串
            for(int i = 0; i < n && !valid; ++i)
            {
                // 不是括号的字符不能删
                if(cur[i] != '(' && cur[i] != ')')
                {
                    continue;
                }
                // 保存一个临时字符串，用于后续的恢复
                string tmp = cur;
                cur = cur.substr(0, i)+cur.substr(i+1);
                q.push(cur);
                // 恢复
                cur = tmp;
            }
        }
        if(valid)
        {
            break;
        }
    }
    vector<string> ans;
    for(const string& str: res)
    {
        ans.push_back(str);
    }
    return ans;
}

// 简单考察一下上面超时的原因：
// 我们在添加下一层字符串到队列中的时候，是 "无条件" 的
// 这就意味着，如果下一层修改出来的字符串有多个一样的，我们也会把它们全部添加到队列中，这就造成了多次重复搜索
// 因而我们可能会需要用一个记忆化哈希集合来避免这种同长度相同字符串的重复添加
// 简单添加一个记忆体即可
vector<string> removeInvalidParentheses(string s)
{
    // 最简单的方法就是直接回溯
    // 为了减少不必要的过度深入，我们可以应用类似 BFS 的方法来进行算法优化
    // 定义一个 BFS 的合法标记 (全局变量)
    // 回顾 BFS 的定义，我们可以发现：如果我们在某一层中找到了一个合法的括号删除方案，那么删除这一层对应的括号次数就是我们最少需要删除的括号数了
    // 下一层就不用再深入了
    bool valid = false;
    unordered_set<string> res;
    // 返回值为 str 是否是一个合法的括号字符串
    function<bool(const string&)> isValid = [&](const string& str) -> bool
    {
        // 我们可以使用下面的方法代替传统的栈方法
        // 定义一个变量，记录当前检查过的左侧子串中，还未匹配的左括号个数
        int left = 0, n = str.size();
        for(int i = 0; i < n; ++i)
        {
            if(str[i] == '(')
            {
                ++left;
            }
            else if(str[i] == ')')
            {
                // 如果是一个右括号，我们需要判断这个右括号左侧是否还有未匹配的左括号
                if(--left < 0)
                {
                    return false;
                }
            }
        }
        // 检查完成，我们还需要确保剩下未匹配的左括号是零个
        return left == 0;
    };
    queue<string> q;
    // 额外记录一个哈希集合，记录所有添加过的字符串
    unordered_set<string> added;
    // 添加第一个字符串到队列中
    q.push(s);
    while(!q.empty())
    {
        int m = q.size();
        // 清空哈希集合，防止过多占用内存
        added = unordered_set<string>();
        for(int k = 0; k < m; ++k)
        {
            // 取出当前字符串
            string cur = q.front();
            // cout << cur << endl;
            q.pop();
            if(isValid(cur))
            {
                valid = true;
                res.insert(cur);
            }
            int n = cur.size();
            // 检查所有可能的下一层字符串
            for(int i = 0; i < n && !valid; ++i)
            {
                // 不是括号的字符不能删
                if(cur[i] != '(' && cur[i] != ')')
                {
                    continue;
                }
                // 保存一个临时字符串，用于后续的恢复
                string tmp = cur;
                cur = cur.substr(0, i)+cur.substr(i+1);
                if(added.find(cur) == added.end())
                {
                    // 记录这个字符串 "添加过了"
                    added.insert(cur);
                    q.push(cur);
                }
                // 恢复
                cur = tmp;
            }
        }
        if(valid)
        {
            break;
        }
    }
    vector<string> ans;
    for(const string& str: res)
    {
        ans.push_back(str);
    }
    return ans;
}