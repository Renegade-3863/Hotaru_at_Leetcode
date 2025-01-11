#include "Solution.h"

vector<int> Leetcode501_600::Soltuion::findFrequentTreeSum(Leetcode501_600::TreeNode* root)
{
    // 读懂题很关键
    // 题目的要求在于：计算以 root 为根的树中，所有子树的元素和，把其中元素和出现频率最高的那些放到答案数组中返回
    // 那么我们可以采用哈希表和递归计算来实现
    // 采用类似后序遍历的方式来实现，(这也是树型哈希的基本逻辑)
    // 定义 dfs(root) 代表 "以 root 为根结点的子树的元素和"
    // 按后序遍历的方式来遍历整棵树，使用一个哈希表 memo 来记录对应元素和的出现次数
    // 同时，res 作为答案数组
    vector<int> res;
    unordered_map<int, int> memo;
    function<int(TreeNode*)> dfs = [&](TreeNode* root) -> int
    {
        // 定义基本情况：
        // 如果结点为空，那么直接返回 0 即可
        if(!root)
        {
            return 0;
        }
        // 后序遍历，先检查左右孩子的结果，再计算最终结果
        return dfs(root->left)+dfs(root->right)+root->val;
    };
    // 外层也需要一个后序遍历，防止重复计算
    stack<TreeNode*> stk;
    // 一个变量，记录当前出现次数最多的元素和出现的次数
    int maxCnt = 0;
    // 我们复习一下后序遍历的非递归实现
    // pre 记录 "上一次访问的结点指针"
    TreeNode* cur = root, * pre = nullptr;
    while(!stk.empty() || cur)
    {
        if(cur)
        {
            // 先往左走，不直接进行访问
            stk.push(cur);
            cur = cur->left;
        }
        else
        {
            // 获取栈顶的元素，这个结点也不一定可以现在被访问，我们需要明确 pre 是否就是 cur->right，或者 cur->right 为空结点
            // 否则不能访问，只能先访问右孩子，同时不能弹出栈顶结点！！
            cur = stk.top();
            if(!cur->right || pre == cur->right)
            {
                // 可以访问，进行访问
                int cnt = dfs(cur);
                if(++memo[cnt] > maxCnt)
                {
                    maxCnt = memo[cnt];
                }
                // 出栈 
                stk.pop();
                // 修改 pre 指针，维护定义
                pre = cur;
                // cur 置空
                cur = nullptr;
            }
            // 否则，不能访问，我们需要先访问右结点
            else
            {
                cur = cur->right;
            }
        }
    }
    // 遍历完成，我们现在在 memo 中记录了所有 "元素和" 出现的各自次数
    for(const auto& m : memo)
    {
        if(m.second == maxCnt)
        {
            res.push_back(m.first);
        }
    }
    return res;
}