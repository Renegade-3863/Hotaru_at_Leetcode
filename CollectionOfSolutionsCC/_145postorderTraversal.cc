#include "Solution.h"

vector<int> Leetcode101_200::Solution::postorderTraversal(Leetcode101_200::TreeNode* root)
{
    // 后序遍历的基本策略和前中序是一致的，只不过有一些细节问题需要处理而已
    stack<TreeNode*> stk;
    vector<int> res;
    TreeNode* cur = root, * pre = nullptr;
    while(cur || !stk.empty())
    {
        if(cur)
        {
            // 后序遍历，按定义，我们还是要先访问左子树
            stk.push(cur);
            cur = cur->left;
        }
        else
        {
            // 如果没有可以检查的结点了，我们拿出最近的还未访问右子树的结点
            cur = stk.top();
            // 此时，按理来说，我们需要对右侧结点进行访问
            // 所以，应该有一句话是：
            // cur = cur->right;
            // 但是，仔细思考一下，我们不难发现，我们仍然没有对 stk.top() 这个结点本身进行访问
            // 那如果我们不弹出这个栈顶元素，那么我们岂不是会无限地重复：弹出 -> 向右， 弹出 -> 向右的过程？
            // 所以，我们需要一个机制来：明确这个弹出的结点是不是右子树已经访问完的情况
            // 关注后序遍历的基本特征，我们可以发现：我们一定是在检查完右子树后，才会回来遍历当前结点，因而，我们遍历序列上前一个遍历的结点，一定会是当前结点的直接右子结点
            // 明确了这一点，我们就可以通过记录一个前驱结点来实现这种判断了
            // 写代码就可以了
            // 如果这个结点的右孩子是空的，或者上一次遍历的结点就是 cur->right 这个结点，那么我们就可以明确这个结点的右子树已经访问完毕，可以访问当前结点并弹栈了
            if(!cur->right || cur->right == pre)
            {
                res.push_back(cur->val);
                pre = cur;
                // 注意，这里需要把 cur 置空，否则我们还会回到上面的 if 语句，错误地重新把这个结点填回栈中
                cur = nullptr;
                stk.pop();
            }
            // 否则，右子树还有我们没有访问完成的结点，需要继续深入
            // 同时这个结点还不能弹栈，因为它还没访问完成，还需要回溯
            else
            {
                cur = cur->right;
            }
        }
    }
    // 结束后，就可以返回结果了
    return res;
}