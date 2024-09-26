#include "Solution.h"

Leetcode101_200::Node* connect2(Leetcode101_200::Node* root)
{
    // 本题放宽了条件限制，要求变成了一般二叉树而不是满二叉树
    // 其实本质上是差不多的，我们仍然可以使用 "利用上层修改下层" 的策略
    // 对于本题，我们可以记录两个指针，而不是一个，一个指针记录 "当前层"，另一个指针记录 "下一层"
    // 当前层指针用于遍历当前层的所有结点，下一层指针用于记录下一层的当前最靠右的已经连好 next 指针的结点
    // 之后，我们用上层指针不断遍历，找下一个出现在下一层的结点，并在找到时更新下一层指针
    // 这样，我们只比上一题多用了一个指针，仍然是常数的空间复杂度
    if(!root)
    {
        return nullptr;
    }
    Node* curLeftMost = root, * nxtLeftMost = root->left ? root->left : root->right;
    // 注意，循环结束条件的意义需要进行修改，我们此时无法再通过下一层最左侧是否有结点来判断下一层本身是否有结点
    // 这个 nxtLeftMost 的意义应该是下一层最靠左的非空结点的值(不存在则为空)
    // 对于它的更新策略也需要一些修改
    while(nxtLeftMost)
    {
        Node* curLevel = curLeftMost, * nxtLevel = nxtLeftMost;
        // 鉴于我们规定的是 nxtLeftMost 是下一层最靠左的非空结点，那么需要在检查 curLevel 指针的时候进行一些判断
        // 如果当前层的左孩子是非空的，那么这个结点指向的可能是 nxtLevel，也可能是它右侧的结点，注意，如果指向的是 nxtLevel 右侧的结点
        // 那么一定是 nxtLevel 右侧和它在同层紧邻的结点，基于我们对 nxtLevel 的定义，它代表的是最靠左的还没有连好 next 指针的下一层结点
        Node* rec = nxtLeftMost->left;
        while(curLevel)
        {
            if(curLevel->left && curLevel->left != nxtLevel)
            {
                // 我们在每次移动 nxtLevel 之前，要判断这个下一层结点有没有子结点，这是为更新 nxtLeftMost 服务的
                if(!rec && nxtLevel->left)
                {
                    rec = nxtLevel->left;
                }
                if(!rec && nxtLevel->right)
                {
                    rec = nxtLevel->right;
                }
                nxtLevel->next = curLevel->left;
                nxtLevel = nxtLevel->next;
            }
            if(curLevel->right && curLevel->right != nxtLevel)
            {
                if(!rec && nxtLevel->left)
                {
                    rec = nxtLevel->left;
                }
                if(!rec && nxtLevel->right)
                {
                    rec = nxtLevel->right;
                }
                nxtLevel->next = curLevel->right;
                nxtLevel = nxtLevel->next;
            }
            curLevel = curLevel->next;
        }
        // 最后一个 nxtLevel 指针也要检查一次，用于更新 rec
        // 澄清一个事实：nxtLevel 在每一轮循环中都必然始终非空，原因在于，我们只有当 nxtLevel 的 next 指针可以指向一个非空结点的情况下才会更新 nxtLevel 信息
        if(!rec && nxtLevel->left)
        {
            rec = nxtLevel->left;
        }
        if(!rec && nxtLevel->right)
        {
            rec = nxtLevel->right;
        }
        // 根据 nxtLeftMost 的原值更新 curLeftMost 指针
        curLeftMost = nxtLeftMost;
        // 根据 rec 的值更新 nxtLeftMost 指针
        nxtLeftMost = rec;
    }
    // 更新结束，返回结果
    return root;
}