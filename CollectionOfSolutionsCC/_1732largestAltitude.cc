class Soltuion
{
public:
    int largestAltitude(vector<int>& gain)
    {
        // 简单题，简单做
        // O(n) 遍历一遍即可
        // 默认的最高海拔是 0，因为起点的海拔就是 0
        int maximum = 0, cur = 0;
        for(const int& dif : gain)
        {
            cur += dif;
            maximum = cur > maximum ? cur : maximum;
        }
        return maximum;
    }
};