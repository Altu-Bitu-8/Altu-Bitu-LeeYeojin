#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main(){
    int N, K; // 바퀴 칸 수, 바퀴돌리는 횟수
    cin >> N >> K;

    vector<char> wheel(N, '?');  // ? 로 초기화 된 행운의 바퀴 배열
    unordered_map<char, int> used; // 사용 여부 확인

    int point = 0; // 현재 화살표 위치

    bool success = true;  // 유효성 확인
    int num; //돌린 칸 수 
    char letter; // 문자  

    for(int i=0; i<K; i++){
        cin >> num >> letter ;

        point = ((point - (num % N)) + N) % N; // 화살표 이동

        // 1. 해당 칸에 다른 문자가 있는 경우
        if(wheel[point] != '?' && wheel[point] != letter){
            success = false;
            break;
        }

        // 2. 동일한 문자가 다른 위치에 있는 경우
        if(used.count(letter) && used[letter] != point){
            success = false;
            break;
        }

        // 기록 및 사용 표시
        wheel[point] = letter;
        used[letter] = point; // 해당 문자가 적힌 배열 인덱스 저장장
    }

    // 출력 
    if (!success) {
        cout << "!" << "\n";
        return 0;    
    } 
    
    // 성공한 경우 해당 화살표위치 부터 출력  
    for(int j =0; j < N; j++){
        cout << wheel[(point + j) % N];
    }
    cout << "\n";
    
    return 0;

}