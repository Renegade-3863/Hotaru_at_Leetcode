#include "Solution.h"

void Leetcode1_100::Solution::recoverTree(Leetcode1_100::TreeNode* root)
{
    // Mark 一下，本题二刷的时候也没做出来，感觉是一道挺特殊的题目，没有太具体的方法分类
    // 考虑只交换了一对元素的二叉搜索树序列
    // 举例：[1,2,6,4,5,3,7,8]
    // 这里面会出现两对相邻的反序元素对：
    // [6,4] 和 [5,3]
    // 规律是这样的：需要交换的元素是第一对反序元素对中较大的那个结点，和第二对反序元素对中较小的那个结点
    // 如果只存在一对反序元素对
    // 举例：[1,2,3,5,4,6,7,8]
    // 这里只有一对反序对，即 [5,4]
    // 此时我们只需要交换这一对反序序列对即可
    TreeNode* cur = root;
    // first 是要交换的第一个结点
    TreeNode* first = nullptr;
    // second 是要交换的第二个结点
    TreeNode* second = nullptr;
    stack<TreeNode*> stk;
    bool firstOne = true;
    TreeNode* pre = nullptr;
    // 进行中序遍历
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
            stk.pop();
            // 出现了逆序对
            if(!firstOne && pre->val > cur->val)
            {
                // 此时是第一对逆序对，我们要同时记录两个结点
                if(!first)
                {
                    first = pre; second = cur;
                }
                // 此时是第二对逆序对，我们修改 second 指针的值
                else 
                {
                    second = cur;
                }
            }
            pre = cur;
            firstOne = false;
            cur = cur->right;
        }
    }
    // 交换 first 和 second 结点的值即可
    int tmp = first->val;   
    first->val = second->val;
    second->val = tmp;
}