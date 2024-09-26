#include "Solution.h"

Leetcode101_200::TreeNode* sortedArrayToBST(vector<int>& nums)
{
    // 题目要求我们把这个有序序列转换成一棵平衡二叉搜索树
    // 可以利用这样的一个性质：
    // 有序数组的中间值一定可以作为它所代表的 平衡BST 的根结点
    // 接下来我们只需要递归地用两半的结点继续按上面的逻辑构造平衡二叉树即可
    // 定义一个递归的回调函数
    // dfs(i, j)：返回值为使用 nums[i] 到 nums[j] 之间的元素构造出的平衡二叉树的根结点
    function<TreeNode*(int, int)> dfs = [&](int i, int j) ->TreeNode* 
    {
        // 如果集合中没有元素，返回一棵空树，空树也是一棵平衡BST
        if(i > j)
        {
            return nullptr;
        }
        // 否则，我们需要选用中间结点的值作为当前这棵平衡BST的根结点
        int mid = ((j-i)>>1)+i;
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = dfs(i, mid-1);
        root->right = dfs(mid+1, j);
        return root;
    };
    return dfs(0, nums.size()-1);
}