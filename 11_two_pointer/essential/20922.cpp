// 아이디어
/*
주어진 수열에서 부분 수열 문제 & 정렬 X => 같은 방향으로 가는 투 포인터?!
윈도우 내 수의 빈도 저장 필요-> 쌍으로 저장해야함 -> unordered_map<int,int>(삽입, 조회, 삭제 모두 O(1))  
 cf) vector<pair<int,int>>는 O(n)으로 느림-> 비효율적 
 
 좌/우 두개의 포인터 이용 
 1. 우포인터 쭉 오른쪽으로 이동해가다가 빈도수가 k가 되면 stop하고
 2. 빈도수가 k 미만일 때까지 좌포인터를 오른쪽으로 이동 
 3. k 미만이되면 이때의 부분 수열의 길이와 max 비교해 업데이트
-> 우포인터가 끝에 도달할 때까지 계속 

*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// 슬라이딩 윈도우 방식 
int findLongest(int n, int k, vector<int> num){
    unordered_map<int, int> freq; // 현재 윈도우 내 수들의 빈도
    int left = 0, right = 0;
    int max_len = 0;

    while(right < n){
        freq[num[right]]++; // 빈도 수 +1

        // k 초과시 왼쪽 포인터 이동 
        while(freq[num[right]] > k){ // k초과가 아닐 때까지 이동
            freq[num[left]]--;
            left++; // 좌포인터 오른쪽으로 한 칸 이동
        }

        max_len = max(max_len, right - left +1);
        right++; // 우포인터 오른쪽으로 한 칸 이동 
    }

    return max_len;
}

int main() {
    // 입력
    int n, k; // 주어진 수열 길이, k개 이하 
    cin >> n >> k;
    vector<int> num(n); // 주어진 수열 
    for(int i =0; i < n; i++){
        cin >> num[i]; 
    }
    
    // 연산 & 출력
    cout << findLongest(n, k, num); 
    
    return 0;
}