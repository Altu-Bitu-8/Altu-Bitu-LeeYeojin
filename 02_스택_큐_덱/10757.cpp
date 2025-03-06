#include <iostream>
#include <cmath>

using namespace std;

int main(){

    string A, B, sum;
    cin >> A;
    cin >> B;

    int temp = 0;
    int carry = 0; // 올림 수수

    // 두 숫자의 길이를 맞추기 위해 0을 앞에 채워줌
    while (A.size() < B.size()) A = "0" + A;
    while (B.size() < A.size()) B = "0" + B;

    for (int i= A.size()-1 ; i >= 0; i--){
        temp = (A[i] - '0') + (B[i] -'0') + carry;
        carry = temp/10;
        sum = char(temp % 10 +'0') + sum;
    }

    if(carry == 1){
        sum = '1' + sum;
    }

    cout << sum << "\n";

    return 0;
}