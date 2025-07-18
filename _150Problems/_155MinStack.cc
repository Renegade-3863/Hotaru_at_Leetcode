class MinStack
{
public:
    // 初始化堆栈对象
    MinStack()
    {

    }

    // 将元素 val 推入堆栈
    void push(int val)
    {
        this->stk.push(val);
        // 如果最小栈为空，那么 val 肯定是当前整个栈中最小的那一个
        // 如果最小栈非空，而最小栈顶的元素是不小于 val，那么说明这个 val 可以代表从现在开始的栈中的最小元素
        // 以上两种情况下，我们都需要把 val 压栈
        if(this->minStk.empty() || this->minStk.top() >= val)
        {
            this->minStk.push(val);
        }
    }

    // 删除堆栈顶部的元素
    void pop()
    {
        // 如果 this->minStk 的栈顶元素等于 this->stk.top()，那么我们只需要一并弹出即可
        if(this->stk.top() == this->minStk.top())
        {
            this->minStk.pop();
        }
        // stk 出栈
        this->stk.pop();
    }

    // 获取堆栈顶部的元素
    int top()
    {
        // 题目保证 top 被调用时栈非空
        return this->stk.top();
    }

    // 获取堆栈中的最小元素
    int getMin()
    {
        return this->minStk.top();
    }
    // 我们用两个栈，一个保存实际的数字序列，另一个保存一个单调栈即可
    stack<int> stk;
    stack<int> minStk;
};