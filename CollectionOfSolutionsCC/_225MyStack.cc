#include "Solution.h"

// 本题要求我们仅使用队列这种先进先出的数据结构来反向实现栈这种先进后出的数据结构
// 考虑如何进行实现
/*
    首先考虑简单一些的方案：使用单个队列来模拟栈
    我们不难实现一种暴力的方案：
    正常向这个队列中压入元素，每次要弹出元素或者获取栈顶元素的时候，我们只需要对队列中的元素进行一轮 "循环出队入队"，直到队列中只剩下一个元素，此时我们就可以根据
    所要执行的操作类型对这个元素进行操作了
    如果要的是出栈，那么我们直接把这最后一个元素出队
    如果要的是返回栈顶元素，那么我们可以记录这个元素值并把它插回队尾，然后返回这个值
*/

// 我们先尝试用一个队列的方式来实现一遍
// 构造函数什么都不用做
Leetcode201_300::Solution::MyStack::MyStack() {}

void Leetcode201_300::Solution::MyStack::push(int x)
{
    // 模拟压栈操作
    // 这里我们正常压队
    this->q.push(x);
}

int Leetcode201_300::Solution::MyStack::pop()
{
    // 注意，本题要求 pop 也要返回栈顶元素，所以要相应作出处理
    int n = this->q.size();
    for(int i = 0; i < n-1; ++i)
    {
        int tmp = this->q.front();
        this->q.pop();
        this->q.push(tmp);
    }
    // 循环结束后，队头的就是 "栈尾" 的元素
    // 我们记录它的值
    int ret = this->q.front();
    this->q.pop();
    return ret;
}

int Leetcode201_300::Solution::MyStack::top()
{
    // 模拟弹栈操作
    // 根据上面的思路来就行
    int n = this->q.size();
    for(int i = 0; i < n-1; ++i)
    {
        int tmp = this->q.front();
        this->q.pop();
        this->q.push(tmp);
    }
    // 循环结束后，队头的就是 "栈尾" 的元素
    // 我们记录它的值，并把它重新插回队尾
    int ret = this->q.front();
    this->q.pop();
    this->q.push(ret);
    return ret;
}

bool Leetcode201_300::Solution::MyStack::empty()
{
    // 直接检查队列是否为空即可
    return this->q.empty();
}

// 考虑如何进行优化，上面的方案肯定不是最优的，因为我们在弹栈和返回栈顶元素的时候都遍历了一轮整个队列中的元素，那么一种较好的优化方式是在压栈的时候就处理好这个队列
// 这样可以省去一轮遍历
Leetcode201_300::Solution::MyStack::MyStack() {}

void Leetcode201_300::Solution::MyStack::push(int x)
{
    // 模拟压栈操作
    // 这里我们正常压队
    this->q.push(x);
    // 正常压队之后，我们这里作一个假设：原先队中存有的元素从队头到队尾是满足一个栈顺序的，因而此时我们可以只用一轮遍历让这个新加入的队尾元素也运动到栈顶
    int n = this->q.size()-1;
    for(int i = 0; i < n; ++i)
    {
        int tmp = this->q.front();
        this->q.pop();
        this->q.push(tmp);
    }
    // 循环处理完成后，就可以返回了，这个新的队列就满足了栈顺序
}

int Leetcode201_300::Solution::MyStack::pop()
{
    // 此时弹栈和取栈顶元素都只需要一步了
    int ret = this->q.front();
    this->q.pop();
    return ret;
}

int Leetcode201_300::Solution::MyStack::top()
{
    return this->q.front();
}

bool Leetcode201_300::Solution::MyStack::empty()
{
    // 直接检查队列是否为空即可
    return this->q.empty();
}
    