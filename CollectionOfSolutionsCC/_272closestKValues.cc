#include "Solution.h"

vector<int> Leetcode201_300::Solution::closestKValues(Leetcode201_300::TreeNode* root, int target, int k)
{
    // 本题要求的目标本身并不具备任何二分性质
    // 因为只通过当前根结点的值和 target 的比较，我们完全无法确定哪一边会有这 k 个元素中的元素
    // 比如 subRoot->val > target，我们只能说右侧不一定会有和 target 距离在前 k 位中的元素，而完全不能说明右侧一定不存在这样的元素
    // 个人能想到的最好办法就是直接把这棵二叉树通过中序遍历转储到一个数组中，这样这个数组中的元素就有了有序的性质
    // 之后，通过二分的方法找到第一个不小于 target 的元素，从它向两侧进行扩散，找出这 k 个离 target 最近的元素即可
    // 对于中序遍历，我们可以用 Morris 遍历来实现 O(1) 空间复杂度的遍历模式
    // 存储中序遍历结果
    vector<int> seq;
    TreeNode* cur = root;
    while(cur)
    {
        // 没有左孩子，说明我们可以先访问这个结点，之后直接往右走
        if(!cur->left)
        {
            seq.push_back(cur->val);
            cur = cur->right;
        }
        // 否则，说明左孩子非空，我们需要先建立这个结点的直接前驱结点到它的联系指针，这可以利用前驱结点的右孩子指针实现(因为这个前驱的右孩子一开始一定是空指针)
        else
        {
            TreeNode* predecessor = cur->left;
            while(predecessor->right && predecessor->right != cur)
            {
                predecessor = predecessor->right;
            }
            // 两种退出循环的条件：
            // 1. 找到了空的右孩子，说明我们是第一次访问到这个前驱结点，那么我们就可以确定后面会深入到这个结点，故我们可以在它的右指针处记录 cur 这个后继结点的信息
            if(!predecessor->right)
            {
                // 指向处理完成后，我们就可以继续向左深入了
                predecessor->right = cur;
                cur = cur->left;
            }
            // 2. 前驱结点的右孩子已经指向了 cur 这个后继结点
            // 这说明我们已经是第二次通过这种方式找到这个前驱结点了，此时 cur 的左子树理应已经访问完毕，就可以对 cur 本身进行访问了
            // 不过注意，为了不破坏二叉搜索树原本的结构，我们这里还需要对指针进行还原
            else
            {
                predecessor->right = nullptr;
                seq.push_back(cur->val);
                // 访问完成，我们可以继续访问它的右子树了
                cur = cur->right;
            }
        }
    }
    // 循环处理完成，我们就拿到了原二叉树的有序序列
    // 在这个序列上应用二分查找，找出不小于 target 的第一个值
    int left = 0, right = seq.size()-1;
    // 这里默认的初始值是 right，是为了防止原数组中不存在不小于 target 的值
    // 如果不存在不小于 target 的值，那么 closest 可以代表最后一个小于 target 的值，下面的过程也都是 compatible 的
    int closest = right;
    while(left <= right)
    {
        int mid = ((right-left)>>1)+left;
        if(seq[mid] >= target)
        {
            closest = mid;
            right = mid-1;
        }
        else
        {
            left = mid+1;
        }
    }
    // 循环结束后，closest 就指向了 seq 中不小于 target 的第一个值的下标
    // 不过此时我们还需要检查一下：
    // 第一个不小于 target 的值
    // 和最后一个小于 target 的值
    // 哪一个更接近 target
    // 把更接近的那一个作为之后扩散的起点
    int start = closest;
    if(closest > 0 && abs(seq[closest-1]-target) < abs(seq[closest]-target))
    {
        start = closest-1;
    }
    // 之后依然是两个指针分别向左右两侧扩散，直到我们拿到了 k 个值为止
    vector<int> res;
    res.push_back(seq[start]);
    left = start-1; right = start+1;
    int cnt = 1;
    while(cnt++ < k)
    {
        if(left < 0)
        {
            res.push_back(seq[right++]);
        }
        else if(right >= seq.size())
        {
            res.push_back(seq[left--]);
        }
        else
        {
            if(abs(seq[left]-target) <= abs(seq[right]-target))
            {
                res.push_back(seq[left--]);
            }
            else
            {
                res.push_back(seq[right++]);
            }
        }
    }
    return res;
}