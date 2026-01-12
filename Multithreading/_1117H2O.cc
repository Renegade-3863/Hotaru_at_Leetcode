// 简单设计一下逻辑链：
/*
    首先，可以用两个条件量 cntH, cntO，来标定当前所处的状态
    cntH == 0, cntO == 0，没有任何原子到达（0 H, 0 O)
    cntH == 1 && cntO == 0 || cntH == 0 && cntO == 1，有一个原子到达
    cntH == 1 && cntO == 1 || cntH == 1 && cntO == 1 || cntH == 2 && cntO == 0，有两个原子到达
    cntH == 2 && cntO == 1，有三个原子到达 （只有这种情况下可以打印一个新的水分子
*/
class H2O
{
private:
    int cntH;
    int cntO;
    mutex mtx;
    // 由于只用两个线程，这里我们只需要一个条件变量
    // 互斥锁用一个也足够了，锁住两个临界变量即可
    condition_variable cv;

public:
    H2O()
    {
        
    }

    void hydrogen(function<void()> releaseHydrogen)
    {

        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();
    }

    void oxygen(function<void()> releaseOxygen)
    {

        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
    }
};