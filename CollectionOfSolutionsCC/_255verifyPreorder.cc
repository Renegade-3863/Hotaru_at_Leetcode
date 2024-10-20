#include "Solution.h"

bool Leetcode201_300::Solution::verifyPreorder(vector<int>& preorder)
{
    // 遇到二叉树类问题，首要的切入点就是递归，因为二叉树天然具有递归性质，这就使得所有和它有关的问题都自然地具备了递归的特性
    // 定义这样的递归函数：bool isPreorder(i, j) 代表 preorder 的 [i, j] 区间中的值是否满足一个前序序列
    function<bool(int, int)> isPreorder = [&](int l, int r) -> bool
    {
        // 递归问题的基本情况：如果这个数组的左边界等于或大于右边界，那么这个区间要么有一个元素，要么没有元素，此时一定满足一个前序序列的条件
        if(l >= r)
        {
            return true;
        }
        // 否则，我们考虑如何切分这个长度大于一的区间
        // 根据前序序列的基本特性，我们可以进行这样的检查：
        // 首先，我们假定这个序列的第一个元素就是这个序列代表的二叉树的根结点(这是前序遍历的基本性质)
        // 之后，我们从第二个元素开始检查，检查到第一个大于第一个元素 (下标l) 的数组下标 i
        // 根据前序遍历的属性，我们知道，preorder[l+1, i-1] 就是我们目前能明确的左子树范围 (假设它是一个前序序列)
        // 之后，preorder[i, r] 就一定是一这个根结点的右子树
        // 还没完，我们找出了第一个连续的满足小于 preorder[l] 的子序列后，还必须确保后面的这个 preorder[i, r] 是完全大于 preorder[l] 的
        // 如果后面还有拐点，那么很显然我们没法声称这个序列是一个前序遍历序列
        // 明确了这个思路，代码就好写了
        // 先找第一个连续的满足小于 preorder[l] 的区间
        int k = l+1;
        for(; k <= r; ++k)
        {
            // 遇到第一个不小于 preorder[l] 的元素，就必须退出了
            if(preorder[k] >= preorder[l])
            {
                break;
            }
        }
        int nxtR = k-1;
        // 验证后面的区间是否是完全大于 preorder[l] 的
        for(; k <= r; ++k)
        {
            // 一旦找到一个不大于 preorder[l] 的，我们就可以明确这个子序列完全不是一个前序序列了，直接返回 false 即可
            if(preorder[k] <= preorder[l])
            {
                return false;
            }
        }
        // 当前层面上看，这个根结点 preorder[l] 是满足前序关系的，不过我们还需要递归地判断两个子树是否是前序序列
        return isPreorder(l+1, nxtR) && isPreorder(nxtR+1, r);
    };
    // 对函数进行调用即可
    return isPreorder(0, preorder.size()-1);
}