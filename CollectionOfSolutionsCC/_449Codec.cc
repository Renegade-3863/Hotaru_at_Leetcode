#include "Solution.h"

// 本题我们可以利用二叉搜索树本身的性质，来开发新的序列化反序列化方案
// 我们应该记得自己之前曾经做过通过后续遍历序列和中序遍历序列来反向工程出原二叉搜索树的题目
string Leetcode401_500::Solution::Codec::serialize(Leetcode401_500::TreeNode* root)
{
    // 序列化操作，我们只需要对这棵树进行后序遍历即可
    string res;
    // 再复习一遍 Morris 遍历 =^=
    TreeNode* cur = root;
    while(cur)
    {
        // Morris 遍历的本质在于，使用右孩子为空的结点来存储对应的后继结点信息
        // 注意，由于我们后面肯定还会第二次访问到这个 cur 结点，因为我们需要访问它的右孩子结点
        // 所以需要做一些处理来让一个结点 "记住" cur
        // 这个结点就是 cur 的直接前驱结点
        // 这可以通过简单的逻辑操作来实现
        TreeNode* predecessor = cur->left;
        // 如果 predecessor 本身就不存在，那么我们也没必要进一步记录 cur 结点了，直接往右走就行
        if(!predecessor)
        {
            res += to_string(cur->val);
            res += ",";
            cur = cur->right;
            continue;
        }
        // cur 左子树中最靠右的结点就是 cur 的直接前驱结点
        // 如果此次寻找找回了 cur 结点，那么说明我们已经是第二次访问这个 cur 结点了，就不用再对它的右孩子进行访问了
        while(predecessor->right && predecessor->right != cur)
        {
            // cout << predecessor->val << endl;
            predecessor = predecessor->right;
        }
        // 此时我们需要判断一下，是不是因为 predecessor->right == nullptr 而退出的
        if(!predecessor->right)
        {
            // 那么我们是第一次访问 cur 结点，需要在 predecessor->right 处记录 cur 的信息
            predecessor->right = cur;
            // 对当前结点进行访问
            res += to_string(cur->val);
            // 拼接一个逗号作为分隔符
            res += ",";
            // 向左走
            cur = cur->left;
        }
        // 否则，说明我们是第二次访问 cur 了，那么恢复树原本的结构，并向右走即可
        else
        {
            predecessor->right = nullptr;
            cur = cur->right;
        }
    }
    // cout << res << endl;
    // 遍历完成，我们修改最后一个逗号，返回结果即可
    if(!res.empty())
    {
        res[res.size()-1] = '#';
    }
    return res;
}

Leetcode401_500::TreeNode* Leetcode401_500::Solution::Codec::deserialize(string data)
{
    // 反序列化的过程基本就是递归处理，我们可以根据先序遍历的基本性质来递归地进行树的恢复处理
    // 先把字符串转成数组存储形式
    // cout << data << endl;
    int num = 0;
    vector<int> nums;
    for(int idx = 0; idx < data.size(); ++idx)
    {
        if(data[idx] == ',' || data[idx] == '#')
        {
            nums.push_back(num);
            num = 0;
        }
        else
        {
            num = num*10+(data[idx]-'0');
        }
    }
    // for(const auto& number : nums)
    // {
        // cout << number << ",";
    // }
    // cout << endl;
    // 我们需要定义一个基本回调函数
    // 从定义上，这个函数是用来构造 nums[start] 到 nums[end] 之间的元素的
    function<TreeNode*(int, int)> subDeserialize = [&](int start, int end) -> TreeNode*
    {
        // 定义递归的基本情况：如果 start > end，那么这棵树就是空的，我们之间返回 nullptr 即可
        if(start > end)
        {
            return nullptr;
        }
        // 首先，我们知道，一个前序序列，根结点一定是开头的元素
        // 那么我们可以先利用 nums[start] 新建一个树结点，这个结点一定是当前子序列的根结点
        TreeNode* root = new TreeNode(nums[start]);
        // 之后，根据先序遍历的性质，我们可以先向后遍历，找到最长的、连续的、小于 nums[start] 的元素的范围，这个范围内的元素构成了 nums[start] 根结点的左子树
        // 剩下的就是右子树了
        int ed = start+1;
        while(ed <= end)
        {
            if(nums[ed] > nums[start])
            {
                break;
            }
            ++ed;
        }
        // 退出时，ed 指向的是第一个右子树中的结点，我们根据这个信息进行递归即可
        root->left = subDeserialize(start+1, ed-1);
        root->right = subDeserialize(ed, end);
        // 构造完成，返回结果即可
        return root;
    };  
    return subDeserialize(0, nums.size()-1);
}