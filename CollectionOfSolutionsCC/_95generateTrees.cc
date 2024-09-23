#include "Solution.h"

// 加上记忆化之后，整体的时空复杂度均超过几乎 100%，而且用记忆化避免了重复分配内存空间导致的内存泄漏型问题
vector<Leetcode1_100::TreeNode*> generateTrees(int n)
{
    // 前 100 题真的很多回溯类题目，本题又是一道回溯类的全情况题
    // 考虑如何进行有方法地枚举
    // 我们可以定义一种类似递归的结构，具体为一个函数，这个函数可以检出使用 [i, j] 中的所有元素构成的所有可能的二叉搜索树结果
    // 注意，本题必须要做记忆化，否则会被 new 关键字创建的无数重复结点填爆
    // 记忆化：
    // 用一个二维指针数组做记忆化，哈希表的话还需要重载对应的内置 find 函数，比较麻烦
    // 一个同一的代表 "还不存在解" 的地址数组
    vector<TreeNode*> nonExist = {new TreeNode(-1)};
    // 初始记忆表中所有结点都指向这个地址数组
    // 这个数组最后不需要进行清理，因为它内部存储的都是最终我们返回的 res 中存在的结点信息，留给调用者进行清理即可
    vector<vector<vector<TreeNode*>>> memo(n, vector<vector<TreeNode*>>(n, vector<TreeNode*>(nonExist)));
    function<vector<TreeNode*>(int, int)> dfs = [&](int i, int j) -> vector<TreeNode*>
    {
        if(i >= 1 && i <= n && j >= 1 && j <= n && memo[i-1][j-1] != nonExist)
        {
            return memo[i-1][j-1];
        }
        vector<TreeNode*> res;
        // 如果我们可选的结点集合为空，直接返回包含一个空结点的列表即可
        if(i > j)
        {
            // 这里必须要返回一个带有一个空结点的数组，不然下面的循环会出问题
            res.push_back(nullptr);
            return res;
        }
        // 从 [i, j] 中选择一个结点作为子树的根结点
        for(int k = i; k <= j; ++k)
        {
            vector<TreeNode*> leftPos = dfs(i, k-1);
            vector<TreeNode*> rightPos = dfs(k+1, j);
            // 现在 leftPos 中存储了所有的可以用 [i, k-1] 中的所有元素构成的可能的二叉搜索树结果
            // 现在 rightPos 中存储了所有的可以用 [k+1, j] 中的所有元素构成的可能的二叉搜索树结果
            // 注意，我们要构造的是二叉搜索树，因而我们需要进一步判断这两个数组中的根结点元素能不能接到这个根结点上
            // 不过又发现，我们在拆分的时候，k 左侧的子树用的都是小于 k 的值，同时 k 右侧的子树用的都是大于 k 的值
            // 这恰好和 二叉搜索树的定义不谋而合，所以我们就不用再进行判断了
            // 进行一个二维的组合循环
            for(int x = 0; x < leftPos.size(); ++x)
            {
                for(int y = 0; y < rightPos.size(); ++y)
                {
                    TreeNode* subRoot = new TreeNode(k);
                    subRoot->left = leftPos[x];
                    subRoot->right = rightPos[y];
                    res.push_back(subRoot);
                }
            }
        }
        // 记忆化
        memo[i-1][j-1] = res;
        // 返回结果
        return res;
    };
    // 调用函数即可
    vector<TreeNode*> ans = dfs(1, n);
    // 别忘了释放那个额外分配的内存
    delete nonExist[0];
    return ans;
}