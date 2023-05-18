#include <iostream>
#include<unordered_map>
using namespace std;

class Check{
private:
    // 状态枚举
    enum State {
        STATE_INITIAL,
        STATE_INT_SIGN,
        STATE_INTEGER,
        STATE_POINT,
        STATE_POINT_WITHOUT_INT,
        STATE_FRACTION,
        STATE_EXP,
        STATE_EXP_SIGN,
        STATE_EXP_NUMBER,
        STATE_END
    };

    // 类型枚举
    enum CharType {
        CHAR_NUMBER,
        CHAR_EXP,
        CHAR_POINT,
        CHAR_SIGN,
        CHAR_SPACE,
        CHAR_ILLEGAL
    };

    CharType checkChar( char c ) {
        if(c == 'e' || c == 'E') return CHAR_EXP;
        else if(c == '.') return CHAR_POINT;
        else if(c >= '0' && c <='9') return CHAR_NUMBER;
        else if(c == '+' || c == '-') return CHAR_SIGN;
        else if(c == ' ') return CHAR_SPACE;
        else return CHAR_ILLEGAL;
    }
public:
    bool isNumber(string s){
        unordered_map<State, unordered_map<CharType, State>> transfer{
            {
                STATE_INITIAL, {
                    {CHAR_SPACE, STATE_INITIAL},
                    {CHAR_NUMBER, STATE_INTEGER},
                    {CHAR_SIGN,  STATE_INT_SIGN},
                    {CHAR_POINT, STATE_POINT_WITHOUT_INT}
                }
            }, {
                STATE_INT_SIGN,{
                    {CHAR_NUMBER, STATE_INTEGER},
                    {CHAR_POINT, STATE_POINT_WITHOUT_INT}
                }
            }, {
                STATE_INTEGER, {
                    {CHAR_NUMBER, STATE_INTEGER},
                    {CHAR_EXP, STATE_EXP},
                    {CHAR_POINT, STATE_POINT},
                    {CHAR_SPACE, STATE_END}
                }
            }, {
                STATE_POINT, {
                    {CHAR_NUMBER, STATE_FRACTION},
                   {CHAR_EXP, STATE_EXP},
                    {CHAR_SPACE, STATE_END}
                }
            }, {
                STATE_POINT_WITHOUT_INT, {
                    {CHAR_NUMBER, STATE_FRACTION}
                }
            }, {
                STATE_FRACTION,
                {
                    {CHAR_NUMBER, STATE_FRACTION},
                    {CHAR_EXP, STATE_EXP},
                    {CHAR_SPACE, STATE_END}
                }
            }, {
                STATE_EXP,
                {
                    {CHAR_NUMBER, STATE_EXP_NUMBER},
                    {CHAR_SIGN, STATE_EXP_SIGN}
                }
            }, {
                STATE_EXP_SIGN, {
                    {CHAR_NUMBER, STATE_EXP_NUMBER}
                }
            }, {
                STATE_EXP_NUMBER, {
                    {CHAR_NUMBER, STATE_EXP_NUMBER},
                    {CHAR_SPACE, STATE_END}
                }
            }, {
                STATE_END, {
                    {CHAR_SPACE, STATE_END}
                }
            }
        };

        // 遍历字符串，进行状态转移
        State p = STATE_INITIAL;
        for(auto & ele : s) {
            CharType type = checkChar(ele);
            //  若没有找到相对应的状态转移路径，返回错误
            if(transfer[p].find(type) == transfer[p].end()){
                return false;
            } else {
                p = transfer[p][type];
            }
        }
        // 判断下最终的结果是否是合法结果
        return p == STATE_INTEGER || p == STATE_POINT || p == STATE_FRACTION || p == STATE_EXP_NUMBER || p == STATE_END;

    }
};

int main()
{
    Check c;
    if(c.isNumber("+100")) cout << "is number" << endl;
    else cout << "is not number" << endl;
    return 0;
}

