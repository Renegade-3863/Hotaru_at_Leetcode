#include "Solution.h"

struct TrieNode
{
public:
    TrieNode() : left(nullptr), right(nullptr) {}
    // 本题的前缀树只有两种可行的 "字符"：0和1
    // 所以一个结点中只需要保存两个指针即可
    // 连哈希表都不需要了
    // left 指向当前为 '0' 的分支
    // right 指向当前为 '1' 的分支
    TrieNode* left;
    TrieNode* right;
    // 32 位整数是定长的，所以我们应该不需要 isEnd 标记位了。。

    // 往 TrieNode 代表的前缀树中添加 val 这个值
    void add(int val)
    {
        TrieNode* cur = this;
        for(int i = 30; i >= 0; --i)
        {
            if((val >> i) & 1)
            {
                if(!cur->right)
                {
                    cur->right = new TrieNode();
                }
                cur = cur->right;
            }
            else
            {
                if(!cur->left)
                {
                    cur->left = new TrieNode();
                }
                cur = cur->left;
            }
        }
    }

    // 定制的检查函数，这里我们只是利用了前缀树的思想，实际上并不是字典树，给定一个 num，我们要找的无非就是和它每个位上不同的数，所以要反过来遍历
    int check(int num)
    {
        TrieNode* cur = this;
        // 找出的结果值
        int res = 0;
        for(int i = 30; i >= 0; --i)
        {
            if((num >> i) & 1)
            {
                // 如果当前位是 1，那么我们要尝试往 '0' 的分支走
                if(cur->left)
                {
                    res = (res << 1)+1;
                    cur = cur->left;
                }
                // 否则，只能往 '1' 的分支走
                else
                {
                    res = res << 1;
                    cur = cur->right;
                }
            }
            else
            {
                // 如果当前位是 0，那么我们要尝试往 '1' 的分支走
                if(cur->right)
                {
                    res = res << 1;
                    cur = cur->right;
                }
                else
                {
                    res = (res << 1)+1;
                    cur = cur->left;
                }
            }
        }
        return res;
    }
};

int Leetcode401_500::Solution::findMaximumXOR(vector<int>& nums)
{
    // Mark 一下这道题，没做过根本想不到还是一道字典树的题。。。
    // 不过后面想想，如果多写一写例子，模拟一下过程，还真会觉得前缀树的这个解法很巧妙
    // 这样想：
    // 我们要最大的异或值，那么肯定是高位的1尽可能多更好
    // 对于任意一个数，我们都想知道有没有任何一个数，能和它做出尽可能多的高位异或结果1
    // 这可以通过前缀树来进行加速
    // 我们正好复习一下前缀树的写法
    TrieNode* root = new TrieNode();
    int ans = 0;
    for(const auto& num : nums)
    {   
        root->add(num);
        ans = max(ans, root->check(num));
    }
    return ans;
}