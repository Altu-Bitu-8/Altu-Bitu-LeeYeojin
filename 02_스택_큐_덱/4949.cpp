#include <iostream>
#include <stack>

using namespace std;

int main() {

    while (true) {
        string str;
        getline(cin, str);  // 공백 포함 한 줄 입력 받기  

        if (cin.eof() == true) break; // 빈 문장이면 종료
        if (str == ".") break; // 종료 조건

        stack<char> s;
        bool res = true; // 결과 

        for(char c: str){
            if (c == '(') {
                s.push('(');
            }
            else if (c == '[') {
                s.push('[');
            }
            else if (c == ')' ) {
                if(s.empty() || s.top() != '('){
                    res = false;
                    break;
                }
                s.pop();
            }
            else if (c == ']') {
                if(s.empty() ||s.top() != '['){
                    res = false;
                    break;
                }
                s.pop();
            }
        }

        if(!s.empty()){ // 스택이 비어있지 않은 경우
            res = false;
        }

        cout << (res ? "yes" : "no") << "\n";
    }

    return 0;
}