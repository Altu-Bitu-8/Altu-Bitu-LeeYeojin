// 16  1/16/16
// E=1 year =1,16,31,46  즉 year%15 일때 / 그런데 year % 15일 떄는 예외적으로 E=0이 아닌 E=15
// 아이디어
// E =15 , S = 28, M =19 일 때만 각각 0으로 바꿔주고 시작
// year%15 = E && year%28 = S && year%19 =M 인 최소 year 찾으면 됨 

#include <iostream>

using namespace std;

int findYear(int e, int s, int m){

    int year;
    
    // E =15 , S = 28, M =19 일 때만 각각 0으로 바꿔주고 시작
    if(e == 15){
        e = 0;
    }
    if(s == 28){
        s = 0;
    } 
    if(m == 19){
        m = 0;
    }

    // year%15 = E && year%28 = S && year%19 =M 인 최소 year 찾기
    for(year = 1; ;year++){
        if(year % 15 == e && year % 28 == s && year % 19 == m){
            return year;
        }
    }
    return 0;
}

int main() {

    ios::sync_with_stdio(false); // 입출력 속도 향상
    cin.tie(NULL); //
    cout.tie(NULL); // 
    
    // 입력
    int E, S, M;
    cin >> E >> S >> M;
    
    // 연산 // 출력
    cout << findYear(E, S, M);

    return 0;
}