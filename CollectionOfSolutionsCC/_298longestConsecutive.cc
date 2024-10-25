#include "Solution.h"

// 第一版：纯 DFS，不加记忆化
int Leetcode201_300::Solution::longestConsecutive(TreeNode* root)
{
    // 还是那句话，二叉树的问题，无论怎么奇葩，一定总有一种用递归可以做的方法
    // 定义下面的子问题：
    // 从某个子结点为起点，往它的任意一个子树延伸，可以拿到的最长连续序列长度
    function<int(TreeNode*)> dfs = [&](TreeNode* subRoot) -> int
    {
        // 最小子问题：这个子结点是空的，那么我们直接返回 0 即可
        if(!subRoot)
        {
            return 0;
        }
        // 否则，为了减少递归次数，我们修改一下递归的次序
        // 初始的最长长度就是1，即只有这个结点的值本身
        int maximum = 1;
        // 先检查当前根结点和左孩子是否能够拼接成递增序列
        if(subRoot->left && subRoot->left->val - subRoot->val == 1)
        {
            // 能拼成，我们才递归检查左孩子
            maximum = max(maximum, 1+dfs(subRoot->left));
        }
        // 再检查当前结点和右孩子是否能够拼接成递增序列
        if(subRoot->right && subRoot->right->val - subRoot->val == 1)
        {
            maximum = max(maximum, 1+dfs(subRoot->right));
        }
        // 返回找到的最终结果
        return maximum;
    };
    // 通过任意一种遍历方法，遍历整棵二叉树，找出对于每一个结点的结果，记录到全局的结果中并返回即可
    int res = 0;
    // 我们依然可以用诸如 Morris 遍历的方法对二叉树进行遍历，别用传统迭代方法，太 low 了 (来自后期的嘲讽：你挖了个坑给自己埋了还在这楽呢)
    // 说明一下，这一题不适合用 Morris 遍历
    // 根本原因在于 Morris 遍历相当于修改了原二叉树的结构，换句话说，在遍历的过程中，这个图结构不再是一棵树了
    // 比如前驱结点在我们检查它的时候，右孩子甚至会往上指向它的祖辈结点
    // 这违背了本题的要求，所以这种方式是不可取的
    // 后面还是回归最基本的栈模拟的迭代遍历了。。。
    // TreeNode* cur = root;
    // while(cur)
    // {
    //     // 回忆：如果左孩子为空，此时我们直接对当前结点进行访问即可
    //     if(!cur->left)
    //     {
    //         res = max(res, dfs(cur));
    //         cout << cur->val << ": " << res << endl;
    //         // 访问完成，走到右孩子
    //         cur = cur->right;
    //     }
    //     // 否则，左孩子非空，我们需要检查它的直接前驱结点是否已经有指向它本身的右指针
    //     else
    //     {
    //         TreeNode* predecessor = cur->left;
    //         while(predecessor->right && predecessor->right != cur)
    //         {
    //             predecessor = predecessor->right;
    //         }
    //         if(!predecessor->right)
    //         {
    //             // 把 predecessor->right 指向 cur，表示前驱关系
    //             predecessor->right = cur;
    //             // 继续往左遍历左子树
    //             cur = cur->left;
    //         }
    //         // 如果 predecessor 通过右指针指回了 cur 结点，那么说明我们已经经历过了对 cur 结点的第一次访问
    //         // 此时直接复原 predecessor->right，并对 cur 进行访问即可
    //         else
    //         {
    //             predecessor->right = nullptr;
    //             res = max(res, dfs(cur));
    //             cout << cur->val << ": " << res << endl;
    //             // 继续往右遍历右子树
    //             cur = cur->right;
    //         }
    //     }   
    // }
    stack<TreeNode*> stk;
    TreeNode* cur = root;
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
            res = max(res, dfs(cur));
            stk.pop();
            cur = cur->right;
        }
    }
    // 迭代检查结束，我们可以直接返回结果
    return res;
}

// 第二版：DFS + 记忆化加速
int longestConsecutive(TreeNode* root)
{
    // 还是那句话，二叉树的问题，无论怎么奇葩，一定总有一种用递归可以做的方法
    // 定义下面的子问题：
    // 从某个子结点为起点，往它的任意一个子树延伸，可以拿到的最长连续序列长度
    // 添加一个记忆化哈希表
    unordered_map<TreeNode*, int> memo;
    function<int(TreeNode*)> dfs = [&](TreeNode* subRoot) -> int
    {
        // 最小子问题：这个子结点是空的，那么我们直接返回 0 即可
        if(!subRoot)
        {
            return 0;
        }
        // 记忆化步骤
        if(memo.find(subRoot) != memo.end())
        {
            return memo[subRoot];
        }
        // 否则，为了减少递归次数，我们修改一下递归的次序
        // 初始的最长长度就是1，即只有这个结点的值本身
        int maximum = 1;
        // 先检查当前根结点和左孩子是否能够拼接成递增序列
        if(subRoot->left && subRoot->left->val - subRoot->val == 1)
        {
            // 能拼成，我们才递归检查左孩子
            maximum = max(maximum, 1+dfs(subRoot->left));
        }
        // 再检查当前结点和右孩子是否能够拼接成递增序列
        if(subRoot->right && subRoot->right->val - subRoot->val == 1)
        {
            maximum = max(maximum, 1+dfs(subRoot->right));
        }
        // 返回找到的最终结果
        memo[subRoot] = maximum;
        return maximum;
    };
    // 通过任意一种遍历方法，遍历整棵二叉树，找出对于每一个结点的结果，记录到全局的结果中并返回即可
    int res = 0;
    stack<TreeNode*> stk;
    TreeNode* cur = root;
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
            res = max(res, dfs(cur));
            stk.pop();
            cur = cur->right;
        }
    }
    // 迭代检查结束，我们可以直接返回结果
    return res;
}