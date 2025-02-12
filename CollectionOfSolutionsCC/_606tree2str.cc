#include "Solution.h"

string Leetcode601_700::Soltuion::tree2str(Leetcode601_700::TreeNode* root)
{
    // 又是一道比较明显的 DFS 函数类问题
    // 我们考虑设定一个子问题来处理树的转化问题：
    // 假设 dfs(node) 代表把 node 为根结点的子树转换成字符串的子过程
    // 实际上这个过程可以和本题的解答函数合并来写
    // 那么我们考虑如何处理这个子过程：
    // 首先，如果 node 为空，那么很明显我们可以直接返回一个空字符串，根据题意，这种空的子树不需要保留
    // 否则，node 非空，那么我们可以先把 node 中的元素提取出来，放到答案字符串 res 中
    // 之后是分开处理 node 的左右子树
    // 在处理左子树和右子树的开始前和结束后两个时间点，别忘了用左右括号把整个子字符串括起来
    if(!root)
    {
        return "";
    }
    string res;
    res += to_string(root->val);
    // 分开处理左右子树
    // 注意，我们需要区分左右子树，所以如果右子树非空，那么即使左子树为空，我们也要把括号加上
    if(root->left || root->right)
    {
        res.push_back('(');
        res += tree2str(root->left);
        res.push_back(')');
    }
    if(root->right)
    {
        res.push_back('(');
        res += tree2str(root->right);
        res.push_back(')');
    }
    // 处理完成，返回结果即可
    return res;
}