#include "Solution.h"

Leetcode101_200::TreeNode* Leetcode101_200::Solution::buildTree(vector<int>& inorder, vector<int>& postorder)
{
    // 和 105 题完全一致的思路，只不过是前序和后序在性质上反过来罢了
    /*
        返回值为使用 inorder 的 l1 到 r1 之间的元素(从集合的角度讲和 postorder 的 l2 到 r2 之间的元素是相同的)构成的子树的根结点
    */
    function<TreeNode*(vector<int>&, int, int, vector<int>&, int, int)> build = [&](vector<int>& inorder, int l1, int r1, vector<int>& postorder, int l2, int r2) ->TreeNode*
    {
        // 递归终止条件：l1 > r1 (等价于 l2 > r2)
        if(l1 > r1)
        {
            return nullptr;
        }
        // 注意到，后序遍历序列的最后一个遍历到的结点是树的根结点
        TreeNode* root = new TreeNode(postorder[r2]);
        // 递归构造两棵子树，不过需要先计算两边的新结点边界值
        // 首先计算中序遍历序列的新边界，这个边界需要通过根结点的下标确定
        // 通过一轮遍历确定根结点下标
        int i = l1;
        for(; i <= r1; ++i)
        {
            if(inorder[i] == postorder[r2])
            {
                break;
            }
        }
        // 结束后 i 指向的就是根结点在中序序列中的下标
        // 根据这个值对新的中序边界和新的后序边界进行计算进行计算
        // 分别计算出左右子树的结点个数
        int sizeLeft = i-l1, sizeRight = r1-i;
        // 依据后序遍历的性质计算出新的后序边界和中序边界
        root->left = build(inorder, l1, l1+sizeLeft-1, postorder, l2, l2+sizeLeft-1);
        root->right = build(inorder, l1+sizeLeft+1, r1, postorder, r2-sizeRight, r2-1);
        return root;
    };
    return build(inorder, 0, inorder.size()-1, postorder, 0, postorder.size()-1);
}
