#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 자리 수 합 메서드
int sum(const string &s){
    int sum = 0;

    // 한글자씩 숫자인 경우 합에 더하기기
    for(char c : s){
        if (isdigit(c)){
            sum += c - '0';  // string이므로 숫자로 계산하기 위해 -'0'
        }
    }
    return sum;
}

// false면 swap
bool comp(const string &a, const string &b){
    // 길이가 짧은 것 먼저
    if (a.length() != b.length() ){
        return a.length() < b.length();  // a가 b보다 작다
    }

    // 자리 수 합이 작은 것 먼저
    int sum_a = sum(a), sum_b = sum(b);
    if( sum_a != sum_b ){
        return sum_a < sum_b;
    }

    // 사전 순서 
    return a < b;
}


int main() {

    // 입력 개수 받기
    int n;
    cin >> n;

    vector<string> serial(n);
    
    for(int i = 0; i < n; i++) {
        cin >> serial[i];
    }

    // 정렬
    sort(serial.begin(), serial.end(), comp);

    // 결과
    for (string s : serial ){
        cout << s << "\n";
    }

    return 0;

}