#include "Solution.h"

vector<TreeNode*> findDuplicateSubtrees(Leetcode601_700::TreeNode* root)
{
    // 同一棵树中的子树结构进行检索
    // 我们可以考虑用树型 KMP，或者树型哈希算法
    // 本题并不适合用单纯的 DFS 来处理
    // 原因在于不好找出比较适合递推的子问题定义
    // 树型哈希，写过的肯定不想写第二遍，如果有兴趣的，可以自行尝试埃氏筛法求质数+设计哈希函数
    // 这里不再写了
    // KMP 同理
    // 我们这道题偷个懒，用一下语言自带的哈希表 (unordered_map) 来简化一下记录和检索流程
    // 基本的思路在于
    // 使用一个 DFS 函数，用固定的生成逻辑，对 root 的每一棵子树进行遍历，并把生成的，能准确表示子树结构的字符串保存到哈希表中
    // 如果出现了重复的结构字符串，那么就把根结点存储到结果数组中
    // 这是本题最简单好理解的解决方案了
    // memo 哈希表，记录所有遍历过的子树结构字符串，以及见过的次数 cnt
    unordered_map<string, int> memo;
    // 最后返回的结果数组 res
    vector<TreeNode*> res;
    function<string(TreeNode*)> dfs = [&](TreeNode* node) -> string
    {
        // 我们用这样的逻辑对 node 子树进行遍历
        // 1. 如果 node 为 nullptr
        // 我们什么也不做，直接返回 "()" 即可，题目并不把空树视为可为重复子树的情况
        if(!node)
        {
            return "()";
        }
        // info 记录 node 子树的结构
        string info = "";
        // 2. node 非空
        // 那么我们可以把 node->val 先保存到 info 中
        info += to_string(node->val);
        // 注意，特征字符串需要对每个结点进行区分，否则会遇到 170/175 这种情况而出错
        // 之后，递归地保存左右子树的结果
        info.push_back(',');
        info += dfs(node->left);
        info.push_back(',');
        info += dfs(node->right);
        // 之后找 memo 中是否已经记录过这个 info 结构，有的话，把 node 记录到 res 数组中
        // 注意，出现第三次及以后就不再考虑了
        if(memo.count(info) && memo[info] == 1)
        {
            res.push_back(node);
        }
        // 记录 info 出现过一次
        ++memo[info];
        // 返回结果
        return info;
    };
    // 我们只调用 dfs(root) 即可
    dfs(root);
    return res;
}