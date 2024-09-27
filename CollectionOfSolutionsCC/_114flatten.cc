#include "Solution.h"

// 递归版本
void Leetcode101_200::Solution::flatten(Leetcode101_200::TreeNode* root)
{
    // 本题完全可以使用先序遍历搞一个新的树出来，再一个一个复制回原树，但这么搞有点 nt
    // 正好题目也要求 O(1) 的原地方案，我们就思考一下怎么实现这种 "换结点" 的方案
    // 说起来可能比较抽象，我们可以写一下代码
    // 定义一个递归函数
    // dfs(subRoot)，返回值为把以 subRoot 展开后的结果单链的根结点
    // 进行这样的操作
    // 先把 root 的左子树展开，展开成一棵单链表形式的树，返回它的根结点给调用了 root 的函数层
    // 之后把 root 的右子树和左子树(被展开后) 进行交换，再对 root 的新左子树进行展开
    // 之后不断向右深入 root 的展开后的右子树，到达叶子结点后，把 root 展开好的左子树再接到 这个叶子结点的右子树上即可
    if(!root)
    {
        return;
    }
    // 展开左子树
    flatten(root->left);
    // 递归执行过程和上面写的过程一样
    TreeNode* tmp = root->right;
    // 之后把这个展开了的左子树接到 root 的右孩子处
    root->right = root->left;
    root->left = tmp;
    // 再展开一次新的左子树
    flatten(root->left);
    test = root->right;
    // 之后向右遍历右侧的单链，直到到达叶子结点
    TreeNode* traverse = root;
    while(traverse->right)
    {
        traverse = traverse->right;
    }
    // 把 root 左侧的这个新链接到右侧最深的叶子结点的右孩子处即可
    traverse->right = root->left;
    // 别忘了把原根结点的左孩子置空！！！
    root->left = nullptr;
}

// 后序迭代版本，使用栈
void flatten(Leetcode101_200::TreeNode* root)
{
    if(!root)
    {
        return;
    }
    stack<TreeNode*> stk;
    TreeNode* cur = root;
    TreeNode* pre = nullptr;
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
            // 判断 cur 的右侧结点是不是刚刚才访问过，如果刚刚才访问完成，或者右孩子本身就是一个空结点就不能继续深入了，就要对当前结点进行处理了
            if(!cur->right || cur->right == pre)
            {
                // 刚刚才访问过，此时要处理当前结点并弹栈
                // 此时已经把左右子树都展开完成了，需要记录现在的右子树，之后把左子树接到当前结点的右孩子位置
                TreeNode* tmp = cur->right;
                cur->right = cur->left;
                // 左孩子置空
                cur->left = nullptr;
                // 不断遍历直到叶子结点
                TreeNode* traverse = cur;
                while(traverse->right)
                {
                    traverse = traverse->right;
                }
                traverse->right = tmp;
                // 处理完成，弹栈+置空 cur 结点，防止重复添加结点
                pre = cur;
                cur = nullptr;
                stk.pop();
            }
            else
            {
                // 否则，cur 的右孩子还没有处理完成，需要继续进行右孩子的访问
                cur = cur->right;
            }
        }
    }
}