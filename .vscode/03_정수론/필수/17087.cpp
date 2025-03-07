#include <iostream>
#include <vector>
#include <cmath> // abs()

using namespace std;

/* (동생의 위치 - 수빈이의 위치) 들의 최대 공약수 구하기 */

// (동생의 위치 - 수빈이의 위치) 배열 구하기
vector<int> diffSbtwA(int S, int N, vector<int> &A){
    vector<int> diff(N);
    for(int i=0 ; i<N; i++){
        diff[i] = abs(A[i]- S);
    }

    return diff;
}

// 최대 공약수 구하기 - 유클리드 호제법
int getGcd(int a, int b){
    // 유클리드 호제법
    while(b){
        a %= b;
        swap(a,b);
    }
    return a;
}

int main() {

    int N; // 동생 N명
    int S; // 수빈이 위치
    cin >> N >> S ;

    vector<int> A(N); //동생 위치
    for(int i=0; i < N; i++){
        cin >> A[i];
    }

    // (동생의 위치 - 수빈이의 위치) 배열 구하기
    vector<int> diff = diffSbtwA(S, N, A);

    // 최대 공약수 구하기 - 앞에서부터 비교
    int D = diff[0];
    for(int j = 1; j < N ; j++){
        D = getGcd(D, diff[j]);
    }

    cout << D << "\n";

    return 0;
}