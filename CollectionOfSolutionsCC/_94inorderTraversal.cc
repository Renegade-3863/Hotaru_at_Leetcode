#include "Solution.h"

vector<int> Leetcode1_100::Solution::inorderTraversal(Leetcode1_100::TreeNode* root)
{
    // 最最基础的二叉树问题，这中简单遍历的问题如果做不明白，建议先别刷了，回去看看算法基础再回来
    // 给出两种简单实现，一种递归，一种迭代
    // 建议掌握迭代，这种用栈的方式比直接用函数回调能省去一些函数调用的开销
    // 递归法
    function<void(vector<int>&, TreeNode*)> dfs = [&](vector<int>& res, TreeNode* node)
    {
        // 递归返回条件为：子树的根结点为空，此时不需要向 res 数组中添加任何数据，直接返回
        if(!node)
        {
            return;
        }
        // 递归深入
        // 根据中序的定义，先左，再中，最后右即可
        // 左
        dfs(res, node->left);
        // 中，这里要进行实际的访问，本题的访问操作就是记录 node 中的值
        res.push_back(node->val);
        // 右
        dfs(res, node->right);
    };
    // 直接调用即可
    vector<int> res;
    dfs(res, root);
    return res;
}

vector<int> inorderTraversal(Leetcode1_100::TreeNode* root)
{
    // 最最基础的二叉树问题，这中简单遍历的问题如果做不明白，建议先别刷了，回去看看算法基础再回来
    // 给出两种简单实现，一种递归，一种迭代
    // 建议掌握迭代，这种用栈的方式比直接用函数回调能省去一些函数调用的开销
    // 迭代法
    // 本质上是用栈来模拟递归的参数栈道方案
    // 本题递归恢复过程要用到的唯一参数就是一个 TreeNode 指针
    stack<TreeNode*> stk;
    // 定义一个 cur 参数，记录当前正在尝试处理的结点
    TreeNode* cur = root;
    vector<int> res;
    // 循环进行结点的处理，结束条件为：当前没有要处理的结点，并且存储记录中也没有还未处理完的任何结点
    while(cur || !stk.empty())
    {
        // 1. 如果当前手里还有未处理完的结点，就先处理这个结点
        if(cur)
        {
            // 要处理一个结点，首先要看它的左孩子是否处理完了
            // 而要检查它的左孩子，就要先把它本身存起来
            stk.push(cur);
            cur = cur->left;
        }
        // 2. 如果当前手里已经没有未处理完的结点了，那么我们就需要看之前是否存过还未处理完的结点
        // 而根据循环体的条件，我们此时一定还有未处理完的结点
        else
        {
            // 弹出一个最近添加的还未处理完的结点
            // 注意到这个最近的一定是已经被处理完左子树的一个结点，否则的话我们应该进入的是上面的 if 分支
            cur = stk.top();
            // 处理它本身
            res.push_back(cur->val);
            // 继续处理右孩子，注意，此时我们相当于已经处理完了 cur 结点，需要把它从未处理完的记录栈中弹出
            stk.pop();
            cur = cur->right;
        }
    }
    // 返回结果即可
    return res;
}