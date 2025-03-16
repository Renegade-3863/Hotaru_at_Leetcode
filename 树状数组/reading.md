# 树状数组 (Binary indexed trees, BIT)
### 一种支持 单点修改 和 区间查询的数据结构 (简化版线段树)

### 具体论证不多说，计算机人学知识，代码先行
### 给出使用树状数组模拟差分睡的思想来动态维护区间和以及单点和区间修改操作的样例代码
``` C++
// 数组 t2 负责记录 di，也就是差分值本身，另一个数组 t1 负责记录 di*i，也就是差分值*差分下标
// 要求 sum of a[1, r]
// 那么通过数学推导，结果式就是：
// (sum of i from 1 to r, di*(r+1)) - (sum of i from 1 to r, di*i)
// 那么 sum of a[l, r]
// 就是 sum of a[1, r] - sum of a[1, l-1]
int t1[MAXN], t2[MAXN], n;

// 获取 x 只保留最低位的 1 的到的结果，这个转换算子是整个树状数组的核心
int lowbit(int x)
{
    return x & (-x);
}

// 处理单点修改的函数，对 a[k] 修改，单点加 v
// 这个点可以往后逐层上溯，直到越过整个树状数组可以维护的区间为止
// 这个回溯路径上的结点，就是所有和 a[k] 有关的树状数组结点
void add(int k, int v)
{
    int v1 = k*v;
    while(k <= n)
    {
        t1[k] += v;
        t2[k] += v1;
        k += lowbit(k);
    }
}

// 获取树状数组 t 维护的数组 a，范围 [1, k] 之间的元素和
int getsum(int* t, int k)
{
    int ret = 0;
    // 循环累加结点值的和，直到 [k-lowbit(k)+1, k] 范围中的 k 值到 0 为止
    while(k)
    {
        ret += t[k];
        k -= lowbit(k);
    }
    return ret;
}

// 简单推断
// 因为我们维护的是一个差分数组 d，代码内的 t1 和 t2
// 所以如果对一个区间 [l, r] 内的元素同时加上 v
// 那么实际上我们并不需要修改 d[l+1..r] 中的任何一个元素
// 只有 d[l] 和 d[r+1] 会需要被修改 (内部其它元素同时修改，差分值不变)
void add1(int l, int r, int v)
{
    add(l, v);
    add(r+1, -v);
}

// 获取 [l, r] 区间中的元素和
long long getsum1(int l, int r)
{
    // 根据代码开头的推断，我们可以把公式直接抄过来
    return (r+1ll)*getsum(t1, r)-getsum(t2, r)-(1ll*((l-1)+1)*getsum(t1, l-1))+getsum(t2, l-1);
}
```
















