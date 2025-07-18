class Solution
{
public:
    int evalRPN(vector<string>& tokens)
    {
        // 简单来说，逆波兰表达式是一种利用栈来计算数学算式的高效结构
        // 我们可以这样执行：
        // 如果遇到一个数组，那么就直接压入栈中
        // 如果遇到一个运算符，那么就弹出栈顶的两个数字弹出，执行符号对应的运算，把结果再压回栈中即可
        stack<int> stk;
        for(const auto& token : tokens)
        {
            if(isdigit(token[token.size()-1]))
            {
                // 如果 token 是一个数字，那么直接压入栈中
                int val = 0, sign = 1;
                for(const auto& c : token)
                {
                    if(c == '-')
                    {
                        sign = -1;
                    }
                    else
                    {
                        val = val*10+(c-'0');
                    }
                }
                stk.push(sign*val);
            }
            else
            {
                int num1 = stk.top();
                stk.pop();
                int num2 = stk.top();
                stk.pop();
                if(token == "+")
                {
                    stk.push(num2+num1);
                }
                else if(token == "-")
                {
                    stk.push(num2-num1);
                }
                else if(token == "*")
                {
                    stk.push(num2*num1);
                }
                else if(token == "/")
                {
                    stk.push(num2/num1);
                }
            }
        }
        return stk.top();
    }
};