#include "Solution.h"

int Leetcode601_700::Soltuion::minStickers(vector<string>& stickers, string target)
{
    // 看完之后，我的第一反应就是背包问题 (这是可以说的吗。)
    // 其实特征挺明显的
    // 每个贴纸代表了一组字母集合 (产品)
    // 每种产品我们可以无限次选取
    // 要拿出构造出 target (背包容量) 的最少产品数
    // 这个架构基本上就可以确定是背包类问题了
    // 我们规定一种新的数据结构 info
    /*
    struct info
    {
        unordered<char, int> cnts;
    };
    */
    // 上面这种数据结构封装了一个哈希表，记录了一个贴纸中每种字母包含了几个
    // 这样，对 stickers 遍历过一次后，我们就能拿到一个 info 数组，之后把 target 再转成一个 info 结构对象
    // 之后，我们就可以用这个 info 数组，和 target 转储后的 info，来玩背包问题了
    // 定义这样的 dfs 函数
    // dfs(i, k) 代表用 [0, i] 这些 info，组合出 k 这个目标，所需的最少 info 个数
    // 那么如果 i == 0，结果就是完全用 info 来组合出 k 这个目标的总个数
    // 如果 k 所有所需的字母个数均非正，那么我们直接返回 0 即可
    struct info
    {
        unordered_map<char, int> cnts;
    };
    int n = stickers.size();
    vector<info> infos;
    // 遍历 stickers 数组，处理 infos 数组
    for(const auto& sticker : stickers)
    {   
        info newInfo;
        for(const auto& c : sticker)
        {
            ++(newInfo.cnts[c]);
        }
        infos.push_back(newInfo);
    }
    // 处理 target 字符串
    info targetInfo;
    for(const auto& c : target)
    {
        ++(targetInfo.cnts[c]);
    }
    // 处理完成后，我们定义一个 dfs 函数
    function<int(int, info)> dfs = [&](int i, info k) -> int
    {
        if(k.cnts.empty())
        {
            return 0;
        }
        // 如果 i == 0，那么我们只用 infos[0] 来构造 k 这个结果
        if(i == 0)
        {
            int ret = 0;
            // 遍历 k 中的每一种字符，尝试用 infos[0] 进行匹配
            for(const auto& [c, cnt] : k.cnts)
            {
                // c 这种字符在 infos[0] 中不存在，所以我们返回 0 即可，没法只用 infos[0] 构造出 k
                if(cnt == 0)
                {
                    continue;
                }
                if(infos[0].cnts.count(c) == 0)
                {
                    return -1;
                }
                // 否则，我们根据 cnt/infos[0].cnts[c] 的结果，来更新 ret
                // 一些数学处理：如果 cnt 不能整除 infos[0].cnts[c]，那么我们需要对除法结果+1
                ret = max(ret, cnt/infos[0].cnts[c]+(cnt%infos[0].cnts[c]>0));
            }
            // cout << "Returned" << endl;
            return ret;
        }
        // 其它为一般情况
        // 我们考虑 infos[i] 
        // 1. 完全不用
        // 那么 dfs(i, k) = dfs(i-1, k)
        // 2. 使用 infos[i]
        // 那么 dfs(i, k) = min(1+dfs(i-1, k-infos[i]), 2+dfs(i-1, k-2*infos[i]), ..., m+dfs(i-1, k-m*infos[i])))
        // 而 dfs(i, k-infos[i]) = min(dfs(i-1, k-infos[i]), 1+dfs(i-1, k-2*infos[i]), ..., (m-1)+dfs(i-1, k-m*infos[i])))
        // 所以 dfs(i, k) = min(dfs(i-1, k), dfs(i, k-infos[i]))
        // 明确了递推关系式，我们就可以开始处理了
        // int noUse = dfs(i-1, k);
        // 展开计算 k-infos[i]
        int time = 0;
        int use = INT_MAX;
        // info curInfo = k;
        while(true)
        {
            info newInfo;
            for(int j = 0; j < 26; ++j)
            {
                if(k.cnts['a'+j]-infos[i].cnts['a'+j]*time > 0)
                {
                    newInfo.cnts['a'+j] = k.cnts['a'+j]-infos[i].cnts['a'+j]*time;
                }
            }
            int tmp = dfs(i-1, newInfo);
            // tmp == -1，说明这种情况下使用 times 次 infos[i] 是没法成功构造出 k 的，我们跳过更新即可
            if(tmp != -1)
            {
               

                use = min(use, time+tmp);
            }
            // 退出循环条件为：
            // curInfo 对应 infos[i] 所有非零的维度上都是 0 
            bool exit = true;
            for(int j = 0; j < 26; ++j)
            {
                if(infos[i].cnts['a'+j] > 0 && newInfo.cnts['a'+j] > 0)
                {
                    exit = false;
                }
            }
            if(exit)
            {
                break;
            }
            ++time;
        }
        return use == INT_MAX ? -1 : use;
    };
    return dfs(n-1, targetInfo);
}

// 第二版：考虑加上记忆化
// 写到这里，我们会发现：没法通过正常格式记录 info 这种东西
// 不过考虑到它是一个长度最多为 26 的哈希表，我们可以考虑使用状态压缩法来记录这些信息
// 这里借用了一下微扰大佬的题解，稍微加了些注释，感觉数位 DP 的题目状态转移方程还是不好想。。
int minStickers(vector<string>& stickers, string target)
{
    int n = target.size();
    // 解释一下 dp 要这么长的原因
    // target 一共有 n 位字符
    // 我们规定 dp[111] 代表 target 的三个字符都被选中了，我们需要的最少 sticker 个数
    // dp[101] 代表 target 从左到右第二个字符还没有被选中时，我们需要的最少 sticker 数量
    vector<int> dp((1<<n), 0);
    queue<int> q;
    // 从 target 所有位都没有被选中的状态开始进行 BFS
    q.push(0);
    int step = 0;

    while(!q.empty())
    {
        // 记录开始状态
        int begin = q.front();
        q.pop();
        // 从当前状态开始，尝试填入一个 sticker，这个 sticker 可以是 stickers 中的任意一种
        for(auto sticker : stickers)
        {
            // 记录使用了这个 sticker 后，新的状态 state
            int state = begin;
            vector<int> cnt(26);
            for(auto c : sticker)
            {
                ++cnt[c-'a'];
            }
            // 对 target 中的每一个字符，尝试用 cnt 去匹配那些尚不是 1 的位
            for(int i = 0; i < n; ++i)
            {
                // 如果 cnt 中还有 target[i] 这个字符，同时 state 对应 i 这个下标上的字符还没被匹配成功
                // 那么就匹配一次，更新 cnt 和 state
                if(cnt[target[i]-'a'] && !(state & (1 << i)))
                {
                    state |= 1 << i;
                    cnt[target[i]-'a']--;
                }
            }
            // 如果 dp[state] 已经被计算过了，那么我们就不再重复流程，
            // 而 state == 0 是边界情况
            // 如果所有字符都没有被选中，我们对一个空字符串进行拼凑，只需要 0 张 sticker，所以此时也跳过计算即可
            if(dp[state] || state == 0)
            {
                continue;
            }
            q.push(state);
            dp[state] = dp[begin]+1;
            if(state == (1<<n)-1)
            {
                // 如果我们已经计算到了 n-1 位 1 这个状态
                // 说明我们已经找到了 target 中的元素都被选中的结果
                // 举例：
                // n == 4
                // 那么我们只要遍历到 (1<<4)-1，也就是 1111，就找到了最终的答案
                return dp[state];
            }
        }
    }
    // BFS 自然退出，找不到全 1 状态的结果，返回 -1 即可
    return -1;
}