#include "Solution.h"

// 基本可以说是线段树的模版题了
// 我们可以这样来实现这道题：
/*
    划定一个维护 [0, 1e9] 范围的线段树数组
    但是不难发现：1e9 是一个非常大的数字
    所以我们可能需要尝试用 "动态开点" 的方式来优化空间复杂度。。
    对于线段树本身的操作
    其它细节方法基本不变
    我们维护的线段树代表的是 [0, 1e9] 这个范围上对应区间的 "元素和" 属性
    之后，对应数组原本的元素
    如果下标 i 上面的元素没有被跟踪，那么对应的被维护值就是 0
    否则，被跟踪了，那么对应的被维护值就是 1
    这样，对应区间上被监控着的区间长度，就是对应区间上值 1 的总和了
*/
Leetcode701_800::Soltuion::RangeModule::RangeModule()
{
    // 初始化过程中，我们直接构造一个根结点即可
    // 由于题目限定 1 <= left < right <= 10^9，所以我们新建一个这样的树即可
    this->root = buildTree(1, 1000000000, 0);
}
:RangeModule::addRange(int left, int right)
{
void Leetcode701_800::Soltuion:
    // 我们调用 update 对 [left, right-1] 上的元素进行处理
    update(this->root, left, right-1, 1);
}

bool Leetcode701_800::Soltuion::queryRange(int left, int right)
{
    // 只要该区间上所有元素均为 1，那么我们就可以返回 true，否则返回 false
    return query(this->root, left, right-1) == (right-left);
}

void Leetcode701_800::Soltuion::removeRange(int left, int right)
{
    update(this->root, left, right-1, -1);
}