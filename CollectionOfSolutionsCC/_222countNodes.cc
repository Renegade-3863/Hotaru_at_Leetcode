#include "Solution.h"

int Leetcode201_300::Solution::countNodes(Leetcode201_300::TreeNode* root)
{
    // 本题自然可以通过诸如前中后序遍历的方式单纯地 O(n) 检出树的结点总数，不过我们可以尝试利用完全二叉树的特性
    // 完全二叉树具有下面这样的特性：
    // 无论它是不是一个满二叉树，那么它的基本组分中一定总会有多个满二叉树
    // 而对于满二叉树，我们可以省去遍历流程，直接通过这个满二叉树的层数计算出其内部的总结点个数
    // 假设该满二叉树的深度为 h
    // 那么其中的总结点个数就是 2^h-1
    // 那么我们只需要找出一种方案来判断当前完全二叉树是不是满二叉树即可
    // 这可以通过分别向左和向右不断深入到最后一层，之后判断两侧找出的树高是否相等来完成
    // 如果根结点为空，我们可以直接返回 0
    if(!root)
    {
        return 0;
    }
    TreeNode* curLeft = root, * curRight = root;
    int leftHeight = 0;
    while(curLeft)
    {
        ++leftHeight;
        curLeft = curLeft->left;
    }
    int rightHeight = 0;
    while(curRight)
    {
        ++rightHeight;
        curRight = curRight->right;
    }
    // 检查两侧检出的高度值，如果相等，那么就是一棵满二叉树，就直接数学计算
    if(leftHeight == rightHeight)
    {
        return (1<<leftHeight)-1;
    }
    // 否则，正常通过递归计算两侧子树的结点和加上当前根结点
    return countNodes(root->left) + countNodes(root->right) + 1;
}