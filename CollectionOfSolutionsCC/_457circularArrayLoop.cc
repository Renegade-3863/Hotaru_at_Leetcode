#include "Solution.h"

bool Leetcode401_500::Soltuion::circularArrayLoop(vector<int>& nums)
{
    // 属于是普通题中比较抽象的一道题了，需要很细心才行
    // 我们一步步来思考如何求解，既然是一道中等题，那么它的思维难度想必不会特别高
    // 如果做过快慢指针那道题，那么本题不难联想到需要用的是快慢指针遍历法来确认 "是否有环"
    // 注意这里一定要理解好题目的本意：我们需要确定是否存在一个 "起点"，这个 "起点" 出发可以最后根据上面的值最终走回 "起点" 本身
    // 所以最简单的思路就是：遍历每个结点，把它们分别作为起点进行快慢指针遍历，检查快慢指针是否可以从这个起点出发最后通过不同的速度相遇
    // 同时，注意题目的要求：我们返回起点，必须是通过全正的走法，或者全负的走法，如果一条路径中出现了异号的走法，那么这条路径就可以直接被丢弃了，不用管了
    // 所以我们还需要对每一轮快慢指针保存一个 "正负" 变量信息才行
    // 最后，我们需要防止两个指针因为没有环而不停地走，如何处理？
    // 打住，别想歪了，我们先考虑这种情况是否真的有可能出现
    // 如果这个数组没有 "环"，那么如果画出来步子，是什么样子？
    // 我们不难发现，如果没有 "环"，那么只可能是：某个下标上的步数为零，换句话说，指针在这里停下了
    // 或者是：路径上某个下标上的步数是负数，换句话说，指针在某个点回头了，往回走了
    // 其它情况下，只要指针是不断 "往前走" 的，那么总会回卷回数组前面的某个结点
    // 即使回卷的结点不是之前访问过的，但记住：结点个数是有限的，比如某一轮遍历，第一次走了 k 个结点才开始回卷
    // 那么回卷后至多有 (n-k)/n 的概率不会走回之前的结点
    // 而每一轮的 "前进"，都会至少经过一个新下标才开始回卷
    // 从这个角度想，我们总有一次回卷会走回之前遍历过的结点
    // 想明白了这个，就知道我们不用考虑这种 "无限循环" 的情况了
    // 剩下的就是先写一下基本方法的代码了，至于 O(n) 的优化后面再说
    // direction 变量用于记录某一轮两个指针行动的基本方向，默认为 "1"，也就是 "向右"
    // 等一下，题目还限制了自循环为不合法，也就是说，任何一个循环不能是长度仅为1的
    // 所以我们必须添加一种机制过滤掉这种情况
    int direction = 1;
    int n = nums.size();
    // 对每个位置进行遍历，对它们使用快慢指针
    for(int i = 0; i < n; ++i)
    {
        // 修改本轮的 direction
        direction = nums[i] > 0 ? 1 : -1;
        int fast = i, slow = i;
        // invalid 代表循环是否合法，初始值为 "合法"
        bool valid = true;
        // 因为一开始 fast 和 slow 对位置是相同的，我们使用 do...while 循环而不是 while 循环
        // 最外面的退出条件是：快慢指针相遇了
        do
        {
            // 根据快慢指针所在位置的下标，进行移动，慢指针一次走一步，快指针一次走两步，超出范围的下一格要回卷
            // 不过在走之前，我们需要判断一下：快慢指针所在位置上的 "走法" 是否违反了 direction 的限制
            if(direction * nums[fast] < 0 || direction * nums[slow] < 0)
            {
                // 我们利用 "同号相乘为正" 进行判断，如果值比较大可能会溢出，可以考虑用位运算代替进行检查
                valid = false;
                break;
            }
            // 我们还需要一种机制来检查是否存在自循环
            // 如果存在，那么一定是 fast 指针先遇到，我们可以在 fast 指针运动时同步进行判断
            // 方向是对的，那么我们继续走
            // 括号内的 %n 是用来防止负数值过大导致后面的 +n 没法回卷回 [0, n] 之间的数的
            // 括号外的 %n 是用来实现 "向右走" 的回卷的
            // slow 走一步
            slow = (slow+(nums[slow]%n)+n)%n;
            // fast 走两步
            int tmp = (fast+(nums[fast]%n)+n)%n;
            if(tmp == fast)
            {
                valid = false;
                break;
            }
            fast = tmp;
            if(direction * nums[fast] < 0)
            {
                valid = false;
                break;
            }
            tmp = (fast+(nums[fast]%n)+n)%n;
            if(tmp == fast)
            {
                valid = false;
                break;
            }
            fast = tmp;
        } while(fast != slow);
        // 退出循环的时候，我们需要检查一下，如果是因为 fast == slow 退出的，同时不是因为方向不同退出的，那么就返回 true
        if(fast == slow && valid)
        {
            return true;
        }
    }
    // 没有找到合法值，我们返回 false
    return false;
}

// 上面的方法是 O(n^2) 的，考虑如何进行时间复杂度优化
bool circularArrayLoop(vector<int>& nums)
{
    // 上面的两层循环是否有某些重复检查？
    // 肯定是存在的，实际上，只要我们在前面的某轮循环访问过了某个结点，并且没有返回 true，那么我们就可以肯定，如果后续的某轮检查又一次到达了这个下标
    // 那么这轮循环就也肯定不能找到环了，我们结束检查即可
    // 至于如何实现，我们可以通过把 fast 和 slow 访问过的下标值都修改为 0 这个特殊值来提示后续访问: "可以结束 while 循环了"
    // 属于是普通题中比较抽象的一道题了，需要很细心才行
    // 我们一步步来思考如何求解，既然是一道中等题，那么它的思维难度想必不会特别高
    // 如果做过快慢指针那道题，那么本题不难联想到需要用的是快慢指针遍历法来确认 "是否有环"
    // 注意这里一定要理解好题目的本意：我们需要确定是否存在一个 "起点"，这个 "起点" 出发可以最后根据上面的值最终走回 "起点" 本身
    // 所以最简单的思路就是：遍历每个结点，把它们分别作为起点进行快慢指针遍历，检查快慢指针是否可以从这个起点出发最后通过不同的速度相遇
    // 同时，注意题目的要求：我们返回起点，必须是通过全正的走法，或者全负的走法，如果一条路径中出现了异号的走法，那么这条路径就可以直接被丢弃了，不用管了
    // 所以我们还需要对每一轮快慢指针保存一个 "正负" 变量信息才行
    // 最后，我们需要防止两个指针因为没有环而不停地走，如何处理？
    // 打住，别想歪了，我们先考虑这种情况是否真的有可能出现
    // 如果这个数组没有 "环"，那么如果画出来步子，是什么样子？
    // 我们不难发现，如果没有 "环"，那么只可能是：某个下标上的步数为零，换句话说，指针在这里停下了
    // 或者是：路径上某个下标上的步数是负数，换句话说，指针在某个点回头了，往回走了
    // 其它情况下，只要指针是不断 "往前走" 的，那么总会回卷回数组前面的某个结点
    // 即使回卷的结点不是之前访问过的，但记住：结点个数是有限的，比如某一轮遍历，第一次走了 k 个结点才开始回卷
    // 那么回卷后至多有 (n-k)/n 的概率不会走回之前的结点
    // 而每一轮的 "前进"，都会至少经过一个新下标才开始回卷
    // 从这个角度想，我们总有一次回卷会走回之前遍历过的结点
    // 想明白了这个，就知道我们不用考虑这种 "无限循环" 的情况了
    // 剩下的就是先写一下基本方法的代码了，至于 O(n) 的优化后面再说
    // direction 变量用于记录某一轮两个指针行动的基本方向，默认为 "1"，也就是 "向右"
    // 等一下，题目还限制了自循环为不合法，也就是说，任何一个循环不能是长度仅为1的
    // 所以我们必须添加一种机制过滤掉这种情况
    int direction = 1;
    int n = nums.size();
    // 对每个位置进行遍历，对它们使用快慢指针
    for(int i = 0; i < n; ++i)
    {
        // 修改本轮的 direction
        direction = nums[i] > 0 ? 1 : -1;
        int fast = i, slow = i;
        // invalid 代表循环是否合法，初始值为 "合法"
        bool valid = true;
        // 因为一开始 fast 和 slow 对位置是相同的，我们使用 do...while 循环而不是 while 循环
        // 最外面的退出条件是：快慢指针相遇了
        do
        {
            // 根据快慢指针所在位置的下标，进行移动，慢指针一次走一步，快指针一次走两步，超出范围的下一格要回卷
            // 不过在走之前，我们需要判断一下：快慢指针所在位置上的 "走法" 是否违反了 direction 的限制
            if(direction * nums[fast] < 0 || direction * nums[slow] < 0)
            {
                // 我们利用 "同号相乘为正" 进行判断，如果值比较大可能会溢出，可以考虑用位运算代替进行检查
                valid = false;
                break;
            }
            // 我们还需要一种机制来检查是否存在自循环
            // 如果存在，那么一定是 fast 指针先遇到，我们可以在 fast 指针运动时同步进行判断
            // 方向是对的，那么我们继续走
            // 括号内的 %n 是用来防止负数值过大导致后面的 +n 没法回卷回 [0, n] 之间的数的
            // 括号外的 %n 是用来实现 "向右走" 的回卷的
            // slow 走一步
            int rec = slow;
            slow = (slow+(nums[slow]%n)+n)%n;
            nums[rec] = 0;
            // fast 走两步
            rec = fast;
            int tmp = (fast+(nums[fast]%n)+n)%n;
            nums[rec] = 0;
            if(tmp == fast)
            {
                valid = false;
                break;
            }
            fast = tmp;
            if(direction * nums[fast] < 0)
            {
                valid = false;
                break;
            }
            rec = fast;
            tmp = (fast+(nums[fast]%n)+n)%n;
            nums[rec] = 0;
            if(tmp == fast)
            {
                valid = false;
                break;
            }
            fast = tmp;
        } while(fast != slow);
        // 退出循环的时候，我们需要检查一下，如果是因为 fast == slow 退出的，同时不是因为方向不同退出的，那么就返回 true
        if(fast == slow && valid)
        {
            return true;
        }
    }
    // 没有找到合法值，我们返回 false
    return false;
}