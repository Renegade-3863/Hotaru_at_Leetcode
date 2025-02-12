#include "Solution.h"

// 据评论区老哥的说法，字节考过这道题，而且本身也挺有思维价值的，是一道很不错的递归类问题
int Leetcode501_600::Soltuion::longestConsecutive(Leetcode501_600::TreeNode* root)
{
    // 搞一下简单的问题定义
    // 先观察题目的要求：
    // 简单来说，题目要求的就是：
    // 找出经过任何一个结点，并 (可能) 向两侧子树延伸的，最长的完全递增/完全递减的路径
    // 那么我们就不难发现下面的子问题定义
    // check(node, dir)
    // 解释：检查从 node 出发，并 (可能) 向两侧子树延伸的，dir == 1 -> 递增，dir == -1 -> 递减
    // 的最长路径长度
    function<int(TreeNode*, int)> check = [&](TreeNode* node, int dir) -> int
    {
        // 根据 dir，我们就可以自然地把递增/递减关系延续下去
        // 要检查这个子问题，那么我们就需要分别讨论往左和往右继续深入的子问题的解
        // 0 代表的是，从这个 node 结点出发，往左和往右走，最长的满足 dir 关系的路径的长度
        // 注意，路径的长度必须至少为 2，我们这里把 res 的初始值赋为 1，是因为在求解的过程中需要用到 node 本身的长度
        int res = 1;
        // 先考虑能不能往左走
        if(node->left && node->left->val-node->val == dir)
        {
            // 可以走，并且差值等于 dir (dir == 1 说明往左走满足递增条件，dir == -1 说明往左走满足递减条件)
            // 那么我们递归求解 node->left, dir 这个子问题
            res = max(res, 1+check(node->left, dir));
        }
        // 再考虑能不能往右走
        if(node->right && node->right->val-node->val == dir)
        {
            // 可以走，并且差值等于 dir (dir == 1 说明往右走满足递增条件，dir == -1 说明往右走满足递减条件)
            // 那么我们可以递归求解 node->right, dir 这个子问题
            res = max(res, 1+check(node->right, dir));
        }
        // 左右方向探查完成，我们就了解了往哪边走可以拿到最优的路径长度了，返回 res 即可
        return res;
    };
    // 之后要考虑的就是如何使用上面这个方法了
    // 我们无非需要考虑 "经过每个结点" 的结果，而不是 "从每个结点出发" 的结果
    // 所以这就是一个结点遍历+访问的问题了
    // 我们依然使用后序遍历的模版来处理问题
    // 注意，访问结点同样需要左右孩子的信息维持原样，所以本题也不能用 Morris 遍历
    stack<TreeNode*> stk;
    TreeNode* cur = root, * pre = nullptr;
    int ans = 0;
    while(cur || !stk.empty())
    {
        if(cur)
        {
            // 后序遍历，我们最后才访问 cur 结点，所以把 cur 压栈，并往左走
            stk.push(cur);
            cur = cur->left;
        }
        else
        {
            // 取出 stk 顶部存储的结点，考虑它的右子树是否已经访问完成
            cur = stk.top();
            if(!cur->right || pre == cur->right)
            {
                // 右子树为空/右子树已经访问完成，那么我们就可以对 cur 进行访问了
                // 别忘了修改 pre 的值
                pre = cur;
                // 访问需要做什么？
                // 我们要拿到的数据是：经过 cur 这个结点的最长递增/最长递减路径长度
                // 那么无非两种情况：
                // 1. 经过 cur，往左递减，往右递增 (即：从左往右递增)
                // 2. 经过 cur，往左递增，往右递减 (即：从右往左递增)
                // first 和 second 分别记录上面两种情况的最优解
                int first = 1, second = 1;
                // 左侧结点可访问，我们更新 1 和 2 情况的解
                if(cur->left)
                {
                    // 满足往左递减，那么我们需要检查 cur->left 往左最远递减可以走多远
                    // 再加上 cur 到 cur->left 这一步的结果
                    if(cur->left->val-cur->val == -1)
                    {
                        first += check(cur->left, -1);
                    }
                    if(cur->left->val-cur->val == 1)
                    {
                        second += check(cur->left, 1);
                    }
                }
                // 右侧结点可访问，我们更新 1 和 2 情况的解
                if(cur->right)
                {
                    // 满足往右递增，那么我们需要检查 cur->right 往右最远递增可以走多远
                    // 再加上 cur 到 cur->right 这一步的结果
                    if(cur->right->val-cur->val == 1)
                    {
                        first += check(cur->right, 1);
                    }
                    if(cur->right->val-cur->val == -1)
                    {
                        second += check(cur->right, -1);
                    }
                }
                // 访问完成，现在 first 和 second 中就存储了两种可能性的结果值
                // 我们把较大的那一个存储到 ans 中即可
                ans = max(ans, max(first, second));
                // 结束后，别忘了把 cur 置空！
                cur = nullptr;
                stk.pop();
            }
            // 否则，右子树还没被访问过，我们需要先访问右子树
            else
            {
                cur = cur->right;
            }
        }
    }
    // 遍历全部完成，返回 ans 即可
    return ans;
}

// 注意到，我们有可能在遍历过程中重复求解同样的子问题，所以可以针对这一现象存储一个记忆化哈希表
// 引入到 check 函数中即可
int longestConsecutive(TreeNode* root)
{
    // 搞一下简单的问题定义
    // 先观察题目的要求：
    // 简单来说，题目要求的就是：
    // 找出经过任何一个结点，并 (可能) 向两侧子树延伸的，最长的完全递增/完全递减的路径
    // 那么我们就不难发现下面的子问题定义
    // check(node, dir)
    // 解释：检查从 node 出发，并 (可能) 向两侧子树延伸的，dir == 1 -> 递增，dir == -1 -> 递减
    // 的最长路径长度
    // 我们用这样的方式对哈希表进行组织：
    // 一个指针作为 key，之后存储一个数值对
    // 代表这个 node 对应的 (dir == -1 结果和 dir == 1 结果)
    unordered_map<TreeNode*, pair<int, int>> memo;
    function<int(TreeNode*, int)> check = [&](TreeNode* node, int dir) -> int
    {
        if(memo.count(node))
        {
            if(dir == 1 && memo[node].second != 0)
            {
                // 已经计算过，返回记录的结果即可
                return memo[node].second;
            }
            if(dir == -1 && memo[node].first != 0)
            {
                return memo[node].first;
            }
        }
        // 根据 dir，我们就可以自然地把递增/递减关系延续下去
        // 要检查这个子问题，那么我们就需要分别讨论往左和往右继续深入的子问题的解
        // 0 代表的是，从这个 node 结点出发，往左和往右走，最长的满足 dir 关系的路径的长度
        // 注意，路径的长度必须至少为 2，我们这里把 res 的初始值赋为 1，是因为在求解的过程中需要用到 node 本身的长度
        int res = 1;
        // 先考虑能不能往左走
        if(node->left && node->left->val-node->val == dir)
        {
            // 可以走，并且差值等于 dir (dir == 1 说明往左走满足递增条件，dir == -1 说明往左走满足递减条件)
            // 那么我们递归求解 node->left, dir 这个子问题
            res = max(res, 1+check(node->left, dir));
        }
        // 再考虑能不能往右走
        if(node->right && node->right->val-node->val == dir)
        {
            // 可以走，并且差值等于 dir (dir == 1 说明往右走满足递增条件，dir == -1 说明往右走满足递减条件)
            // 那么我们可以递归求解 node->right, dir 这个子问题
            res = max(res, 1+check(node->right, dir));
        }
        // 左右方向探查完成，我们就了解了往哪边走可以拿到最优的路径长度了，返回 res 即可
        // 记录结果到哈希表中
        if(dir == -1)
        {
            memo[node].first = res;
        }
        else
        {
            memo[node].second = res;
        }
        return res;
    };
    // 之后要考虑的就是如何使用上面这个方法了
    // 我们无非需要考虑 "经过每个结点" 的结果，而不是 "从每个结点出发" 的结果
    // 所以这就是一个结点遍历+访问的问题了
    // 我们依然使用后序遍历的模版来处理问题
    // 注意，访问结点同样需要左右孩子的信息维持原样，所以本题也不能用 Morris 遍历
    stack<TreeNode*> stk;
    TreeNode* cur = root, * pre = nullptr;
    int ans = 0;
    while(cur || !stk.empty())
    {
        if(cur)
        {
            // 后序遍历，我们最后才访问 cur 结点，所以把 cur 压栈，并往左走
            stk.push(cur);
            cur = cur->left;
        }
        else
        {
            // 取出 stk 顶部存储的结点，考虑它的右子树是否已经访问完成
            cur = stk.top();
            if(!cur->right || pre == cur->right)
            {
                // 右子树为空/右子树已经访问完成，那么我们就可以对 cur 进行访问了
                // 别忘了修改 pre 的值
                pre = cur;
                // 访问需要做什么？
                // 我们要拿到的数据是：经过 cur 这个结点的最长递增/最长递减路径长度
                // 那么无非两种情况：
                // 1. 经过 cur，往左递减，往右递增 (即：从左往右递增)
                // 2. 经过 cur，往左递增，往右递减 (即：从右往左递增)
                // first 和 second 分别记录上面两种情况的最优解
                int first = 1, second = 1;
                // 左侧结点可访问，我们更新 1 和 2 情况的解
                if(cur->left)
                {
                    // 满足往左递减，那么我们需要检查 cur->left 往左最远递减可以走多远
                    // 再加上 cur 到 cur->left 这一步的结果
                    if(cur->left->val-cur->val == -1)
                    {
                        first += check(cur->left, -1);
                    }
                    if(cur->left->val-cur->val == 1)
                    {
                        second += check(cur->left, 1);
                    }
                }
                // 右侧结点可访问，我们更新 1 和 2 情况的解
                if(cur->right)
                {
                    // 满足往右递增，那么我们需要检查 cur->right 往右最远递增可以走多远
                    // 再加上 cur 到 cur->right 这一步的结果
                    if(cur->right->val-cur->val == 1)
                    {
                        first += check(cur->right, 1);
                    }
                    if(cur->right->val-cur->val == -1)
                    {
                        second += check(cur->right, -1);
                    }
                }
                // 访问完成，现在 first 和 second 中就存储了两种可能性的结果值
                // 我们把较大的那一个存储到 ans 中即可
                ans = max(ans, max(first, second));
                // 结束后，别忘了把 cur 置空！
                cur = nullptr;
                stk.pop();
            }
            // 否则，右子树还没被访问过，我们需要先访问右子树
            else
            {
                cur = cur->right;
            }
        }
    }
    // 遍历全部完成，返回 ans 即可
    return ans;
}