#include "Solution.h"

string getPermutation(int n, int k)
{
    // 本题要求找出按字典序由小到大排列的 n 个数的 n! 种排列中的第 k 个排列
    // 可以通过由最小的排列组合( 1 到 n 按升序排列)开始，调用 k-1 次 "下一个排列" 的算法，就能最终找到第 k 个排列
    // 虽然有些粗暴，不过个人认为这个方法也没有很高的时间复杂度
    // 先复习一下 "下一个排列" 的算法
    function<void(string&)> nextPer = [&](string& s)
    {
        // 第一步，先从左到右找出第一个不是非升序排列的字符对
        int i = s.size()-2;
        while(s[i] >= s[i+1])
        {
            --i;
        }
        // 现在 i 指向了从右到左第一个满足 s[i] < s[i+1] 的元素的下标，这个元素应该和它右侧最靠右的大于它的元素互换
        int j = s.size()-1;
        while(s[j] <= s[i])
        {
            --j;
        }
        // 现在 j 指向了从右到左第一个满足 s[j] > s[i] 的元素的下标，之后我们要做的就是交换着两个元素，并把 i 下标右侧的所有元素(现在还是非升序的)反序成非降序
        swap(s[i], s[j]);
        reverse(s.begin()+i+1, s.end());
    };
    // 初始化一个字典序最小的字符串
    string res = "";
    for(int i = 1; i <= n; ++i)
    {
        res += (char)(i+'0');
    }
    // 递增 k-1 次即可
    for(int i = 1; i < k; ++i)
    {
        nextPer(res);
    }
    return res;
}