#include "Solution.h"

// 第一版这个代码是错的，警示我们不要随随便便就用 Morris，它并不是万能的。。。
int Leetcode501_600::Soltuion::diameterOfBinaryTree(Leetcode501_600::TreeNode* root)
{
    // 二叉树类问题一般都可以用递归的方式来解决
    // 我们定义一个这样的子问题：
    // dfs(root) 为以 root 为根的树的最大深度
    // 我们考虑如何计算全局的最优结果
    // 可以按这样的定义求解：
    // 遍历每一个结点 node，求解 "从 node 到两侧子树最深结点到距离之和"
    // 我们可以按照 Morris 遍历加上记忆化来实现全局答案的求解
    TreeNode* cur = root;
    // res 记录最终结果
    int res = 0;
    // 定义 dfs 函数，用于求解上面提到的子问题
    // dfs 函数本身就是后序遍历，所以不会有重复求解的子问题
    // 但是我们后面的外层树遍历可能会涉及到重复的求解，我们可以用一个哈希表记录一下中间结果
    unordered_map<TreeNode*, int> memo;
    function<int(TreeNode*)> dfs = [&](TreeNode* root)  -> int
    {
        // 根结点为空，返回 0 即可
        if(!root)
        {
            return 0;
        }
        // 记忆化
        if(memo.count(root))
        {
            return memo[root];
        }
        // 先求解左右两侧子树的最大深度，把较大者加 1，作为当前子树的最大深度
        int left = dfs(root->left), right = dfs(root->right);
        memo[root] = max(left, right)+1;
        return memo[root];
    };
    while(cur)
    {
        if(cur->left)
        {
            // 左侧有子树，我们可以先检查是否记录的后继结点，如果记录过，说明左子树已经访问完成
            // 那么我们可以对 cur 本身进行访问，如果没有，那么我们需要先访问左子树，再访问 cur 结点
            TreeNode* predecessor = cur->left;
            while(predecessor->right && predecessor->right != cur)
            {
                predecessor = predecessor->right;
            }
            if(!predecessor->right)
            {
                // 说明后继关系还没有记录，这是第一次访问 cur
                // 我们记录后继关系，继续往左走即可
                predecessor->right = cur;
                cur = cur->left;
            }
            else 
            {
                // 我们的后继关系已经记录过了，那么我们可以对 cur 进行访问
                res = max(res, dfs(cur->left)+dfs(cur->right)+1);
                // 别忘了修正二叉树，防止破坏原本的结构
                predecessor->right = nullptr;
                // 往右走
                cur = cur->right;
            }
        }
        else
        {
            // 左子树为空，那么我们直接对 cur 结点进行访问即可
            // cur 结点的最大深度就是当前的最优解
            // 注意，dfs 函数假设了树原本的结构，所以我们这里没法直接调用 dfs，会出现死循环
            res = max(res, dfs(cur));
            // 往右走
            cur = cur->right;
        }
    } 
    // res 记录了答案，返回即可
    return res;
}

// 修正：用正常的，不修改树结构的栈遍历法来重新执行整棵树的遍历
TreeNode* diameterOfBinaryTree(TreeNode* root)
{
    // 定义 dfs 函数，用于求解上面提到的子问题
    // dfs 函数本身就是后序遍历，所以不会有重复求解的子问题
    // 但是我们后面的外层树遍历可能会涉及到重复的求解，我们可以用一个哈希表记录一下中间结果
    unordered_map<TreeNode*, int> memo;
    function<int(TreeNode*)> dfs = [&](TreeNode* root)  -> int
    {
        // 根结点为空，返回 0 即可
        if(!root)
        {
            return 0;
        }
        // 记忆化
        if(memo.count(root))
        {
            return memo[root];
        }
        // 先求解左右两侧子树的最大深度，把较大者加1，作为当前子树的最大深度
        int left = dfs(root->left), right = dfs(root->right);
        memo[root] = max(left, right)+1;
        return memo[root];
    };
    stack<TreeNode*> stk;
    TreeNode* cur = root, * pre = nullptr;
    int res = 0;
    while(cur || !stk.empty())
    {
        if(cur)
        {
            stk.push(cur);
            cur = cur->left;
        }
        else
        {
            cur = stk.top();
            // 采用后序遍历的方法，搭配记忆化数组防止重复子问题的求解
            if(!cur->right || cur->right == pre)
            {
                // 如果右子树为空，或者右子树的根结点刚刚被访问过，那么说明左右子树都被访问过了
                // 我们可以对 cur 结点本身进行访问
                res = max(res, dfs(cur->left)+dfs(cur->right));
                // 访问完成，我们把 cur 置空，以进行下一个结点的访问
                // 别忘了修改 pre 指针
                pre = cur;
                cur = nullptr;
                // 别忘了，结点访问完成，要把结点弹出栈
                stk.pop();
            }
            // 否则，右子树还没访问，我们往右访问右子树
            else
            {
                cur = cur->right;
                // 结点不用弹出，它还没被访问过
            }
        }
    }
    return res;
}