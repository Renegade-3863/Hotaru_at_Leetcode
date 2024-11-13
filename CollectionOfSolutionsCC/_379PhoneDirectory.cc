#include "Solution.h"

// 本题的关键设计思路难点是：
// 如何提供一种高效的检查最小还未被分配号码的方法？
// 其实这道题让我想到了和位图有关的方法
// 考虑用下面的方式存储电话号码 (最多 10^4 种)
// 我们用每一个32位的整数代表32种不同的电话号码
// 例如，第一个32位的整数代表 0-31 这32个电话号码是否可用
// 第二个32位的整数代表 32-63 这32个电话号码是否可用
// 以此类推
// 之后在获取最小可用的电话号码时，假设我们知道最小哪个32位一组的电话号码里面有可用号码，我们就用位运算计算出最靠右的那一位1，并返回这个号码即可(这一步可以通过减1按位与实现)
// 不过前面这个假设我们还需要考虑一下如何实现
// 不难想到，可以再存一层对于这些32位整数的位图
// 每一位标识对应序号的32位整数是否为全零(只要不为全零，我们就明白这里还有为1的位)
// 那么检查最小的不为全零的32位整数同样可以复用我们上面的位运算方法
Leetcode301_400::Solution::PhoneDirectory::PhoneDirectory(int maxNumbers)
{
    // 这里我们需要根据电话号码的数据量决定两个位图的大小
    // 底层位图的大小应该是 maxNumbers / 32 + (maxNumbers % 32 > 0) 
    this->constraint = maxNumbers / 32 + (maxNumbers % 32 > 0);
    this->mappingBottom = vector<unsigned int>();
    this->mappingBottom.resize((maxNumbers/32+(maxNumbers%32>0)), 0xffffffff);
    this->idx = 0;
    // 为了避免底层位图的最高一个32位整数出现不合法的数据选取，我们划定一个最大容量值
    this->maxNumber = maxNumbers;
}

int Leetcode301_400::Solution::PhoneDirectory::get()
{
    // 已经没有可用号码了，直接返回 -1 即可
    if(this->idx == constraint)
    {
        return -1;
    }
    // 本题的核心函数，实现了这个，别的都不难了
    // 首先，检查顶层的下标，看最小的非零的32位整数的序号
    // 这个值记录在了 this->idx 中
    // x ^ (x-1) 取出的就是从右到左第一个1
    unsigned int innerOffset = this->mappingBottom[this->idx] ^ (this->mappingBottom[this->idx]-1);
    // 一个 O(32) == O(1) 的检查过程。。。
    int offset = 0;
    // bool printit = innerOffset == 4294967295;
    while(innerOffset != 1)
    {
        ++offset;
        innerOffset >>= 1;
    }
    // 我们需要检查一下，this->mappintBottom[idx] 这个值是不是在取出这个号码后变为全零了
    this->mappingBottom[this->idx] &= (0xffffffff ^ (1<<offset));
    // 如果变为全零，我们需要更新到下一个非全零的位置
    // 这里我们假设：比 idx 更小的元素都是全零
    // 这里需要额外检查一轮返回的电话号是否超过了原本设定的 maxNumber
    int ret = idx*32+offset;
    while(this->idx < constraint && !this->mappingBottom[this->idx])
    {
        ++this->idx;
    }
    // 注意，这里结束后，idx 可能会停留在 constraint 处，这时意味着已经没有可用的电话号了
    return ret < maxNumber ? ret : -1;
}

bool Leetcode301_400::Solution::PhoneDirectory::check(int number)
{
    // 要检查的是对应的号码是否可用
    // 我们检查桶内的对应位置是否为1即可
    return (this->mappingBottom[number / 32] & (1 << (number%32)));
}

void release(int number)
{
    // 这一步很简单，我们先释放，然后判断 idx 是否小于当前这个 number 所在的桶即可
    this->mappingBottom[number/32] = this->mappingBottom[number/32] | (1 << (number%32));
    if(this->idx > number/32)
    {
        this->idx = number/32;
    }
}