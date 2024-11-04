#include "Solution.h"

vector<int> Leetcode301_400::Solution::maxNumber(vector<int>& nums1, vector<int>& nums2, int k)
{
    // 做这题之前建议先学习一下 402 题，那道题可以说是本题的基础，会了 402 题这道题只是做了一些拓展
    // 从这个角度来考虑本题会更容易：
    // 我们最后得到的那个最大的结果，一定会是这样的
    // n 个来自 nums1，k-n 个来自 nums2
    // 那么，我们是不是只需要枚举这个 n 的值，就能遍历所有可能的情况？
    // 如果是的，那么我们是不是之后就只需要选出这些得到的最大值中，最大的那一个就行了？
    // 似乎有了一个切入点
    // 之后，我们还需要考虑一件事情
    // 这 n 个数字 / k-n 个数字怎么选？
    // 不难想到，应该是选出一个基于 nums1 全序列的、长度为 n 的，数值上最大的子序列
    // 对于 n-k 的部分同理
    // 之后把这两部分进行排列组合，再拿到结果最大的那个值即可
    // 最后还有一个问题：怎么个排列组合法？
    // 举个例子：
    // 假设我们从 nums1 中取 3 个数，从 nums2 中取 2 个数
    // 拿到了 [5, 9, 3] 和 [5, 8] 这两个序列
    // 那么接下来我们进行比较：
    // 第一位：5 == 5
    // 此时应该添加哪个 5 ？
    // 不难看出应该添加第一个 5
    // 这样继续后面的添加，我们能拿到 59583 这个最大值
    // 而如果添加第二个 5
    // 那么最后我们只能拿到 58593 这个非最大值
    // 先说结论，我们应该添加并推进指针的，是字典序上来看更大的那一侧的序列指针
    // 具体原因：
    // 首先，对于两列序列字典序相同的最长前缀，这部分实际上我们添加谁都行
    // 但是，如果其中某个序列的字典序大于另一个序列，即它们有不等的部分
    // 那么更大的那部分应该被保证会先被遍历到
    // 好比上面的 [5] 和 [5] 这两个相等的前缀，这部分本质上我们先添加谁都可以
    // 但是，因为 nums1 第一个和 nums2 不等的元素是大于的关系，那么我们为了保证在添加过程中能先检查到这个 9
    // 就必须先添加 nums1 的这个5，并后移它的指针
    // 当两个指针指向的元素不同的时候，我们就可以直接贪心，添加并移动指向值较大的那一侧的指针即可
    // 直到合并完两个数组即可
    // 终于明确了基本的思路，下面开始写代码
    // 首先，我们需要一个类似 402 题的抽取长度为 n 的最大子序列的函数
    function<vector<int>(const vector<int>&, int)> findKLargest = [&](const vector<int>& nums, int n) -> vector<int>
    {
        // 用于找出给定的数组中长度为 n 的最大子序列
        // 对于单一的字符串，我们只需要使用一个栈来完成整个操作
        vector<int> res;
        int m = nums.size();
        for(int i = 0; i < m; ++i)
        {
            // 如果栈中现有的元素加上还剩下的没有检视的元素的和还够凑出一个长度为 n 的串，那么我们可以进一步讨论
            // 否则，就不需要进一步讨论了，剩下的元素都必须添加到栈中
            while(res.size()+(m-i) > n && !res.empty() && res.back() < nums[i])
            {
                res.pop_back();
            }
            // 退出上面的内部循环后，我们要么是已经确定剩下的元素必须全部添加到结果中
            // 要么是栈中已经没元素了
            // 要么是栈顶部到元素是不小于当前数据的
            // 这些情况下，当前数据都可以直接压到栈中
            res.push_back(nums[i]);
        }
        // 注意，上面的过程中，我们可能会构建出一个长度大于 n 的序列，所以最后我们需要截取前 n 个元素作为答案
        res.resize(n);
        return res;
    };  
    // 根据上面的逻辑，我们还需要一个比较两个数字数组字典序大小关系的函数，在下面写一下
    function<int(const vector<int>&, const vector<int>&, int, int)> compare = [&](const vector<int>& nums1, const vector<int>& nums2, int idx1, int idx2) -> int
    {
        // 我们需要按位进行比较
        while(idx1 < nums1.size() && idx2 < nums2.size())
        {
            int num1 = idx1 < nums1.size() ? nums1[idx1] : 0;
            int num2 = idx2 < nums2.size() ? nums2[idx2] : 0;
            if(num1 > num2)
            {
                return 1;
            }
            else if(num1 < num2)
            {
                return -1;
            }
            // 否则，相等时，同步移动两个指针
            ++idx1; ++idx2;
        }
        if(idx1 == nums1.size() && idx2 == nums2.size())
        {
            return 0;
        }        
        return idx1 == nums1.size() ? -1 : 1;
    };
    // 需要用到的函数写完了，我们只需要以它们为基础完成我们之前的逻辑
    int m = nums1.size(), n = nums2.size();
    vector<int> res(k, 0);
    for(int s = max(0, k-n); s <= min(m, k); ++s)
    {
        vector<int> board1 = findKLargest(nums1, s);
        vector<int> board2 = findKLargest(nums2, k-s);
        vector<int> board;
        int i = 0, j = 0;
        while(i < board1.size() || j < board2.size())
        {
            int num1 = i < board1.size() ? board1[i] : 0;
            int num2 = j < board2.size() ? board2[j] : 0;
            if(num1 > num2)
            {
                // 直接添加更大的那个元素即可
                board.push_back(board1[i++]);
            }
            else if(num1 < num2)
            {
                board.push_back(board2[j++]);
            }
            else
            {
                // 先比较剩余部分的字典序
                int result = compare(board1, board2, i, j);
                switch (result)
                {
                    case 1:
                        board.push_back(board1[i++]);
                        break;
                    case -1:
                        board.push_back(board2[j++]);
                        break;
                    default:
                        board.push_back(board1[i++]);
                        break;
                }
            }
        }
        if(compare(board, res, 0, 0) == 1)
        {
            res = board;
        }
    }
    // 全部完成，返回 res 即可
    return res;
}