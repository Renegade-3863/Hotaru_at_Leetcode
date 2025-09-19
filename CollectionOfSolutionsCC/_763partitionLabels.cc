#include "Solution.h"

vector<int> Leetcode701_800::Solution::partitionLabels(string s)
{
    // 挺明显的贪心类问题，问题在于切入点
    // 我们可以这样来对问题进行转换：
    // 每种字符都有第一次出现和最后一次出现的区间范围
    // 根据题意，我们必须让某种字符的所有出现下标都被囊括在同一个子串区间中
    // 那么我们预处理出上面这种范围的信息后，就知道每种字符至少应该
    // 举个例子：
    // ababcbacadefgdehijhklij
    // 我们可以处理出：
    // [a: {0, 8}], [b: {1, 5}], [c: {4, 7}], [d: {9, 13}]
    // [e: {10, 14}], [f: {11, 11}], [g: {12, 12}], [h: {15, 18}]
    // [i: {16, 21}], [j: {17, 17}], [k: {19, 19}], [l: {20, 20}]
    // 我们可以注意到，a 这个范围，必须和 b 以及 c 合并到一起，因为 [0, 8] 和 [1, 5] 以及 [4, 7] 都有交集
    // 之后，从 d 开始，开头位置就超过了 9，所以它们都不需要和 a 合并到一个集合中了
    // 我们接着处理 d
    // 我们会发现：d、e、f 以及 g 都是有交集的
    // 所以我们不得不把它们四种字符合并到一个子串中
    // 之后处理 h，我们会发现，从 h 到 l，这些字符都是有交集的，所以我们也不得不把它们合并成一个子串
    // 总结一下，我们可以归纳出下面的逻辑：
    // 把所有上面这样的区间值按照第一次出现的下标进行排序
    // 然后维护一个 "当前在维护的区间" 的左右边界
    // 如果当前看到的新区间的左区间和 "当前在维护的区间" 的右边界有交集，那么我们就不得不把它也合并到当前区间中
    // 同时更新 "当前在维护的区间" 的右边界
    // 而如果当前看到的新区间的左区间和 "当前在维护的区间" 的右边界没有交集，那么我们就可以把新区间作为一个新的 "当前在维护的区间"
    // 重复上面的流程，直到处理完整个数组
    // 首先第一步，我们处理这个区间信息表
    unordered_map<char, int> visited;
    int n = s.size();
    // 重载一下比较函数，用仿函数的方式进行
    vector<pair<int, int>> info;
    for(int i = 0; i < n; ++i)
    {
        if(visited.find(s[i]) == visited.end())
        {
            visited[s[i]] = info.size();
            info.emplace_back(i, i);
        }
        // 已有对应信息对，更新结束信息值即可
        else
        {
            info[visited[s[i]]].second = i;
        }
    }
    sort(info.begin(), info.end(), [&](const pair<int, int>& a, const pair<int, int>& b) -> bool {
        return a.first <= b.first;
    });
    // for(const auto& p : info)
    // {
    //     cout << p.first << ", " << p.second << endl;
    // }
    // 处理完成，我们之后用 info 进行处理即可
    // last 用于标识 "当前在维护的区间的右端点"
    // 初始时，默认从 -1 开始，这样能保证我们新建出第一个区间
    // start 用于记录每一个维护区间的开头，这个值用于更新 ans 数组
    int start = -1, last = -1;
    vector<int> ans;
    for(const auto& p : info)
    {
        if(last >= p.first)
        {
            // 有交集，那么我们更新 last，并进行合并
            last = max(last, p.second);
        }
        // 否则，没有交集，我们可以更新 last 为 p 的结束位置，新建一个维护区间
        else
        {
            if(last != -1)
            {
                ans.push_back(last-start+1);
            }
            start = p.first;
            last = p.second;
        }
    }
    if(last != -1)
    {
        ans.push_back(last-start+1);
    }
    return ans;
}