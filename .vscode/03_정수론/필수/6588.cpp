#include <iostream>
#include <vector>

using namespace std;

const int MAX = 1000000;
vector<bool> is_prime(MAX + 1, true); // 소수 판별 배열 

// 에라토스테네스의 채 방법으로 n보다 작은 소수를 모두 찾아두고,
// 가장 작은 소수(a) 부터 n-(작은소수(a))가 소수인거 찾으면 그게 b-a가 가장 큰 경우 
 
void findPrime(){
    // 0과 1은 소수가 아니므로 먼저 제거
    is_prime[0] = is_prime[1] = false;
    
    for(int i =2; i*i <= MAX; i++){ // 제곱근i 까지만 확인하면 됨
        //이미 지워진 수 이면 탐색 X
        if (is_prime[i]) {
            for (int j = i * i; j <= MAX; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n; // 주어진 숫자

    // 미리 에라토스테네스의 체를 사용해 소수인 것 구하기
    findPrime();

    while(true){
        cin >> n;
        if(n == 0){ break;} // 종료 조건

        bool is_valid = false; 
        int prime_small, prime_big; // 두 소수

        // 배열에서 가장 큰 소수 부터 짝꿍 찾기
        // 두 홀수 소수의 합이라 추측  
        for(int i = 3; i <= n - 3; i += 2){
            if(is_prime[i]){
                if(is_prime[n-i]){
                    prime_small = i;
                    prime_big = n-i;
                    is_valid = true;
                    break;
                }
            }
        }

        // 출력
        if(!is_valid){
            cout <<  "Goldbach's conjecture is wrong." << "\n";
        } else{
            cout << n << " = " << prime_small << " + " << prime_big << "\n";
        }
    }

    return 0;
}