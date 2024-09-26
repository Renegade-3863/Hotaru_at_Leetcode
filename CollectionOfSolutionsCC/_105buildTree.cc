#include "Solution.h"

Leetcode101_200::TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)
{
    // 要求根据一棵树的前序和中序遍历序列构建出原本的二叉树
    // 本质是一道分治的题目，我们可以通过前序和中序遍历的特性来进行构造
    // 首先明确，前序遍历序列的首个元素一定是原树的根结点
    // 我们定义这样的一个递归的构造函数
    // TreeNode* build(vector<int>& preorder, int l1, int r1, vector<int>& inorder, int l2, int r2)
    // 意义是通过 preorder 的 [l1, r1] 之间的元素和 inorder 的 [l2, r2] 之间的元素构造出的二叉树的根结点
    function<TreeNode*(vector<int>&, int, int, vector<int>&, int, int)> build = [&](vector<int>& preorder, int l1, int r1, vector<int>& inorder, int l2, int r2) ->TreeNode*
    {
        // 序列中没有结点，就直接返回空结点
        if(l1 > r1)
        {
            return nullptr;
        }
        // 我们可以明确，这样构造出来的树的根结点就是前序序列的第一个元素，也就是 preorder[l1] 位置处的元素
        TreeNode* root = new TreeNode(preorder[l1]);
        // 之后，使用这个根结点的值对两个数组进行分割
        // 利用这个根结点的值对两个数组分别进行分割
        // 先对中序数组进行分割
        // 找出对应根结点在 inorder 序列中的下标
        int i = l2;
        for(; i <= r2; ++i)
        {
            if(inorder[i] == preorder[l1])
            {
                break;
            }
        }
        // 找到了中序序列中根结点的位置，就能计算出这课二叉树根结点左子树的大小和右子树的大小
        // 0 1 2 [3] 4 5
        // [3] 0 1 2 4 5
        int sizeLeft = i-l2;
        int sizeRight = r2-i;
        // 根据前序遍历的特性，左子树中的结点一定紧跟着根结点，聚集在序列的左侧
        // 因而可以根据从中序序列中找到的左子树大小，找出前序序列中对应元素的下标范围
        // 进而也就可以找出右子树对应的下标范围
        // 之后递归进行构造即可
        root->left = build(preorder, l1+1, l1+sizeLeft, inorder, l2, i-1);
        root->right = build(preorder, l1+sizeLeft+1, r1, inorder, i+1, r2);
        // 构造完成，直接返回结果即可
        return root;
    };
    // 进行函数调用即可
    return build(preorder, 0, preorder.size()-1, inorder, 0, inorder.size()-1);
}