#include "Solution.h"

// 经典的线段树类问题
// book 操作可以被视为对 [startTime, endTime] 的操作
// 而如果 book 的 [startTime, endTime] 范围不为全 0，那么我们返回 false
// 否则，返回 true 即可
// 写一个线段树辅助结构
// 我们用动态开点点方法来做
struct SegNode
{
public:
    // left 和 right 分别指向当前结点的左右子结点 (对应满二叉树中的结点)
    SegNode* left;
    SegNode* right;
    // val 代表当前结点的区间和
    int val;
    // 懒更新信息
    int lazy;
    SegNode(int _val) : val(_val), left(nullptr), right(nullptr), lazy(0) {}
};
// 构建树的函数
SegNode* buildTree(int _val)
{
    // 构建一个新的根结点并返回即可
    return new SegNode(_val);
}
// 清空树占用的内存空间
void deleteTree(SegNode* p)
{   
    // 先递归删除左右孩子，再删除根结点
    if(!p)
    {
        return;
    }
    deleteTree(p->left);
    deleteTree(p->right);
    delete p;
}
// 懒更新函数，对节点 p 进行更新，它管辖的范围是 [l, r]，中点值为 mid
void push_down(SegNode* p, int l, int r, int mid)
{
    // 如果 lazy 值为 0，那么无需对孩子结点进行更新
    // 但是如果左右孩子为空，那么需要进行新建
    if(!p->left)
    {
        p->left = new SegNode(0);
    }
    if(!p->right)
    {
        p->right = new SegNode(0);
    }
    if(p->lazy == 1)
    {
        p->left->val = (mid-l+1);
        p->right->val = (r-mid);
        p->left->lazy = 1;
        p->right->lazy = 1;
        // 别忘了情况 p 的懒信息
        p->lazy = 0;
    }
    // 否则，p->lazy 为 0，那么我们什么也不用做
}

// 用 p 左右孩子的值更新 p
void push_up(SegNode* p)
{
    p->val = p->left->val+p->right->val;
}

// 编写对 root 给定区间 [left, right] 的值进行修改的函数
void update(SegNode* p, int l, int r, int left, int right, int val)
{
    // 我们首先检查 [l, r] 是否被 [left, right] 覆盖了
    if(l >= left && r <= right)
    {
        // 如果被覆盖了，那么我们直接更新 p 的懒信息和 p 本身的值即可
        p->val = (r-l+1);
        p->lazy = 1;
        return;
    }
    // 否则，[left, right] 并不完全包含了 [l, r] 区间，那么我们需要先对 p 进行懒更新，把它的 lazy 数据传递给孩子结点
    int mid = ((r-l)>>1)+l;
    // 利用 mid 进行左右孩子的更新
    push_down(p, l, r, mid);
    // 更新完成后，我们再递归对左右孩子进行更新
    // 如果 [l, mid] 与 [left, right] 有交集，我们对左孩子更新
    if(left <= mid)
    {
        update(p->left, l, mid, left, right, val);
    }
    // 如果 [mid+1, r] 与 [left, right] 有交集，我们对右孩子更新
    if(mid+1 <= right)
    {
        update(p->right, mid+1, r, left, right, val);
    }
    // 左右孩子更新完成，别忘了对 p 进行更新
    push_up(p);
}

// 编写搜索指定区间 [left, right] 的和值的函数
int search(SegNode* p, int l, int r, int left, int right)
{
    // 如果 [left, right] 包含了 [l, r] 区间，那么我们可以直接返回 p->val
    if(l >= left && r <= right)
    {
        return p->val;
    }
    // 否则，我们需要检查 p 的左右孩子
    int mid = ((r-l)>>1)+l;
    push_down(p, l, r, mid);
    int leftVal = 0, rightVal = 0;
    if(left <= mid)
    {
        leftVal = search(p->left, l, mid, left, right);
    }
    if(mid+1 <= right)
    {
        rightVal = search(p->right, mid+1, r, left, right);
    }
    // 返回左右孩子对应区间的值之和即可
    return leftVal+rightVal;
}

Leetcode701_800::Soltuion::MyCalendar::MyCalendar()
{
    // 我们初始化一个根结点即可
    this->root = new SegNode(0);
}

bool Leetcode701_800::Soltuion::MyCalendar::book(int startTime, int endTime)
{
    // 我们假设根结点的范围代表的是 [0, 1e9+7]
    bool ret = true;
    if(search(this->root, 0, 1e9+7, startTime, endTime-1) != 0)
    {
        ret = false;
    }
    else
    {
        update(this->root, 0, 1e9+7, startTime, endTime-1, 1);
    }
    return ret;
}