#include "Solution.h"

int Leetcode101_200::Solution::minDepth(Leetcode101_200::TreeNode* root)
{
    // 要求找出一棵二叉树的最小深度
    // 还是那句话，二叉树无非两种思路：递归和迭代，其中递归大概率更简单
    // 尝试定义递归函数
    // 发现这个大函数体本身就能当成是一个递归函数体
    // 直接利用即可
    // 递归结束条件
    // 空树的最小深度就是0
    if(!root)
    {
        return 0;
    }
    // 否则，递归检查两棵子树
    int minH = 1;
    int leftMin = minDepth(root->left), rightMin = minDepth(root->right);
    // 注意本题和最大深度问题的一个细节区别，本题由于我们要求的是从根结点到最近叶子结点到最短路径上的结点数量
    // 那么可能会出现某个根结点有且仅有一个孩子结点是空结点的情况，此时我们不能记根结点的最小深度为1
    // 因为它本身并不是一个叶子结点，因而此时取其左右子树更小的深度加一的方案会有问题(很显然为空的那一个子树的最小深度就是0)
    if(!root->left)
    {
        minH += rightMin;
        return minH;
    }
    if(!root->right)
    {
        minH += leftMin;
        return minH;
    }
    minH += min(leftMin, rightMin);
    return minH;
}