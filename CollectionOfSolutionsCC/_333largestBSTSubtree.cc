#include "Solution.h"

// 不加任何优化，先暴力搞出来 =^=
int Leetcode301_400::Solution::largestBSTSubtree(Leetcode301_400::TreeNode* root)
{
    // 题目要求我们找出一个二叉树中最大的满足 BST 性质的子树(最大意思就是结点个数最多)
    // 题目要求我们提供一个 O(n) 时间复杂度的算法，不难想到应该是想让我们用拓扑式的 DP 来解题
    // 所以我们先从 DFS 入手
    // 考虑子问题定义：
    // dfs(node) 代表以 node 为根结点的最大可行 BST 的大小
    // 如何进行子问题递推？
    // 我们可以检查左右子树的最大合法 BST 大小
    // 说是检查最大合法 BST 大小，其实只有两种返回结果：
    // 要么不含合法 BST，要么有合法 BST，就是以 node 为根的子树的总大小
    // 我们可以这样检查：
    // 立碑：这里的 nt 判断方法是哪个 nt 想出来的。。。
    // 如果左子树和右子树都是合法的 BST，并且左孩子结点 left、node、以及右孩子结点 right 的大小关系满足：
    // left->val < node->val < right->val 
    // 订正：判断一个根结点和两个子树是否构成 BST 关系，我们需要知道左子树的最大结点和右子树的最小结点的值，而不是单单获取它们的根结点值。。。
    // 那么我们就可以返回以 node 为根结点的子树总大小作为答案
    // 否则，任何其它情况下，我们都返回 -1 代表没有合法的 BST 即可
    // 定义递归的子问题函数
    function<int(TreeNode*)> dfs = [&](TreeNode* node) -> int
    {
        // 最小的子问题：node 是一个空根结点，此时我们直接返回 0 即可
        if(!node)
        {
            return 0;
        }
        // 其它情况下，我们先检查左右孩子，再检查三个结点的关系
        int left = dfs(node->left);
        int right = dfs(node->right);
        // 任何一棵子树不是合法的 BST，我们都只能声明以 node 为根结点的子树不是 BST
        if(left < 0 || right < 0)
        {
            return -1;
        }
        // 第一步：检查根结点的值是否大于左子树中的最大值
        TreeNode* predecessor = node->left;
        while(predecessor && predecessor->right)
        {
            predecessor = predecessor->right;
        }
        // 检查前驱结点是否存在，并且值小于 node->val
        if(predecessor && predecessor->val >= node->val)
        {
            return -1;
        }
        // 第二步：检查根结点的值是否小于右子树中的最小值
        TreeNode* successor = node->right;
        while(successor && successor->left)
        {
            successor = successor->left;
        }
        if(successor && successor->val <= node->val)
        {
            return -1;
        }
        // 其它情况下，是合法的 BST，返回 left+right+1 即可
        return left+right+1;
    };
    // 对二叉树进行遍历，对每个结点调用上面的函数，保存最大的那个结果即可
    // 这里我们用后序遍历
    TreeNode* cur = root;
    stack<TreeNode*> stk;
    TreeNode* pre = nullptr;
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
            // 后序遍历，我们需要检查上一次访问的结点是不是 cur 的右孩子结点
            if(!cur->right || pre == cur->right)
            {
                // 此时我们可以访问 cur 结点
                res = max(res, dfs(cur));
                // 访问结束后，把 cur 置空，不能继续访问右孩子了
                // 维护 pre 的语义
                pre = cur;
                stk.pop();
                cur = nullptr;
            }
            // 否则，我们还没检查右子树，需要访问右子树
            else
            {
                cur = cur->right;
            }
        }
    }
    // 返回结果即可
    return res;
}

// 第二步：考虑如何应用记忆化进行加速
int largestBSTSubtree(Leetcode301_400::TreeNode* root)
{
    // 题目要求我们找出一个二叉树中最大的满足 BST 性质的子树(最大意思就是结点个数最多)
    // 题目要求我们提供一个 O(n) 时间复杂度的算法，不难想到应该是想让我们用拓扑式的 DP 来解题
    // 所以我们先从 DFS 入手
    // 考虑子问题定义：
    // dfs(node) 代表以 node 为根结点的最大可行 BST 的大小
    // 如何进行子问题递推？
    // 我们可以检查左右子树的最大合法 BST 大小
    // 说是检查最大合法 BST 大小，其实只有两种返回结果：
    // 要么不含合法 BST，要么有合法 BST，就是以 node 为根的子树的总大小
    // 我们可以这样检查：
    // 立碑：这里的 nt 判断方法是哪个 nt 想出来的。。。
    // 如果左子树和右子树都是合法的 BST，并且左孩子结点 left、node、以及右孩子结点 right 的大小关系满足：
    // left->val < node->val < right->val 
    // 订正：判断一个根结点和两个子树是否构成 BST 关系，我们需要知道左子树的最大结点和右子树的最小结点的值，而不是单单获取它们的根结点值。。。
    // 那么我们就可以返回以 node 为根结点的子树总大小作为答案
    // 否则，任何其它情况下，我们都返回 -1 代表没有合法的 BST 即可
    // 定义递归的子问题函数
    // 检查有哪些数据可能是需要记忆的
    // 首先是每个结点的前驱和后继值
    // 其次是 dfs 的结果
    // 我们分别进行记忆化即可
    // 记忆每个结点的前驱
    // 记忆前驱值的哈希表
    unordered_map<TreeNode*, TreeNode*> memoPre;
    // 记忆后继值的哈希表
    unordered_map<TreeNode*, TreeNode*> memoSuc;
    // 记忆 dfs 结果
    unordered_map<TreeNode*, int> memo;
    function<int(TreeNode*)> dfs = [&](TreeNode* node) -> int
    {
        if(memo.find(node) != memo.end())
        {
            return memo[node];
        }
        // 最小的子问题：node 是一个空根结点，此时我们直接返回 0 即可
        if(!node)
        {
            return 0;
        }
        // 其它情况下，我们先检查左右孩子，再检查三个结点的关系
        int left = dfs(node->left);
        int right = dfs(node->right);
        // 任何一棵子树不是合法的 BST，我们都只能声明以 node 为根结点的子树不是 BST
        if(left < 0 || right < 0)
        {
            return -1;
        }
        // 第一步：检查根结点的值是否大于左子树中的最大值
        // 因为我们找出前驱后继的过程是同步的，所以只要前驱记录了，那么后继就一定也有了
        if(memoPre.find(node) != memoPre.end())
        {
            // 那么我们直接在这里进行判断即可
            if(memoPre[node] && memoPre[node]->val >= node->val)
            {
                return -1;
            }
            if(memoSuc[node] && memoSuc[node]->val <= node->val)
            {
                return -1;
            }
            // 否则，直接返回结果
            memo[node] = left+right+1;
            return memo[node];
        }
        TreeNode* predecessor = node->left;
        while(predecessor && predecessor->right)
        {
            predecessor = predecessor->right;
        }
        // 检查前驱结点是否存在，并且值小于 node->val
        if(predecessor && predecessor->val >= node->val)
        {
            return -1;
        }
        // 第二步：检查根结点的值是否小于右子树中的最小值
        TreeNode* successor = node->right;
        while(successor && successor->left)
        {
            successor = successor->left;
        }
        if(successor && successor->val <= node->val)
        {
            return -1;
        }
        // 其它情况下，是合法的 BST，返回 left+right+1 即可
        memo[node] = left+right+1;
        return memo[node];
    };
    // 对二叉树进行遍历，对每个结点调用上面的函数，保存最大的那个结果即可
    // 这里我们用后序遍历
    TreeNode* cur = root;
    stack<TreeNode*> stk;
    TreeNode* pre = nullptr;
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
            // 后序遍历，我们需要检查上一次访问的结点是不是 cur 的右孩子结点
            if(!cur->right || pre == cur->right)
            {
                // 此时我们可以访问 cur 结点
                res = max(res, dfs(cur));
                // 访问结束后，把 cur 置空，不能继续访问右孩子了
                // 维护 pre 的语义
                pre = cur;
                stk.pop();
                cur = nullptr;
            }
            // 否则，我们还没检查右子树，需要访问右子树
            else
            {
                cur = cur->right;
            }
        }
    }
    // 返回结果即可
    return res;
}