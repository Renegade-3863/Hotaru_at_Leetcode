#include "Solution.h"

// 被 Leetcode 的垃圾判题机制卡了二十分钟
// 它要求处理前后整棵树的基本结构不能被破坏
// 所以如果我们用 Morris 遍历，那么就必须对整棵树进行遍历，而不能中间返回
// 否则树原本的结构会被破坏
bool Leetcode601_700::Soltuion::findTarget(Leetcode601_700::TreeNode* root, int k)
{
    // 本质上和有序数组的两数之和没有什么区别
    // 可以用一个哈希表记录所有遍历过的数值，同时检查哈希表中是否存在 k-cur->val 这个值
    // 存在就返回 true，全部遍历完成，没有返回 true，就返回 false
    unordered_set<int> memo;
    bool res = false;
    // 用 Morris 遍历来省去栈空间
    TreeNode* cur = root;
    while(cur)
    {
        // 1. 如果 cur 有左孩子，那么我们可以先记录它的中序前驱结点和它的关系
        // 但是注意，我们在做的事先序遍历
        // 所以需要先访问
        if(cur->left)
        {
            TreeNode* predecessor = cur->left;
            // 不断往右走，直到访问到 cur，或者找到了 cur 的前驱为止
            while(predecessor->right && predecessor->right != cur)
            {
                predecessor = predecessor->right;
            }
            // 检查结束情况
            // 1. predecessor->right == nullptr
            // 那么说明我们是第一次访问 cur，也是第一次检查出 cur 的中序前驱结点
            // 所以我们需要把这个前驱关系记录到 predecessor 中
            if(!predecessor->right)
            {
                predecessor->right = cur;
                // 根据先序遍历的定义，我们需要先对它进行访问
                // 如果 memo 中已经记录过了 (k-cur->val)，那么需要返回 true
                if(memo.find(k-cur->val) != memo.end())
                {
                    res = true;
                }
                // 把当前值添加到 memo 中，代表我们见过这个值
                memo.insert(cur->val);
                // 访问完成，我们往左走
                cur = cur->left;
            }
            // 2. predecessor->right == cur
            // 这说明，我们是第二次访问 cur 结点了，之前第一次的时候一定已经访问过了 cur 结点
            // 所以我们可以恢复树原本的结构，同时往右走
            else
            {
                predecessor->right = nullptr;
                cur = cur->right;
            }
        }
        // cur->left 为空，那么我们直接对 cur->val 进行访问，并直接往右走即可
        else
        {
            if(memo.find(k-cur->val) != memo.end())
            {
                res = true;
            }
            memo.insert(cur->val);
            cur = cur->right;
        }
    }
    // 返回 res 即可
    return res;
}