#include <iostream>
#include <set>

using namespace std;

int main() {

    string S;
    cin >> S;

    int len = S.length();
    set<string> sub_string;

    // 모든 부분 문자열 set에 저장 (중복X)
    // substr(pos, len): pos(시작위치), len(부분문자열 길이) 사용
    int a = 0;
    for(int i=0; i < len ; i++){
        for(int j = 1; j <= len - i ; j++){
            sub_string.insert(S.substr(i,j));
            a++;
        }
    }

    //결과 출력
    cout << sub_string.size() << "\n";

    return 0;
}
