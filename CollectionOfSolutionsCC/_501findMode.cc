#include "Solution.h"

vector<int> Leetcode501_600::Soltuion::findMode(Leetcode501_600::TreeNode* root)
{
    if(!root)
    {
        return {};
    }
    // 题目的优化要求是 O(n) 的空间复杂度，对于一棵 BST，这样的空间优化应该第一时间想到 Morris 遍历
    // 题目要求找出这棵 BST 中所有出现次数最多的元素的值
    // 这很容易让我们联想到对 BST 遍历的几种方法
    // 我们这里采用 Morris 中序遍历即可
    // cur 记录当前在检查的数值类型 (在一棵 BST 中，值相同的元素一定在中序序列中是相邻的)
    // 用于第一次存储 cur 值，如果 hasVal 为 false，说明 cur 还没存储任何值
    bool hasVal = false;
    int curVal;
    int cnt = 0, maxCnt = 1;
    vector<int> res;
    TreeNode* cur = root;
    while(cur)
    {
        // Morris 的基本思想就是利用前驱结点和后继结点之间的右孩子空隙，来临时存储返回信息
            // 我们访问到了一个结点，需要检查这是不是第一次访问这个结点，如果是第一次，我们需要先往左子树走，之后再访问这个结点
            // 如果不是第一次访问这个结点，那么我们就需要对结点本身进行访问，之后往右子树走了
            // 如果这个结点本身没有左子树，那么我们很明显只需要访问它一次
            if(!cur->left)
            {
                // 此时我们只需要提取出当前结点的值做处理，之后往右子树走即可
                int value = cur->val;
                // 如果当前结点的值不等于 cur 的值，或者 cur 还没有值，就要做处理
                if(!hasVal)
                {
                    curVal = value;
                    hasVal = true;
                    cnt = 1;
                    res.push_back(curVal);
                }
                else if(curVal == value)
                {
                    // 找到一个重复值，对应计数+1
                    ++cnt;
                    // 检查 curVal 的 cnt 值是否大于了 maxCnt，如果是，那么清空 res 数组，把当前的 curVal 加入到 res 中
                    if(cnt > maxCnt)
                    {
                        // 别忘了更新 maxCnt
                        res = vector<int>();
                        maxCnt = cnt;
                        res.push_back(curVal);
                    }
                    // 如果 cnt == 已知的出现次数最多的元素
                    else if(cnt == maxCnt)
                    {
                        // 把 curVal 添加到 res 中
                        res.push_back(curVal);
                    }
                }
                else
                {
                    // 检查 curVal 的 cnt 值是否大于了 maxCnt，如果是，那么重置 curVal 和 cnt，并检查是否需要添加到结果数组中
                    // 更新 curVal
                    curVal = value;
                    cnt = 1;
                    if(cnt == maxCnt)
                    {
                        res.push_back(curVal);
                    }
                }
                cur = cur->right;
            }
            else
            {
                // 否则，当前结点有左子树，那么我们需要判断这是第几次访问到 cur，这可以通过寻找 cur 的前驱结点来实现
                TreeNode* predecessor = cur->left;
                while(predecessor->right && predecessor->right != cur)
                {
                    // 不断往右孩子走
                    predecessor = predecessor->right;
                }
                // 退出循环有两种可能性
                if(!predecessor->right)
                {
                    // 这说明我们是第一次访问 cur 结点，那么此时只需要记录 predecessor 对 cur 的前驱关系，不对 cur 进行访问
                    predecessor->right = cur;
                    // 往左走
                    cur = cur->left;
                }
                else
                {
                    // cout << cur->val << endl;
                    // 这说明我们是第二次访问 cur 结点了，那么此时我们执行对 cur 的访问操作 (别忘了在离开 cur 前修复树原本的结构)
                    int value = cur->val;
                    if(!hasVal)
                    {
                        curVal = value;
                        hasVal = true;
                        cnt = 1;
                        res.push_back(curVal);
                    }
                    else if(curVal == value)
                    {
                        ++cnt;
                        // 检查 curVal 的 cnt 值是否大于了 maxCnt，如果是，那么清空 res 数组，把当前的 curVal 加入到 res 中
                        if(cnt > maxCnt)
                        {
                            // 别忘了更新 maxCnt
                            res = vector<int>();
                            maxCnt = cnt;
                            res.push_back(curVal);
                        }
                        // 如果 cnt == 已知的出现次数最多的元素
                        else if(cnt == maxCnt)
                        {
                            // 把 curVal 添加到 res 中
                            res.push_back(curVal);
                        }
                    }
                    else
                    {
                        // 检查 curVal 的 cnt 值是否大于了 maxCnt，如果是，那么重置 curVal 和 cnt，并检查是否需要添加到结果数组中
                        // 更新 curVal
                        curVal = value;
                        cnt = 1;
                        if(cnt == maxCnt)
                        {
                            res.push_back(curVal);
                        }
                    }
                    // 访问完成，别忘了恢复结构
                    predecessor->right = nullptr;
                    // 往右走
                    cur = cur->right;
                }
            }
    }
    // 遍历结束后，我们还剩最后一组数没有检查，在循环外进行检查即可
    if(res.size() == 0 || (cnt == maxCnt && res[res.size()-1] != curVal))
    {
        res.push_back(curVal);
    }
    // 遍历完成，返回结果
    return res;
}