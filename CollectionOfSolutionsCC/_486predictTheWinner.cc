#include "Solution.h"

// 第一版：DFS，不带记忆化的版本
bool Leetcode401_500::Soltuion::predictTheWinner(vector<int>& nums)
{
    // 经典博弈论问法：给定 ... 情况，谁能赢？
    // 这种题一般也是 DP 问题，我们还是从子问题入手，先尝试用传统的 DFS 来解决问题
    // 定义下面的子问题：
    // 给定当前玩家的得分 curScore，以及剩余可以选择的数字下标范围 i 和 j
    // 返回一个 bool 值，代表当前玩家在这种情况下是否能赢
    // 鉴于题目本身有一个限定条件：当得分相同时，赢的人是玩家1，我们需要引入一个额外的变量：记录当前玩家编号：num
    // oppoScore 代表对手的得分
    function<bool(int, const int&, int, int, int)> canWin = [&](int curScore, const int& oppoScore, int i, int j, int num) -> bool
    {
        // 如何判断当前情况下是否能赢？
        // 首先定下一个结束条件，也是最容易判断输赢的情况：
        // i == j，那么此时当前玩家就只能取 nums[i] 处的元素
        if(i == j)
        {
            curScore += nums[i];
            // 我们需要根据 num 是否为 1 来决定在 curScore == oppoScore 的时候是否返回 true
            if(curScore == oppoScore)
            {
                // 如果当前玩家是玩家 1，那么说明他赢了，否则说明是玩家2，他输了
                return num == 1;
            }
            return curScore > oppoScore;
        }
        // 那么在当前玩家拿完 nums[i] 元素后，我们就可以根据
        // 当前玩家无非有两种选择：1. 拿取下标 i 处的元素，留下 [i+1, j] 范围内的元素给对手
        // 2. 拿取下标 j 处的元素，留下 [i, j-1] 范围内的元素给对手
        // 检查如果拿 i 处的元素，对手能不能赢
        curScore += nums[i];
        if(!canWin(oppoScore, curScore, i+1, j, (num%2)+1))
        {
            // 如果这样做，对手一定赢不了，那么当前玩家就一定能赢，返回 true 即可
            return true;
        }
        curScore -= nums[i];
        curScore += nums[j];
        // 检查如果拿 j 处的元素，对手能不能赢
        if(!canWin(oppoScore, curScore, i, j-1, (num%2)+1))
        {
            return true;
        }
        curScore -= nums[j];
        // 如果两种情况下都没法赢，那么这种操作下，当前玩家就一定会输，返回 false 即可
        return false;
    };
    // 调用函数即可
    return canWin(0, 0, 0, nums.size()-1, 1);
}

// 第二版：优化 DFS，加入记忆化数组
bool predictTheWinner(vector<int>& nums)
{
    // 不难发现上面的递归过程包含很多重复的计算，我们可以引入一个记忆化数组来对搜索进行加速
    // 我们需要思考一下这个记忆化数组实际需要记忆的东西有哪些
    // 首先，最基本的："剩余数字区间" [i, j] 肯定是需要记录的
    // 那么，curScore 和 oppoScore 也是必须要记忆的东西吗？
    // 实际上，我们不难发现这样一个情况：
    // 我们只需要记录 curScore 和 oppoScore 的差值
    // 同时，这个差值就可以用来得出每一个子问题的结果
    // 那么我们实际上可以把原来 dp 数组中记录的 bool 值换成实际的 curScore 和 oppoScore 的差值
    // 这样就完成了数据的压缩存储
    // 最后是剩下的这个 num 值
    // 我们之前使用它的唯一目的就是所谓的 "如果是玩家 1，那么他在得分想等的情况下能赢"，但是仔细想一下就会发现
    // 实际上，我们定义的子问题是：当前玩家，在给定的条件下，是否能够赢得游戏
    // 所以其实精确地定义每个子问题的玩家 1 和玩家 2 没有任何意义
    // 同时，这里我们记忆的内容是 "当前做出选择的玩家在给定的情况下，能够赢过对手的最大分数值"
    // 那么我们就只需要在最外层，也就是题目给定的玩家 1 和玩家 2 的情况下，判断结果是否是非负数即可
    // 明确了整体流程，我们就可以写出 DFS+记忆化代码了
    // 记忆化数组，存储的东西和下面的定义是统一的
    int n = nums.size();
    // 最后，我们发现，这里判断记忆化数组中是否实际存储了对应的结果值的条件不好写，那么我们就直接写 DP 代码好了。。
    /*
    vector<vector<int>> memo(n, vector<int>(n, 0));
    // 这个返回值，代表的是 "当前做出选择的玩家在给定的情况下，能够赢过对手的最大分数值"
    function<int(int, int)> dfs = [&](int i, int j) -> int
    {

    };
    */
}

// 第三版：DP 代码，具体执行逻辑见第二版的解释
bool predictTheWinner(vector<int>& nums)
{
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(n, INT_MIN));
    // 重新审视一下递推关系式：
    // dp[i][j] = max(nums[i]-dp[i+1][j], nums[j]-dp[i][j-1])
    // 意思是：当前玩家可以胜过对手的数值，等于它做出这次选择的收益，减去之后情况下，对手可以赢过他的最大值
    // 那么我们不难发现，这就是一个常规的区间 dp，我们可以用区间长度来进行从小到大的计算
    for(int i = 0; i < n; ++i)
    {
        // 首先初始化边界情况：i == j，此时根据 dp 数组的定义，我们不难得出 dp[i][i] == nums[i]
        dp[i][i] = nums[i];
    }
    // 之后，就是按照区间长度进行遍历
    for(int len = 2; len <= n; ++len)
    {
        for(int i = 0; i <= n-len; ++i)
        {
            // 获取当前起点，固定长度的区间的右边界
            int j = i+len-1;
            // 执行递推
            dp[i][j] = max(nums[i]-dp[i+1][j], nums[j]-dp[i][j-1]);
        }
    }
    // 最后需要的结果就是 dp[0][n-1];
    return dp[0][n-1] >= 0;
}

// 第四版：DP 空间优化，转二维为一维
bool predictTheWinner(vector<int>& nums)
{
    // 观察上面的 DP 递推式：
    // dp[i][j] = max(nums[i]-dp[i+1][j], nums[j]-dp[i][j-1])
    // 不难发现，对于 dp 矩阵，每一个格子的值只和它左侧和上方相邻的元素有关
    // 所以我们实际上可以把二维数组压缩成一维，换成滚动数组
    int n = nums.size();
    vector<int> dp(n, INT_MIN);
    // 初始化只需要填 dp[0][0]
    // 我们会发现这个矩阵只有右上半+对角线是有意义的
    // dp[0][0] = nums[0];
    // 之后，每一轮按行计算开始之前，都别忘了对 dp[i][i] 进行初值赋值
    for(int i = n-1; i >= 0; --i)
    {
        dp[i] = nums[i];
        for(int j = i+1; j < n; ++j)
        {
            dp[j] = max(nums[i]-dp[j], nums[j]-dp[j-1]);
        }
    }
    return dp[n-1] >= 0;
}