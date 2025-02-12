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

vector<int> Leetcode501_600::Soltuion::preorder(Node* root)
{
    // 一个 Status 状态对象，保存：(结点，访问到第几个孩子) 信息
    struct Status 
    {
    public:
        Node* node;
        int cnt;
        Status(Node* _node, int _cnt) : node(_node), cnt(_cnt) {}
    };
    // 二叉树的拓展类问题，N 叉树的遍历
    // 我们就不写递归版本了，没什么技术含量
    // 直接考虑如何实现非递归的版本
    // 本质上来说，还是使用栈来实现非递归版本的方案
    // 我们规定栈在这里存储的是 "还未完成访问的结点"
    // "还未完成访问" 的意义在于：这个结点本身加上它所有的子树，还没有被完全访问
    stack<Status> stk;
    Node* cur = root;
    // res 存储所有的树中元素值
    vector<int> res;
    // 循环结束条件为：已经没有还未访问的结点了
    while(cur || !stk.empty())
    {
        if(cur)
        {
            // 找出了一个新结点，我们先对它本身进行访问，之后压入栈中 (如果它还有没有访问完成的子树)
            res.push_back(cur->val);
            // 注意，这个 if 条件下，我们一定是第一次访问到 cur 结点，所以直接移动到 cur->children[0] 即可
            // 但如果 cur->children.empty()，那么就需要把 cur 置为空结点
            if(cur->children.empty())
            {
                // 不然不会触发后面的 else 语句了
                cur = nullptr;
            }
            else
            {
                // 如果 cur 有多于一个孩子，那么我们才把它压栈
                if(cur->children.size() > 1)
                {
                    stk.emplace(cur, 1);
                }
                // 还有孩子，那么往第一个孩子的地方走
                cur = cur->children[0];
            }
        }
        else
        {
            // 遇到了空结点的情况，此时检查我们还有没有没访问完成的结点，有的话，按先序顺序取出最近的还未访问完成的结点出来多访问一次
            Status& st = stk.top();
            // 根据记录的状态信息，决定下一步要访问哪一个结点
            cur = st.node;
            int count = st.cnt;
            // 我们需要对 cur->children[++st.cnt] 这个结点进行访问
            // 否则，这个结点还有其它需要访问的子节点，我们不能把它出栈
            // 如果 st.cnt+1 == cur->children.size()，那么说明经过这最后一次使用，cur 这个结点就访问完成了，我们可以把它弹出栈
            if(++st.cnt == cur->children.size())
            {
                stk.pop();
            }
            // 走到下一个孩子的位置上去
            cur = cur->children[count];
        }
    }
    // 全部访问完成，返回结果即可
    return res;
}