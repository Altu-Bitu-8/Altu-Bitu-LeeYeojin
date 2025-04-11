// 아이디어
/* 
뭔가 앞의 부분문제에서 현재 인덱스의 값을 비교해서 bottom-up 방식으로 풀 수 있지 않을까? 
    => 동적계획법
각 인덱스에서의 가장 긴 증가하는 부분 수열의 길이를 dp라고 하자.
    * k < i라 하면, 결국 k에서의 가장 긴 증가하는 부분 수열이,
    i에서의 가장 긴 증가하는 부분 수열에 포함(부분)이 될 수 있는지를 확인하면서 bottom-up 시켜가는 문제!  
    그리고 그 중에서 가장 긴 수열을(길이를)찾는 것!!(len)
*/

#include <iostream> 
#include <vector>

using namespace std;

int main() {
    // 입력
    int n;
    cin >> n;

    vector<int> a(n, 0);
    vector<int> dp(n, 0);
    int len;
    int max_len = 0;

    // 연산
    for(int i = 0; i < n; i++){
        len = 0;
        cin >> a[i];
        
        for(int k = 0; k < i; k++){
            // 인덱스의 값을 비교해서 K의 가장 긴~수열이 i의 가장 긴 ~ 수열에 포함될 수 있는지 판단 
            if(a[i] > a[k]){  
                len = max(dp[k], len); // 부분 문제 이용   
            }
        }
        dp[i] = ++len;  // 자기자신 // len++은 dp에 ++하기 전의 값이 저장됨!! 주의!   

        // 수열 a 전체에서의 max 업데이트   
        if(max_len < dp[i]){
            max_len = dp[i];
        }
    }

    // 출력 
    cout << max_len;
    return 0;
}
