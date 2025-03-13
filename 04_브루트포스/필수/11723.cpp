// 아이디어
// 주어진 연산 구현 
// check 연산일 경우 출력되게 
// M이 3백만이므로 시간 복잡도 생각해야함! => 비트마스킹으로 풀어보기
// 20bit를 설정하고 1인 각 비트의 자리수를 집합 S으로 설정

#include <iostream>

using namespace std; 

const int MAX = 20;

// all 연산
void calculationAll(int &S){
    S |= (1 << MAX) - 1 ;  // ex.10000 -1 = 1111 방법으로 전체1 만들기
}

// empty 연산
void calculationEmpty(int &S){
    S = 0;
}

// 나머지 연산들
void calculation(int &S, string calc, int num){
    int n = num -1;
    
    if(calc == "add"){
        S |= (1 << n); // n번째 비트를 1로 설정 (1과의 or연산은 항상1)
    }
    else if(calc == "remove"){
        S &= ~(1 << n); // n번째 비트를 0으로 설정 (0과의 and 연산은 항상 0)
    }
    else if(calc == "check"){
        cout << ((S & (1 << n)) ? 1 : 0) << "\n"; // (1&1=1 0&1=0)
    }
    else if(calc == "toggle"){
        S ^= (1 << n);  // 1과의 XOR연산 (1^1 =0, 0^1=1)
    }
}

int main() {
    // 입출력 속도 빠르게
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // 입력
    int S = 0; // 집합을 비트마스킹으로 표현 
    int M;
    string calc;
    int num;
    cin >> M;

    while(M--){
        // num입력이 있는 경우와 없는 경우 구분
        cin >> calc;

        if(calc == "all"){
            calculationAll(S);
        }
        else if(calc == "empty"){
            calculationEmpty(S);
        }
        else{
            cin >> num;
            calculation(S, calc, num);
        }
    }
    return 0;
}
