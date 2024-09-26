#include "Solution.h"

vector<vector<int>> Leetcode101_200::Solution::pathSum(Leetcode101_200::TreeNode* root, int targetSum)
{
    // 看到题目要求输出所有可能的路径，那么第一反应就应该是回溯暴搜了
    // 但是这题没有以前做过的一般回溯题那样的参数板用来添加数字，所以还是要回归传统的递归
    // 同上一题，还是用大函数本身作为回调函数
    // 如果子树为空，直接返回空集合，代表不存在这样的路径
    if(!root)
    {
        return {};
    }
    // 如果子树非空，那么先新建一个结果集合
    vector<vector<int>> res;
    // 此时如果结点 root 就是一个叶子结点，我们判断它的值是否等于 targetSum
    if(!root->left && !root->right)
    {
        if(root->val != targetSum)
        {
            return {};
        }
        // 如果 targetSum == root->val，那么我们可以往 res 中添加一个集合，这个集合只包含 root->val 一个元素
        res.push_back(vector<int>(1, root->val));
        // 结束后直接返回结果
        return res;
    }
    // 否则，这个结点不是一个叶子结点，需要进一步递归检查
    // 考虑这样的事实，如果我们能找出左子树中所有路径和为 targetSum-root->val 的路径集合，那么我们只需要把 root->val 的值添加到这些路径的开头即可
    vector<vector<int>> leftSub = pathSum(root->left, targetSum-root->val);
    vector<vector<int>> rightSub = pathSum(root->right, targetSum-root->val);
    // 先统计左子树的可能结果
    for(int i = 0; i < leftSub.size(); ++i)
    {
        res.insert(res.begin(), leftSub[i]);
        res[0].insert(res[0].begin(), root->val);
    }
    for(int i = 0; i < rightSub.size(); ++i)
    {
        res.insert(res.begin(), rightSub[i]);
        res[0].insert(res[0].begin(), root->val);   
    }
    return res;
}

// 总结，自己上面的写法有很大的效率问题，问题主要出在这两行代码上：
// res.insert(res.begin(), leftSub[i])
// &
// res.insert(res.begin(), rightSub[i])
// 由于它们会对一个子数组进行遍历和复制，这显然是很浪费时间和空间的一种行为
// 后面看了一下答案，发现其实还是复刻了传统的回溯类问题，只是这次记录的信息变成了路径中的结点信息
// 那么此时我们以记录过程信息为 "当前路径" 的方式来进行回溯
// 全局的答案数组
vector<vector<int>> res;
// 全局的中间路径数组，记录当前在访问的路径
vector<int> path;
vector<vector<int>> pathSum(Leetcode101_200::TreeNode* root, int targetSum)
{
    function<void(TreeNode*, int)> backtrack = [&](TreeNode* cur, int targetSum)
    {
        // 当前结点为空，无法继续往路径中添加路径
        if(!cur)
        {
            return;
        }
        // 记录当前路径结点
        path.push_back(cur->val);
        // 如果是一个叶子结点，那么要检查当前结点的值是否已经等于了剩下的 targetSum
        if(!cur->left && !cur->right)
        {
            if(cur->val == targetSum)
            {
                res.push_back(path);
                path.pop_back();
                return;
            }
        }
        // 否则，进行递归+回溯，递归步骤是把当前结点值添加到路径数组中，然后对左右两个子结点进行递归
        backtrack(cur->left, targetSum-cur->val);
        backtrack(cur->right, targetSum-cur->val);
        // 回溯，弹出当前结点值
        path.pop_back();
        return;
    };
    backtrack(root, targetSum);
    return res;
}