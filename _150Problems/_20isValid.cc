class Solution
{
public:
    bool isValid(string s)
    {
        // 简单题，简单做
        // 使用一个栈记录当前所有还未被匹配的左括号（含类型）
        // 每遇到一个右括号，就尝试从栈中取出元素进行匹配
        stack<char> stk;
        function<bool(const char&)> checkValid = [&](const char& c) -> bool {
            if(c == ')')
            {
                return !stk.empty() && stk.top() == '(';
            }
            else if(c == ']')
            {
                return !stk.empty() && stk.top() == '[';
            }
            else if(c == '}')
            {
                return !stk.empty() && stk.top() == '{';
            }
            return true;
        };
        for(const auto& c : s)
        {
            if(c == '(' || c == '[' || c == '{')
            {
                stk.push(c);
            }
            else if(c == ')' || c == ']' || c == '}')
            {
                if(checkValid(c))
                {
                    // 如果 checkValid 为 true，那么 stk 中必然有括号（无论圆括号、方括号还是花括号）
                    stk.pop();
                }
                else
                {
                    return false;
                }
            }
        }
        return stk.empty();
    }
};