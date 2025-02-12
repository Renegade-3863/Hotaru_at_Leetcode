#include "Solution.h"

vector<int> Leetcode501_600::Soltuion::killProcess(vector<int>& pid, vector<int>& ppid, int kill)
{
    // 乍一看，感觉有点像一个数组形式表示的二叉树，但又不完全一样
    // 最傻的办法：
    // 不断遍历 ppid 数组，维护一个 "当前被杀掉的进程 id 哈希集合"
    // 每次，如果某个进程的父进程出现在了这个哈希表中，那么把这个进程作为 "新的被杀掉进程"，等待后续生成下一层的 "当前被杀掉进程哈希表"
    // 直到 "当前被杀掉的进程 id 哈希集合" 为空为止
    // 但这种不带任何预处理的方法很明显有很多 dummy 的遍历
    // 我们可以考虑加入一些预处理来加速算法
    // 我们可以先整体遍历一遍 pid，把每个进程存成一个哈希映射：
    // (pid, childPs)
    // 之后遍历 ppid，记录所有父进程和子进程的关系
    // 之后再进行题目要求的检索，就很方便了
    unordered_map<int, vector<int>> mapping;
    // 遍历 ppid 数组
    int n = ppid.size();
    for(int i = 0; i < n; ++i)
    {
        // 记录映射关系
        mapping[ppid[i]].push_back(pid[i]);
    }
    // 记录完成，我们可以根据 kill 开始反向工程，检查哪些子进程需要被删除，就像检查一棵树一样
    // 使用类似 BFS 的方法，我们用一个队列来处理
    queue<int> q;
    q.push(kill);
    vector<int> res;
    while(!q.empty())
    {
        // 按层来遍历
        n = q.size();
        for(int i = 0; i < n; ++i)
        {
            // 取出队头的一个 "被杀进程"
            int cur = q.front();
            res.push_back(cur);
            // 检查它的所有子进程
            for(const auto& subP : mapping[cur])
            {
                // 把这些子进程作为新的 "被杀进程" 压入队列
                q.push(subP);
            }
            // 弹出队头元素
            q.pop();
        }
    }
    return res;
}