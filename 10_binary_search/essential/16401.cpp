// 아이디어
/* 
    과자 길이 정렬
    가장 긴 과자 길이(longest) 기준으로 1~longest까지에서 이분탐색
    이때 mid값이 나오면 전체 과자 각각에 대해 /mid한 값 모두 합치기 => 만들 수 있는 총 조각 개수 구함
    총 조각 개수와 m값 비교해 계속 이분탐색 
*/

#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std; 

int maxLength(int m, int n, vector<int> &snack_len){
    // 정렬
    sort(snack_len.begin(), snack_len.end());

    // 가장 긴 과자 길이 
    int longest = snack_len[n-1];
    
    // 이분 탐색
    int left = 1;
    int right = longest;
    int mid;
    int sum=0;
    int max_len = 0;
    
    while(left <= right){
        mid = (left + right)/2;
        sum = 0;
        for(int i=0; i < n; i++){
            sum += snack_len[i] / mid; // 각 과자에서 mid크기 조각 최대 개수 더하기   
        }

        if(sum >= m){ // 총 조각이 m개 이상 나왔다면 
            max_len = max(mid, max_len); // 이때 최대 조각 길이 긴걸로 업데이트  
            left = mid +1;

        }else{ // 총 조각이 m개보다 적다면 
            right = mid-1;
        }
    }
    return max_len;
}

int main(){
    // 입력
    int m, n; // m:조카 수, n:과자 길이
    cin >> m >> n;
    vector<int> snack_len(n,0);
    for(int i = 0; i < n; i++){
        cin >> snack_len[i];
    }

    // 연산 & 출력
    cout << maxLength(m, n, snack_len);
}