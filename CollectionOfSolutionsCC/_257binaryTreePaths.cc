#include "Solution.h"

vector<string> Leetcode201_300::Solution::binaryTreePaths(Leetcode201_300::TreeNode* root)
{
    // 简单题简单做，本题要求找出所有路径，很明显是一道回溯类问题，我们只需要按照先左后右的顺序往一个路径字符串中添加数字即可
    if(!root)
    {
        return {};
    }
    // 初始化 path 为包括最上层的根结点值，这是为了统一字符串中箭头的添加逻辑
    string path = to_string(root->val);
    vector<string> res;
    if(!root->left && !root->right)
    {
        res.push_back(path);
        return res;
    }
    function<void(TreeNode*)> backtrack = [&](TreeNode* subRoot)
    {
        if(!subRoot->left && !subRoot->right)
        {
            // 找到了一个叶子结点，我们就可以添加当前这个路径数组了
            path += "->";
            string value = to_string(subRoot->val);
            path += value;
            res.push_back(path);
            path = path.substr(0, path.size()-value.size());
            path = path.substr(0, path.size()-2);
            return;
        }
        // 先添加一个箭头加当前结点的数值，然后分别向左向右深入递归
        path += "->";
        string value = to_string(subRoot->val);
        path += value;
        if(subRoot->left)
        {
            backtrack(subRoot->left);
        }
        if(subRoot->right)
        {
            backtrack(subRoot->right);
        }
        // 回溯
        path = path.substr(0, path.size()-value.size());
        path = path.substr(0, path.size()-2);
    };
    // 直接调用函数即可
    if(root->left)
    {
        backtrack(root->left);
    }
    if(root->right)
    {
        backtrack(root->right);
    }
    return res;
}

// 重构一下写法，第一版写得太丑陋了。。。
vector<string> binaryTreePaths(Leetcode201_300::TreeNode* root)
{
    // 不合法情况处理，如果 root 本身是空结点，直接返回空数组
    if(!root)
    {
        return {};
    }
    string path("");
    vector<string> res;
    function<void(TreeNode*)> backtrack = [&](TreeNode* subRoot)
    {
        // 回溯结束情况
        if(!subRoot->left && !subRoot->right)
        {
            res.push_back(path);
            return;
        }
        // 其它情况：
        // subRoot->left || subRoot->right
        // 递归步骤
        // 如果 subRoot->left，那么我们就可以往左递归
        if(subRoot->left)
        {
            path += "->";
            string value = to_string(subRoot->left->val);
            path += value;
            backtrack(subRoot->left);
            // 回溯
            path = path.substr(0, path.size()-value.size());
            path = path.substr(0, path.size()-2);
        }
        // 如果 subRoot->right，那么我们就可以往右递归
        if(subRoot->right)
        {
            path += "->";
            string value = to_string(subRoot->right->val);
            path += value;
            backtrack(subRoot->right);
            // 回溯
            path = path.substr(0, path.size()-value.size());
            path = path.substr(0, path.size()-2);
        }
    };
    // 注意，由于我们没有在回溯函数体内对根结点进行处理，需要先把根结点添加到 path 中
    path += to_string(root->val);
    backtrack(root);
    return res;
}