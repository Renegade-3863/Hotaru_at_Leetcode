#include "Solution.h"

int kthSmallest(Leetcode201_300::TreeNode* root, int k)
{
    // 本题如果是一道朴素二叉树的题目，那么显然我们很难求解，不过既然是一棵 BST，那么我们显然有一种简单暴力的方案：中序遍历一次这棵树，返回升序序列中第 k 个元素
    // 这里只给出迭代版本的实现方案，递归相信是个人都会写了。。。
    // 注意，题目限定了树中一定有至少一个结点，所以这里不用检查树是否为空了
    // if(!root)
    // {
    //     return 0;
    // }
    stack<TreeNode*> stk;
    TreeNode* cur = root;
    int cnt = 0;
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
            if(++cnt == k)
            {
                return cur->val;
            }
            cur = cur->right;
        }
    }
    // 理论上不会执行到这一行
    return 0;
}

// 看到好多人都提到了 Morris 遍历解法，这里就学习一下这个 "据说" 只有竞赛才会用到的 O(1) 空间复杂度的 BST 遍历方案
int kthSmallest(Leetcode201_300::TreeNode* root, int k)
{
    // Morris 遍历的基本原理来自于我们在《数据结构》书中学习到的二叉搜索树线索化过程
    // 我们在丢掉了原本用于存储 DFS 记录的栈后，需要做的弥补就是找到一种方案，在我们需要回弹的时候，能够找到那个要回弹的结点
    // 这可以通过 "线索化" 来实现
    TreeNode* cur = root;
    // res 记录的是第 k 小的元素的值
    int cnt = 0, res = -1;
    // cur 定义为我们当前在 "观察" 的结点
    while(cur)
    {
        // 我们针对当前结点进行检查
        // 如果左孩子是空的，这就意味着，这个结点的左子树已经访问完成，那么此时根据中序遍历的性质，我们就可以访问本结点数据了
        if(!cur->left)
        {
            // 记录当前元素的次序值
            if(++cnt == k)
            {
                res = cur->val;
            }
            // 之后向右深入
            cur = cur->right;
        }
        // 如果左孩子是非空的，那么我们此时需要找出这个结点的直接前驱结点
        else
        {
            // 通过循环找出前驱
            TreeNode* predecessor = cur->left;
            while(predecessor->right && predecessor->right != cur)
            {
                predecessor = predecessor->right;
            }
            // 如果这个前驱的右孩子还是一个空结点，即还没链接到后继结点，说明我们还没完成对这个结点的访问，我们把后继前驱关系记录下来
            if(!predecessor->right)
            {
                predecessor->right = cur;
                cur = cur->left;
            }
            // 我们又一次找到了这个前驱，注意这样的性质：如果我们第二次以 "找前驱" 的方式找到了当前这个 predecessor，那么说明我们一定是又访问到了同一个 cur 结点
            // 而在中序遍历中，第一次访问到一个结点的时候我们需要先向左侧深入，第二次的时候就一定是因为左子树访问完了，我们才会回来，所以这时我们可以默认是 cur 的左子树已经访问完了
            // 也就是可以对 cur 进行处理了
            else
            {
                // 别忘了，处理完 cur，要把它的前驱结点的右孩子指向复原，防止后续出现死循环
                predecessor->right = nullptr;
                if(++cnt == k)
                {
                    res = cur->val;
                }
                // 根据中序遍历的性质，访问完一个结点 cur 后，我们还是需要向右深入
                cur = cur->right;
            }
        }
    }
    // 返回结果
    return res;
}

// 即然写完了中序遍历的代码，那么我们很难不想到如何完成前序和后序的 Morris 遍历方法
// 这里回顾 144 题和 145 题进行一下学习
// 144. 二叉树的前序遍历
vector<int> preorderTraversal(Leetcode101_200::TreeNode* root)
{
    // 前序遍历不难写出类似于中序遍历的代码，本身思想是类似的，只是访问 cur 结点的时机不同而已
    TreeNode* cur = root;
    vector<int> res;
    while(cur)
    {
        // 剩下的内容和中序遍历几乎没有区别
        // 如果左子树为空，那么因为此时本结点已经访问完成，我们可以直接转入右孩子
        if(!cur->left)
        {
            // 根据前序遍历的思路，无论左孩子是否为空，我们都需要先对 cur 结点进行访问
            res.push_back(cur->val);
            cur = cur->right;
        }
        // 否则，左子树还有结点，那么我们还是先找出 cur 的直接前驱，把它链接到 cur 上，以便后续返回时通过右指针回来
        else
        {
            TreeNode* predecessor = cur->left;
            while(predecessor->right && predecessor->right != cur)
            {
                predecessor = predecessor->right;
            }
            // 这是第一次访问到 cur 和通过 cur 访问到这个 predecessor 结点
            if(!predecessor->right)
            {
                // 根据前序遍历的思路，无论左孩子是否为空，我们都需要先对 cur 结点进行访问
                res.push_back(cur->val);
                predecessor->right = cur;
                // 进行链接并继续深入左子树
                cur = cur->left;
            }
            // 这是第二次访问到 cur 和通过 cur 访问到这个 predecessor 结点
            else
            {
                predecessor->right = nullptr;
                // 解除链接并继续深入右子树，因为这时 cur 以及它的左子树都以及访问完成了
                cur = cur->right;
            }
        }
    }
    return res;
}

// 145. 二叉树的后序遍历
vector<int> postorderTraversal(Leetcode101_200::TreeNode* root)
{
    // Morris 的后序遍历不像一般的迭代后序遍历那样难想，我们稍加思考即可
    // 依然是类似的遍历模版
    TreeNode* cur = root;
    vector<int> res;
    while(cur)
    {
        if(!cur->left)
        {
            // 基于后序遍历的原则，我们此时依然不能对当前结点进行访问，需要进一步对右子树进行访问
            cur = cur->right;
        }
        else
        {
            // 类似的逻辑
            // 先找当前结点的中序前驱
            // 注意这里找的是中序前驱，不是后序前驱！
            TreeNode* predecessor = cur->left;
            while(predecessor->right && predecessor->right != cur)
            {
                predecessor = predecessor->right;
            }
            // 判断这个中序前驱结点是否链接到了当前 cur 结点
            if(!predecessor->right)
            {
                // 第一次访问 cur，在 predecessor 中记录 cur 这个中序后继
                predecessor->right = cur;
                cur = cur->left;
            }
            else
            {
                // 第二次访问 cur 并通过 cur 检查出这个 predecessor 结点
                // 那么此时我们就终于可以对 cur 结点进行访问了，因为第二次访问到 cur 意味着我们已经完成了对其左右子树的访问
                res.push_back(cur->val);
                predecessor->right = nullptr;
                // 此时 cur 应该怎么办？
                // 写到这里，我们会发现遇到了一个逻辑上的难题：cur 是否应该继续向右走？
                // 理论上讲，后序遍历中，我们如果第二次访问到 cur 结点，此时就代表着左右子树都访问完成了，那么我们应该把 cur 置空从而退出循环？
                // 可是仔细一想，这又不对，因为这只在 cur 是根结点的时候才可行，如果 cur 不是根结点，那么在这里把 cur 置空相当于提前退出遍历循环了
                // 这样显然是错误的
                // 不好处理了，不得已，我们只能丢弃这种模版，另寻它法
            }
        }
    }
    return res;
}

// 经历了上面错误的 Morris 后序遍历尝试，我们需要考虑怎么重写后序遍历的代码
// 考虑这样的事实：前序遍历的顺序是：root->left->right
//              后序遍历的顺序是：left->right->root
//              前序遍历左右反过来进行是：root->right->left
//              前序遍历左右反过来，再反序是：left->right->root，好巧不巧，正好是后序遍历！
// 所以我们就找到了一种巧法来变形前序遍历的代码来进行后序遍历
// 简单对前序遍历的代码做一点修改即可
vector<int> postorderTraversal(Leetcode101_200::TreeNode* root)
{
    TreeNode* cur = root;
    vector<int> res;
    while(cur)
    {
        // 反过来，我们对 cur->right 进行镜像判断即可
        if(!cur->right)
        {
            res.push_back(cur->val);
            cur = cur->left;
        }
        // 只需要简单地把 left 换成 right，right 换成 left 即可
        else 
        {
            TreeNode* predecessor = cur->right;
            while(predecessor->left && predecessor->left != cur)
            {
                predecessor = predecessor->left;
            }
            if(!predecessor->left)
            {
                res.push_back(cur->val);
                predecessor->left = cur;
                cur = cur->right;
            }
            else
            {
                predecessor->left = nullptr;
                cur = cur->left;
            }
        }
    }
    reverse(res.begin(), res.end());
    return res;
}