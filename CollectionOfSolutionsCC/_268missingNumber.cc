#include "Solution.h"

int Leetcode201_300::Solution::missingNumber(vector<int>& nums)
{
    // 简单题简单做，本题类似脑筋急转弯题目，有点考验智商
    // 考察 nums 数组的本质属性
    // 因为 nums 中有 n 个元素，而 [0, n] 中有 n+1 个元素，那么我们可以明确，如果对 nums 数组排序，那么 nums 数组中一定有一位是对不上的
    // 同时这一位后面的所有元素都是对不上号的 (第一个对不上号的位导致的)
    // 我们可以利用这个性质，每次把当前位置上的元素交换到它在最终排好序的数组中该在的位置上，通过这种方式，我们应该总能找到一个位置，它的元素无论怎么交换，都无法得到本位置上该有的元素
    // 那么这个位置上本该有的元素，就是我们缺失的那个元素了
    // 为了防止越界问题，我们先给原数组结尾添加一位元素，这一位上填一个 -1，这个 -1 也是有用的
    nums.push_back(-1);
    int n = nums.size();
    for(int i = 0; i < n; ++i)
    {
        // 注意，如果当前这个位置上的元素，也就是 i，在 nums 数组中实际上并不存在，那么我们这里会陷入死循环，需要额外的退出条件来避免这种情况的发生
        while(nums[i] != i && nums[i] != -1)
        {
            swap(nums[i], nums[nums[i]]);
        }
        // 提问：如果我们是因为 nums[i] == -1 而退出了上面循环，那么是否说明 i 这个元素就是缺失的那一个？
        // 不一定，举一个简单的例子就懂了：
        // [0, 3, 1, -1]
        // 上面这个例子中，我们会先把 3 换到结尾的 -1 位置上，此时 nums[1] 就等于了 -1
        // 可是 nums[1] 位置上本来该有的元素 (1) 不存在吗？
        // 很显然是存在的
        // 因此此时我们不能断定 nums[i] 就是缺失的元素
        // 不过，有一个隐性的条件我们其实是保证了的：
        // i 这个下标左侧一定不存在 i 这个值
        // 具体原因如下：
        // 假设左侧存在了 i 这个值
        // 那么由于我们是从左往右在遍历，那么在之前肯定就已经把 i 这个值交换过来了，同时在当前位置上，我们就不会进入 nums[i] != i 的这个循环，更不可能把 -1 交换过来了
        // 明确了这一点，我们可以发现
        // 只要我们循环遍历完了整个数组，对每个位置都执行完了上面的过程，最后得到的结果数组中，值为 -1 的那个位置上本应有的元素就一定是缺失的了
        // 明确了这一点，最后的函数结尾一个循环就结束了
    }
    // 一个循环
    for(int i = 0; i < n; ++i)
    {
        if(nums[i] == -1)
        {
            return i;
        }
    }
    // 不会执行到这一行
    return -1;
}