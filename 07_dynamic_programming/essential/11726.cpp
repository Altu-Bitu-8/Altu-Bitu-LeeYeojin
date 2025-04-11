// 아이디어
/*
(2*1 타일 개수, 1*2 타일 2개를 붙인 2*2 모양 개수)
n이 1개 늘어나면 2*1 타일 하나를 더 붙일 수 있고,
2가 늘어나면 2*2 모양을 한 쌍 더 붙일 수 있음
이를 거꾸로 생각해보면 
dp[i] = n-1일 때에서 2*1 타일 하나를 붙인 경우 + n-2일 때 2*2 한 쌍을 붙인 경우
즉, dp[i] = dp[i-1] + dp[i-2]
(피보나치와 매우 유사한 방식)
*/

#include <iostream>
#include <vector>

using namespace std;

// Bottom-up 방식
int tiling(int n, vector<int> &dp){
    dp[1] = 1;
    dp[2] = 2;
    for(int i = 3; i <= n; i++){
        // 오버플로우 방지를 위해 매 계산마다 %10007을 해준다다
        dp[i] = (dp[i-1] + dp[i-2]) % 10007;
    }
    return dp[n];
}

int main () {
    // 입력
    int n;
    int res = 0;
    cin >> n;
    vector<int> dp (n+1,0);

    // 연산 & 출력
    cout << tiling(n, dp) << "\n";
    return 0;
}