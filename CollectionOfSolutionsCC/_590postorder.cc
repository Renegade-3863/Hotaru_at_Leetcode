#include "Solution.h"

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

vector<int> Leetcode501_600::Soltuion::postorder(Node* root)
{
    // 对应前序遍历 N 叉树，一定就会有对应的后序遍历 N 叉树
    // 后序一般来说会比前序多一些步骤，主要是用来判断一个结点是否所有的孩子都被访问完成了
    // 不过对应 N 叉树这种数据存储格式，上面的判断方式会更简单一些
    // 简单来说，可行的解决方案如下：
    // 仍然利用 Status 状态信息，记录每个结点当前被访问完的孩子个数，当一个结点所有的孩子都被访问完成了，我们才访问它本身
    // 一个 Status 状态对象，保存：(结点，访问到第几个孩子) 信息
    struct Status 
    {
    public:
        Node* node;
        int cnt;
        Status(Node* _node, int _cnt) : node(_node), cnt(_cnt) {}
    };
    stack<Status> stk;
    Node* cur = root;
    vector<int> res;
    while(cur || !stk.empty())
    {
        if(cur)
        {
            if(cur->children.empty())
            {
                // 如果 cur 是叶子结点，那么我们直接访问即可
                res.push_back(cur->val);
                // 重置 cur 为 nullptr
                cur = nullptr;
            }
            // 因为是后序遍历，我们不需要进行访问，如果 cur 有后续孩子，我们就压栈，挪到 cur->children[0]
            else
            {
                // 注意，这里和先序不一样，无论 cur 是否只有一个孩子，我们都要把它压栈
                // 本质上来说，我们需要记录 cur 这个结点已经有几个孩子被访问完成了，所以这里添加一个 '1'，代表 cur 已经有一个孩子被访问过了
                stk.emplace(cur, 1);
                // cur 移到 cur->children[0]
                cur = cur->children[0];
            }
        }
        else
        {
            // cur 为空，我们检查 stk 中最近的，没有访问完成的结点
            Status& st = stk.top();
            // 结点赋值给 cur
            cur = st.node;
            // 检查 st.cnt 是否等于 cur->children.size()，如果是，说明 cur 代表的子树只剩它自己没有访问了
            if(st.cnt == cur->children.size())
            {
                // 注意，不光要访问，还要把这个已经完全访问了的结点弹出栈
                res.push_back(cur->val);
                // cur 要置空
                cur = nullptr;
                stk.pop();
            }
            else
            {
                // 否则，cur 这个结点所有子树还没访问完全，我们继续访问下一个还没被访问的结点即可
                // 注意，我们使用后置递增函数，是在移动了 cur 后对栈中元素进行的修改
                cur = cur->children[st.cnt++];
            }
        }
    }
    // 访问完成，返回 res 即可
    return res;
}