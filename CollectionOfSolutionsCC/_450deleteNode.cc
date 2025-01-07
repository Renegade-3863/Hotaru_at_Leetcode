#include "Solution.h"

Leetcode401_500::TreeNode* deleteNode(Leetcode401_500::TreeNode* root, int key)
{
    // 数据结构基础题：如何删除 BST 中具有指定值的结点
    // 我们需要考虑的是：
    // 1. 要删除的结点有哪些类型，可以一并处理吗？
    // 2. 如果不能一并处理，那么分别都需要怎么处理？
    // 先来看第一个问题：
    // 很明显我们不能把根结点和其它结点一并处理
    // 第一步是：定位到这个结点本身，过程中记录每一个遍历到的结点的父结点，根结点的父结点为空
    TreeNode* par = nullptr, * cur = root;
    // BST 的遍历过程，这个不会的话真得去补基础了。。
    // 退出条件有两个
    // 一是 cur 为空，代表树中不存在关键字为 key 的结点
    // 二是 cur->val == key，代表找到了要删除的结点
    while(cur && cur->val != key)
    {
        par = cur;
        // 根据 key 值和 cur->val 的大小关系决定要怎么动
        if(cur->val > key)
        {
            // 要删的结点只可能在左子树，往左走
            cur = cur->left;
        }
        else
        {
            // 要删的结点只可能在右子树，往右走
            cur = cur->right;
        }
    }
    // 分类讨论各种可能性
    // 1. !cur，此时说明要删的结点压根就不存在，那么什么都不用做了
    if(cur)
    {
        // 定位前驱结点
        TreeNode* predecessor = cur->left, * pre = cur;
        // cur 没有前驱结点 
        if(!predecessor)
        {
            // 那么直接删除 cur 即可
            if(par)
            {
                if(par->left == cur)
                {
                    par->left = cur->right;
                }
                else
                {
                    par->right = cur->right;
                }
            }
            TreeNode* ret = par ? root : cur->right;
            delete cur;
            return ret;
        }    
        // 我们单独把： cur 的前驱结点就是它的左孩子 这种情况拿出来进行讨论
        if(!predecessor->right)
        {
            // 如果 par 不是空结点，那么需要对其进行修改，根据具体关系来
            if(par)
            {
                if(par->left == cur)
                {
                    par->left = predecessor;
                }
                else
                {
                    par->right = predecessor;
                }
            }
            // 之后是对 predecessor 本身进行修改
            // 但是由于 predecessor 本身就是 cur 的左孩子，所以这里我们只能对 predecessor 的右孩子进行修改
            predecessor->right = cur->right;
            // predecessor 父结点也要进行修改
            pre->left = nullptr;
            // 别忘了删除 cur
            delete cur;
            // 返回新的根结点即可
            return par ? root : predecessor;
        }
        // 其它情况可以合并到一起写逻辑
        while(predecessor->right)
        {
            pre = predecessor;
            predecessor = predecessor->right;
        }           
        // predecessor 上移
        // 这部分和前面是一样的
        if(par)
        {
            if(par->left == cur)
            {
                par->left = predecessor;
            }
            else
            {
                par->right = predecessor;
            }
        }
        // 这种情况下，pre 一定是 predecessor 的父结点，并且 predecessor 在 pre 的右孩子上
        pre->right = predecessor->left;
        // 之后是修改 predecessor 本身
        predecessor->left = cur->left;
        predecessor->right = cur->right;
        delete cur;
        // 返回结果
        return par ? root : predecessor;
    }
    // !cur，直接返回根结点即可
    return root;
}