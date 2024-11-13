#include "Solution.h"

// 来自后期的嘲讽：还搁这装B，觉得你会滑窗了不起是吧。。。
// 后期总结，这题不具有滑窗需要的 "可省" 性质，用不了滑窗
// 原因在于：
// 我们要的是最长的子串，所以
// 无法确保滑窗移动左指针的时候，后面的 right 指针不会用到前面这些 left 值。。。
int Leetcode301_400::Solution::longestSubstring(string s, int k)
{
    // 熟悉的子串，不变的滑窗
    // 几乎可以直接套滑窗的模版做了。。
    // 我们依然是划定两个边界变量 left 和 right
    // 之后考虑：
    // 求出以每个 right 下标处字符结尾的、最长的、其中所有字符出现次数都不少于 K 个的子串长度
    // 真拗口。。。
    int left = -1, n = s.size();
    // 两个信息结构，一个代表当前窗口中满足 "出现次数不少于 K 个的字符个数"
    // 一个代表当前窗口中的总字符种类数
    int valid = 0, cnt = 0;
    // 记录当前窗口中每种字符的个数
    unordered_map<char, int> cnts;
    int res = 0;
    // 只有当 valid == cnt 的时候，我们才能更新对应的最长长度
    for(int right = 0; right < n; ++right)
    {
        // 每次记录当前这个 s[right] 的信息
        if(cnts.find(s[right]) == cnts.end())
        {
            ++cnt;
        }
        // 如果有一个新的满足条件的字符出现，我们对 valid 进行更新
        if(++cnts[s[right]] == k)
        {
            ++valid;
        }
        // 更新完成
        // 根据是否满足 cnt == valid 进行更新
        // 如果 cnt > valid，说明我们不能进行更新，需要右移 left 指针
        while(cnt > valid)
        {
            // 如果清除这个字符前，它出现的次数正好等于 k，那么清除后，我们会少一个 valid
            if(cnts[s[left+1]] == k)
            {
                --valid;
            }
            --cnts[s[left+1]];
            // 每移动一次 left 指针，清除对应字符的记录
            if(cnts[s[left+1]] == 0)
            {
                // 清光了一种字符，修改总字符种类数
                --cnt;
            }
            ++left;
        }
        // 保证的是，这里 cnt 一定是不大于 valid 的
        // 我们直接更新答案即可
        res = max(res, right-left);
    }
    return res;
}

// 重新思考本题，由于不具备有效的使用滑动窗口的性质，我们需要另寻他法
// 解决一道题最重要的是切入点，切忌使用惯性思维来做题，虽然有些时候这样确实可行
// 上面的事后分析已经解释过了：不能用传统滑窗的本质原因在于：
// 我们不知道移动左指针是否是可以毫无顾忌的
// 因为有可能我们会丢失一个之后的右端点会用到的某种字符
// 所以，我们可以思考对滑动窗口求解的子问题进行一定程度的限制：
// 具体地：我们每一轮滑动窗口，只求解窗口中字符种类数固定的、每种字符出现次数不少于 k 次、结束于 right 处的最长子串
// 那么此时，我们在移动左指针的时候，就可以确保，只有窗口内的字符种类数不小于我们规定的值，并且每种字符出现的次数都至少有 k 次的时候，我们才能够对结果进行更新
// 具体流程放到代码中解释
int longestSubstring(string s, int k)
{
    // 记录最终的答案
    int res = 0, n = s.size();
    // 枚举窗口中最多可以出现的字符种类数，最少1种，最多26种
    // 注意剪枝，如果 cur 种类数甚至都比我们的 s 长度长了，那么显然不可能有结果
    for(int cur = 1; cur <= 26 && cur <= n; ++cur)
    {
        // 窗口左边界
        int left = -1;
        // 记录窗口内出现的总字符种类数，valid 代表满足了条件的字符种类数
        int cnt = 0, valid = 0;
        unordered_map<char, int> cnts;
        for(int right = 0; right < n; ++right)
        {
            // 对于每一个字符，记录这个字符的出现
            if(cnts.find(s[right]) == cnts.end())
            {
                ++cnt;
            }
            if(++cnts[s[right]] == k)
            {
                ++valid;
            }
            // 只有当 cnt 不少于 cur 的时候，我们才考虑往右移动 left 指针，否则，连最基本的种类数都没法保证，我们更没法进行更新了
            // 注意到我们上面这种新求解模式的好处了没？
            // 我们在往右移动左指针的时候，只可能减少 cnt，而不会增大 cnt
            // 换句话说，我们每次移动左指针的时候，都能确保对于当前的 right 以及它右侧所有的 right 可选值，这个 left 处的字符不可能会被用到了
            // 也就是说：后面的 right，如果要一路覆盖到这个 left，那么字符种类数只可能更多 (大于 cur 种)，也就没办法考虑 valid 的问题了
            // 所以我们每次移动 left 都可以是毫无顾忌的
            while(cnt > cur)
            {   
                cout << cnt << endl;
                if(cnts[s[left+1]] == k)
                {
                    --valid;
                }
                if(--cnts[s[left+1]] == 0)
                {
                    // 别忘了删掉这条记录，否则会出问题
                    cnts.erase(s[left+1]);
                    --cnt;
                }
                ++left;
            }
            // 保证每次到这里，都有 cnt <= cur，valid 不确定
            // 所以只有当 valid == cnt == cur 的时候，我们才能更新结果
            if(valid == cnt && cnt == cur)
            {
                res = max(res, right-left);
            }
        }
    }
    return res;
}