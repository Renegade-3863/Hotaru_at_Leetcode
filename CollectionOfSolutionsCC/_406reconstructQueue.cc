#include "Solution.h"

vector<vector<int>> Leetcode401_500::Solution::reconstructQueue(vector<vector<int>>& people)
{
    // 本质是贪心算法
    // 我们考虑下面的事实：
    // 如果我们不限制每个人前面不低于他的人的个数，那么我们只需要对所有人按身从高高到低进行排序即可
    // 之后，考虑从左到右维护第二维的条件即可
    // 对于任何一个元素，它前面的元素都是不低于它的，后面的元素都是低于它的
    // 我们考虑应该把这个元素放到结果数组的哪一个位置上
    // 首先，它前面的所有不低于它的元素都已经放好了，那么我们要做的就是把这个元素放到它要求的 "K 个不低于它的元素" 后面的第一个空位上即可
    // 不过这里会发现我们少了一个限制条件
    // 如果两个人身高是相等的，那么我们可能会需要考虑一下是否应该按照第二维进行排序
    // 思考下面的事实：
    // 如果我们先放 K 值大的，那么会出现：后续身高相同的人有可能插到这个 K 值大的人前面，这样就破坏了前面这个 K 值更大的人 K 值的正确性
    // 所以我们不能先放 K 值大的人
    // 那么可以先放 K 值小的吗？
    // 显然是可以的：如果 K 值小的占据了一个空位，那么说明这个位置前面的、身高不低于它的值个数就是这个更小的 K 个
    // 而 K 值更大的那个元素，最多最多只能是小 k 值加一，那么它一定不会被放到 K 值小的元素前面！
    // 至此，元素添加的逻辑基本敲定
    // 我们总结一下：
    // 第一步是对整个数组进行排序
    // 优先按第一维进行降序排列，否则按照第二维进行升序排列
    // 排序之后按照上面说好的逻辑进行答案填写即可
    // 答案数组
    int n = people.size(); 
    vector<vector<int>> res;   
    vector<bool> added(n, false);
    sort(people.begin(), people.end(), [&](const vector<int>& a, const vector<int>& b) {
        return a[0] == b[0] ? a[1] < b[1] : a[0] > b[0];
    });
    // 之后考虑进行答案填写
    // 对于每一个元素，我们只需要保证在 res 中它前面有 person[1] 个元素即可，因为前面添加的一定都是满足 "不低于它" 的元素
    for(const vector<int>& person : people)
    {
        res.insert(res.begin() + person[1], person);
    }
    return res;
}