class Solution
{
public:
    bool isPalindrome(string s)
    {
        // 简单题，简单做
        // 先移除所有非字母数字字符
        int n = s.size();
        string tmp;
        for(int i = 0; i < n; ++i)
        {
            if(!isalnum(s[i]))
            {
                continue;
            }
            tmp.push_back(tolower(s[i]));
        }
        // 双指针检查一遍就行了
        int left = 0, right = tmp.size()-1;
        while(left < right)
        {
            if(tmp[left] != tmp[right])
            {
                return false;
            }
            ++left;
            --right;
        }
        return true;
    }
};