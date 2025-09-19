class FooBar
{
private:
    // n 代表要打印 foobar 的次数
    int n;
    // idx 用于判断当前是哪个线程该工作了，防止虚假唤醒
    int idx;
    // 互斥锁，用于锁定打印顺序，包括 n 和 idx
    mutex mtx;
    // 条件变量，用于唤醒另一个线程来执行后续打印
    condition_variable cd;

public:
    FooBar(int n)
    {
        // 一开始，工作的应该是 foo 函数
        this->idx = 0;
        this->n = n;
    }

    void foo(function<void()> printFoo)
    {
        for(int i = 0; i < n; ++i)
        {
            // 每次打印前，尝试获取锁
            unique_lock<mutex> lock(mtx);
            // 条件变量，防止虚假唤醒
            // 如果 idx 是奇数，说明是虚假唤醒，当前线程不能进行打印，要释放锁并继续休眠
            while(idx % 2)
            {
                // cd 等待并释放锁（如果条件不满足）
                this->cd.wait(lock);
            }
            // 可以进行打印，那么进行打印
            printFoo();
            // 打印完成，修改 idx，并唤醒另一个线程继续工作
            this->idx = 1;
            // 不推荐用 notify_all()，不是主从关系，不应有虚假唤醒
            this->cd.notify_one();
        }
    }

    // 逻辑与 foo 类似
    void bar(function<void()> printBar)
    {
        for(int i = 0; i < n; ++i)
        {
            unique_lock<mutex> lock(this->mtx);
            while(idx % 2 == 0)
            {
                this->cd.wait(lock);
            }
            printBar();
            this->idx = 0;
            this->cd.notify_one();
        }
    }
};