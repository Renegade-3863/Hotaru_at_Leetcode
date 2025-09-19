class ZeroEvenOdd
{
private:
    int n;
    // turn 用于记录当前输出的是一个偶数还是奇数，或者是一个 0
    // 简单说，它是按序打印的关键量
    int turn;
    // idx 记录当前打印到数字几（不是打印 0 的时候会用到它）
    int idx;
    // 互斥锁，用于在打印时加锁
    mutex mtx;
    // 条件变量，用于唤醒其它线程
    condition_variable cv;

public:
    ZeroEvenOdd(int n)
    {
        this->n = n;
        // 第一个要打印的数默认是 0
        this->turn = 0;
        this->idx = 1;
    }

    // printNumber(x) output "x", where x is an integer
    void zero(function<void(int)> printNumber)
    {
        while(1)
        {
            // 执行任何操作前，先尝试获取锁
            unique_lock<mutex> lock(this->mtx);
            /*
                总结一下：为什么需要这个 if 语句：
                一个很可能出现的死亡情况：
                当前线程（A）执行完一个 0 的打印 -> notify_all() -> 另一个线程立刻获取到锁 -> A 甚至来不及进入后面的 while 循环中的 wait
                -> 另一线程（B）执行完自己的打印 -> 发现需要结束任务 -> 调用 notify_all() 
                问题就出在这里
                此时 A 还未调用 wait 函数，所以压根不涉及唤醒
                它只会在 B 退出后，正常拿到这个锁，之后才进入 while 循环进行 wait，而此时，黄花菜都凉了，信号也不会收到 -> 直接锁死
            */
            if(this->idx > n)
            {
                return;
            }
            // 防止虚假唤醒
            while(this->turn == 1)
            {
                // 虚假唤醒，释放锁，继续休眠
                this->cv.wait(lock);
                // 被唤醒时，检查是否是因为已经完成打印而被唤醒，如果是，就直接结束线程
                if(this->idx > n)
                {
                    return;
                }
            }
            // 正确唤醒，打印一个 0
            printNumber(0);
            // 修改 turn 为 1
            this->turn = 1;
            // 注意，这里有几种方案，但是只 notify_one 肯定是不行的，这样可能会唤醒错误的线程，导致锁死
            // 这里采用直接 notify_all() 的暴力方案
            this->cv.notify_all();            
        }
    }

    void even(function<void(int)> printNumber)
    {
        while(1)
        {
            // 打印前，尝试获取锁
            unique_lock<mutex> lock(this->mtx);
            if(this->idx > n)
            {
                return;
            }
            // 多一个条件检查，如果当前要打印的数不是偶数，当前线程也要继续休眠等待
            while(this->turn == 0 || this->idx % 2)
            {
                this->cv.wait(lock);
                // 被唤醒时，检查是否是因为已经完成打印而被唤醒，如果是，就直接结束线程
                if(this->idx > n)
                {
                    return;
                }
            }
            // 是正确的唤醒，进行打印
            printNumber(this->idx++);
            // 注意：如果 this->idx 已经到了 n，我们就不再进行打印，直接退出线程
            // 同时需要唤醒其它线程一起退出
            if(this->idx > n)
            {
                this->cv.notify_all();
                // 唤醒其它线程后，自己也要结束
                return;
            }
            // 修改必要的变量
            this->turn = 0;
            // 唤醒所有其它线程
            this->cv.notify_all();            
        }
    }

    void odd(function<void(int)> printNumber)
    {
        while(1)
        {
            unique_lock<mutex> lock(this->mtx);
            if(this->idx > n)
            {
                return;
            }
            while(this->turn == 0 || this->idx % 2 == 0)
            {
                this->cv.wait(lock);
                // 被唤醒时，检查是否是因为已经完成打印而被唤醒，如果是，就直接结束线程
                if(this->idx > n)
                {
                    return;
                }
            }
            printNumber(this->idx++);
            if(this->idx > n)
            {
                this->cv.notify_all();
                return;
            }
            this->turn = 0;
            this->cv.notify_all();            
        }
    }
};