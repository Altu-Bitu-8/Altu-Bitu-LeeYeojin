#include <iostream>
#include <cmath>

using namespace std;

int main() {
    
    // 체중,  일일 에너지 섭취량 , 역치  // 에너지 섭취량 = 기초대사량
    int W, Ia, T;
    cin >> W >> Ia >> T;

    // 기간, 다이어트 기간 에너지 섭취량, 활동 대사량
    int D , Ib, A;
    cin >> D  >> Ib >> A;

    int bmr = Ia; // 기초 대사량
    string res;  // 결과

    // 1. 일일 기초 대사량 고려X
    int weight1 = W + D * (Ib - (bmr + A)); 

    // 위험
    if (weight1 <= 0 || Ia <= 0) {
        cout << "Danger Diet\n";
    } else {
        cout << weight1 << " " << Ia << "\n";
    }

    // 2. 일일 기초 대사량 고려O
    int weight2  = W;
    int diff;
    for (int i = 0; i < D; i++){
        diff = Ib - (bmr + A);
        weight2 += diff;

        if (abs(diff) > T) {
            bmr += floor(diff/2.0);
        }

        if (weight2  <= 0 || bmr <= 0) {
            cout << "Danger Diet\n";
            return 0;
        }    
    }                                                     

    // 요요 계산
    if ( Ia > bmr ){ 
        res = "YOYO";

    } else {
        res = "NO";
    }

    cout << weight2  << " " << bmr << " " << res << "\n";
    return 0;

}