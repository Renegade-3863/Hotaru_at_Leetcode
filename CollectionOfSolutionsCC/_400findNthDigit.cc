#include "Solution.h"

int Leetcode301_400::Solution::findNthDigit(int n)
{
    // 这题有桶的特性，我们可以考虑使用这种方式来加速检索
    // 我们可以发现，一位数有9个(从1到9)
    // 二位数有100个(从10到99)
    // 三位数有1000个(从100到999)
    // 以此类推
    // 而我们要的是第 n 个数，那么我们可以把 [1, n] 这些元素按位数分成不同大小的桶
    // 第一个桶大小为9，第二个为100，...
    // 我们不断从 n 中减少这些桶的数量，直到剩下的桶大小能够覆盖剩下的 offset
    // 我们此时就可以明确：第 n 个数在当前这个桶内部的某一个数上
    // 之后我们就需要具体确定这个数是几了
    // 由于我们肯定知道当前这个桶是几位数的桶，我们再进行一轮类似上面的取模过程即可
    // 假设当前这个桶代表的是 k 位数，剩余的大小为 offset
    // 那么我们只需要取 offset % k
    // 最后我们只需要取 offset / k * k 这个数的第 offset % k 位返回即可，这个数就是答案
    // 明确了上面的过程，我们只需要模拟就行
    // 记录当前桶代表的数的位数
    // size 代表的是桶的大小，只有 digit == 1 的时候不用它而用9做减法
    // start 记录的是当前桶的开头元素
    int digit = 1, size = 9, start = 1;
    // 当 n < digit 的时候我们就可以退出进行下一轮检查了
    while(n/digit > size)
    {
        n -= size * digit;
        // 当前桶中不存在 n 的对应 offset，我们递增一位
        ++digit;
        size *= 10;
        start *= 10;
    }
    // cout << n << endl;
    // 结束这一层循环后，我们就拿到了 n 剩余的部分在 digit 位数的桶中的 offset
    // 这个值就是现在的 n
    // 接下来要定位的是对应的整数
    // 我们取模即可
    int offset = (n-1) % digit;
    // 要取的就是对应数的第 offset 个数
    int board = start + (n-1)/digit;
    // 最后返回 board 的下标为 offset 的数即可 
    // cout << board << endl;
    for(int i = 0; i < digit-offset-1; ++i)
    {
        board /= 10;
    }
    return board % 10;
}