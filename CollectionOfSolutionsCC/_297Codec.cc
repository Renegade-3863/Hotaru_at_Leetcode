#include "Solution.h"

string Leetcode201_300::Solution::CodecTree::serialize(Leetcode201_300::TreeNode* root)
{
    // 把给定的二叉树进行序列化操作
    // 我们可以通过类似 BFS 的方法对一棵二叉树进行序列化：
    // 我们按行对结点添加到返回的字符串中
    string res = "#";
    // 用于 BFS 的队列
    queue<TreeNode*> q;
    if(!root)
    {
        res += "#";
        return res;
    }
    q.push(root);
    while(!q.empty())
    {
        TreeNode* cur = q.front();
        q.pop();
        if(!cur)
        {
            res += "null";
            if(!q.empty())
            {
                res += ",";
            }
            continue;
        }
        // 把当前结点的值尾接到 res 字符串结尾
        res += to_string(cur->val);
        // 对它的两个子结点进行操作
        q.push(cur->left);
        q.push(cur->right);
        // 检查是否还有下一份数据，如果有，就添加一个分隔符 ","
        if(!q.empty())
        {
            res += ",";
        }
    }
    // 结尾添加一个井号，代表序列化字符串的结尾
    res += '#';
    return res;
}   

Leetcode201_300::TreeNode* Leetcode201_300::Solution::deserialize(string data)
{
    // 遍历字符串进行还原即可
    int n = data.size();
    int idx = 1;
    TreeNode* root = nullptr;
    string cur = "";
    // 用于把字符串转换成整型数的子过程
    // 我们假设整数都可以用32位整型表示
    function<int(const string&)> stoi = [&](const string& str) -> int
    {
        int sign = 1;
        if(str[0] == '-')
        {   
            sign = -1;
        }
        int ret = 0;
        for(int i = sign == 1 ? 0 : 1; i < str.size(); ++i)
        {
            ret = ret*10+(str[i]-'0');
        }
        return sign * ret;
    };
    // 为了编写逻辑简便，先把根结点做好初始化
    while(data[idx] != ',' && data[idx] != '#')
    {
        cur += data[idx++];
    }
    if(data[idx] != '#')
    {
        ++idx;
    }
    if(cur == "")
    {
        return nullptr;
    }
    // 把第一个结点赋值给 root
    root = new TreeNode(stoi(cur));
    // 再经过一轮 BFS 即可复原出原二叉树
    queue<TreeNode*> q;
    q.push(root);
    // 转换的退出条件是，遍历到了最后的那个井号
    while(!q.empty())
    {
        TreeNode* curr = q.front();
        q.pop();
        cur = "";
        // 分别尝试添加下一层的左右孩子
        // 先取出当前分段的这个子串
        while(data[idx] != ',' && data[idx] != '#')
        {
            cur += data[idx++];
        }
        // 之后，如果退出不是因为 '#'，我们就把 idx 再后移一位
        if(data[idx] != '#')
        {
            ++idx;
        }
        // 对取出来的 cur 字符串进行分类讨论
        // 1. 是一个数字
        if(cur != "null")
        {
            // 此时先添加到当前结点的左孩子位置上
            curr->left = new TreeNode(stoi(cur));
            q.push(curr->left);
        }
        // 2. 不是一个数字，而是一个 null
        // 我们保持当前结点的左孩子为空即可，不用压队列
        // 如果此时我们已经检查到了 '#'，就可以退出了
        if(data[idx] == '#')
        {
            break;
        }
        // 获取下一个分段
        cur = "";
        while(data[idx] != ',' && data[idx] != '#')
        {
            cur += data[idx++];
        }
        if(data[idx] == ',')
        {
            ++idx;
        }
        // 检查取出来的子串
        if(cur != "null")
        {
            // 此时添加到当前结点的右孩子位置上
            curr->right = new TreeNode(stoi(cur));
            q.push(curr->right);
        }
        // 否则，同左孩子的情况，我们依然什么都不做
    }
    // 处理完成，返回根结点即可
    return root;
} 
