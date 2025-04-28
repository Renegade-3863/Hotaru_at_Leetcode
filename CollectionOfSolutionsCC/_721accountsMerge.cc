#include "Solution.h"

vector<vector<string>> Leetcode701_800::Soltuion::accountsMerge(vector<vector<string>>& accounts)
{
    // 分析一下题目中的具体要求：
    // 唯一能标定一个用户的是邮箱地址
    // 有相同邮箱地址的用户，即使不重名，也是同一个用户的，需要合并
    // 其实这道题第一想法就应该是并查集
    // 但是本题的索引不是简单的数字，而是 [账户，邮箱地址] 对
    // 思考一下并查集的基本模版：
    // 给定一串数字 [1, n]
    // 我们原先假定它们都各自独立成集
    // 之后给定一组边联系，用来连接这 n 个结点
    // 每次检查到一个联系
    // 那么我们就检查两个结点各自所在集合的 "代表"，也就是 representative
    // 如果二者的 representative 不同，那么就进行合并
    // 否则什么都不做
    // 回顾本题：我们会发现，题目并没有实际给我们这个联系集合
    // 实际上的联系关系保存在了每个 account 之间相同的邮箱账户中
    // 换句话说，如果两个账户有相同的邮箱，那么它们之间就有联系，或者说，同属于一个集合
    // 实际实现中，我们依然可以用序号来标记每一个 account 数据
    // 即：1 -> account[0], 2 -> account[1]
    // 这样的表示法更便于实际的代码编写
    // 我们需要先整体遍历一次整个 accounts 数组，检出这些联系
    // 注意：我们这里用数字代指 account 元素对
    // mapping 内存储的信息是：
    // 账户序号 -> 这个账户和哪些其它账户存在联系
    map<int, unordered_set<int>> mapping;
    // 注意，为了实现对 mapping 的填充，我们需要另一个哈希表来记录：
    // 邮箱 -> 属于的 account 序号 关系，定义为 memo
    unordered_map<string, int> memo;
    for(int i = 0; i < accounts.size(); ++i)
    {
        // 对于每个 account，我们检查 account[1] 到 account[account.size()-1] 这些元素，开头的名字不用管，只在第二轮合并的时候才会用到它
        for(int j = 1; j < accounts[i].size(); ++j)
        {
            if(memo.count(accounts[i][j]))
            {
                // 如果这个邮箱之前有记录过，属于某个序号代表的账号，那么我们把这个账号和那个账号建立联系即可
                mapping[memo[accounts[i][j]]].insert(i);
            }
            else
            {
                memo[accounts[i][j]] = i;
            }
        }
    }
    // 处理完成，注意上面的处理流程，我们实际上会忽略一些 "中间联系"，比如 1 和 2 有联系，同时 2 和 3 也有联系，那么我们只会记录 2 和 3 都与 1 有联系
    // 而不会记录 2 和 3 有联系，实际上，这种记录就足够了
    // 之后，我们考虑尝试用并查集来合并这些 account
    // 建立一个 sets 数组，这是并查集的模版数组，元素记录的是每个 account 所在的集合
    vector<int> sets(accounts.size(), 0);
    for(int i = 0; i < accounts.size(); ++i)
    {
        sets[i] = i;
    }
    // 之后就是并查集的 "并"，"查" 几个方法函数的定义
    // 检查 x 元素所在集合的 "代表" 元素
    function<int(int)> father = [&](int x) -> int
    {
        if(sets[x] != x)
        {
            // 如果当前元素的 sets 指针处不是它自己，证明它所属的集合的代表不是它，那么需要递归查找
            return father(sets[x]);
        }
        // 否则，说明 x 本身就是自己所在集合的代表，直接返回它即可
        return x;
    };
    // 用于检查 x 和 y 两个元素是否属于同一个集合，这个函数需要一个检查给定元素所属集合代表的 helper 方法
    function<void(int, int)> checkAndMerge = [&](int x, int y) -> void
    {
        int fx = father(x), fy = father(y);
        // 检查两个元素是否属于同一个集合，如果不属于，那么默认修改 fy 所在的指针，指向 fx
        if(fx != fy)
        {
            sets[fy] = fx;
        }
        // 否则，二者已经属于同一集合，我们什么也不用做了
    };
    // 最后，调用上面的方法函数，以及已经记录好的联系集合，对 sets 进行处理
    for(const auto& p : mapping)
    {
        // 每一个 p 都是一个 [int, unordered_set<int>] 信息对
        int x = p.first;
        for(const auto& y : p.second)
        {
            // 每一对 [x, y] 对，我们都尝试进行 merge 操作
            checkAndMerge(x, y);
        }
    }
    // 合并完成，我们遍历 sets，对于每一个 account，把它的邮箱合并到答案中即可
    // 如果当前 account 的序号 idx 在 sets 中满足 sets[idx] = idx，那么我们就找到了结果数组中新一行的开始
    // 我们往结果中添加一行即可
    // remapping 记录 sets 中的下标和最后答案数组下标的映射关系
    int idx = 0;
    // vector<vector<string>> res;
    map<int, set<string>> res;
    // 加一个哈希集合，用于去重
    unordered_set<string> dist;
    for(int i = 0; i < accounts.size(); ++i)
    {
        int fa = father(i);
        // 把 i 号 account 中的所有邮箱添加到 res 对应键值对中即可
        for(int j = 1; j < accounts[i].size(); ++j)
        {
            if(dist.count(accounts[i][j]))
            {
                continue;
            }
            dist.insert(accounts[i][j]);
            res[fa].insert(accounts[i][j]);
        }
    }
    vector<vector<string>> ans;
    for(const auto& p : res)
    {
        ans.push_back(vector<string>());
        for(const auto& str : p.second)
        {
            ans[ans.size()-1].push_back(str);
        }
        ans[ans.size()-1].insert(ans[ans.size()-1].begin(), accounts[p.first][0]);
    }
    return ans;
}