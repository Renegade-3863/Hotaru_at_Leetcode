#include "Solution.h"

vector<vector<string>> Leetcode601_700::Soltuion::printTree(Leetcode601_700::TreeNode* root)
{
    // 这实际上是一道模拟题
    // 我们首先计算出 root 的高度，定义为 height
    // 这可以通过 dfs 来完成
    function<int(TreeNode*)> dfs = [&](TreeNode* root) -> int
    {
        // 根据定义 (虽然挺难接受)，空树的高度为 -1
        if(!root)
        {
            return -1;
        }
        // 之后，检查 root 结点的左右子树高度，取更大值加个一作为结果返回
        return max(dfs(root->left), dfs(root->right))+1;
    };
    // 直接调用 dfs 函数，就能拿到 root 树的高度
    int height = dfs(root);
    // 根据 height 高度，我们可以初始化出最后的结果数组 res
    vector<vector<string>> res(height+1, vector<string>((1<<(height+1))-1, ""));
    // 之后就是按照题目要求的顺序，对树进行一轮新的 dfs 遍历，并根据每个遍历到的结点所在的行标和列标决定它左右孩子的位置
    // 把 node 以及它左右孩子中的所有结点值填入 res 中的函数 inputNodes
    // node 本身需要填入的位置是 res[r][c]
    function<void(TreeNode*, int, int)> inputNodes = [&](TreeNode* node, int r, int c)
    {
        // 如果 root 是 nullptr，那么无论 r 和 c 为什么值，都不用管了，直接返回
        if(!node)
        {
            return;
        }
        // root 非空
        // 首先填入 to_string(root->val)
        res[r][c] = to_string(node->val);
        // 之后根据 r 和 c 的值，递归地计算左右子结点应该填入的坐标，并递归填入它们所在的子树
        inputNodes(node->left, r+1, c-(pow(2, height-r-1)));
        inputNodes(node->right, r+1, c+(pow(2, height-r-1)));
        // 填写完成
    };
    // 初始，root 要填入的位置就是 (0, (n-1)/2)
    inputNodes(root, 0, (res[0].size()-1)>>1);
    return res;
}