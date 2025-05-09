// 상근이가 가진 n개의 카드 정렬 후,
// m개의 정수에 대해 이분 탐색 반복
#include <iostream>
#include <vector>
#include <algorithm>
 
using namespace std;

int binarySearch(int target, int n, vector<int> &s_card){
    int left = 0;
    int right = n-1;
    int mid;
    
    while(left <= right){
        mid = (right+left)/2;
        if(s_card[mid] == target){
            return 1;
        } 
        else if (s_card[mid] < target){
            left = mid+1;
        }
        else{
            right = mid -1;
        }
    }
    return 0;
}

void checkCards(int &n, int &m ,vector<int> &s_card, vector<int> &q_card, vector<int> &res){
    // 각 q_card에 대해서 이분 탐색으로 확인
    // 1. s_card 정렬
    sort(s_card.begin(), s_card.end());

    // 2. 이분 탐색 
    int target =0 ;
    for(int i=0; i < m; i++){
        target = q_card[i]; // 확인할 숫자 
        res[i] = binarySearch(target, n, s_card);
    }
}

int main() {
    // 입력
    int n, m;
    cin >> n;
    vector<int> s_card(n,0); // 상근이가 가진 카드
    for(int i = 0; i < n; i++){
        cin >> s_card[i];
    }

    cin >> m;
    vector<int> q_card(m,0); // 확인할 카드 
    for(int j = 0; j < m; j++){
        cin >> q_card[j];
    }
    vector<int> res(m,0); // 각 q_card에 대한 결과 저장

    // 연산
    checkCards(n, m, s_card, q_card, res);

    // 출력
    for(int k=0; k < m; k++){
        cout << res[k] << " ";
    }
    return 0;  
}