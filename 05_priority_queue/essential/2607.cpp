// *서로 비슷한 단어 - 아이디어*

// 1. 알파벳 빈도를 기록하는 배열을 생성하고,
// 2. 한 단어씩 읽어서 해당 알파벳-'A' 번 인덱스에 +1 증가
// 3. 이제 기준 단어의 배열과 비교 단어의 배열의 각 원소마다 비교
//    만약 값이 다른 인덱스의 원소 등장시 
//        first[] - target[] = 1 : 기준 단어가 비교 단어보다 하나 더 많은 경우 -> only_first++
//        first[] - target[] = -1 : 비교단어가 하나 더 많은 경우 -> only_target++
//        둘 다 아닌 경우(차가 1이 아닌 경우): 비슷한 단어 아님
// 4. 다 돌린 결과 (1,0)(0,1)(0,0)(1,1) 인 경우 -> 비슷한 단어

#include <iostream>
#include <vector>

using namespace std;

const int ALPHABET = 26;

// 단어 빈도수 배열 저장
void countAlphabetNum(vector<int> &v, string str){

    int length = str.length();
    for(int i = 0; i < length; i++){
        v[str[i]-'A']++; // 0번 인덱스에 A의 빈도 저장장
    }

}

// 비슷한 단어인지 확인
bool similarWord(vector<int> &first, string target_word){

    vector<int> target(26,0); // 비교 단어의 빈도수 배열
    int only_first = 0;
    int only_target = 0;

    countAlphabetNum(target, target_word); // 비교 단어 빈도 배열 생성  
    
    for(int i = 0; i <ALPHABET ; i++){
        if(first[i] == target[i]){
            continue;
        }
        else if(first[i] - target[i] == 1){
            only_first++;
        }
        else if(first[i] - target[i] == -1){
            only_target++;
        }
        else{
            return false;
        }
    }

    if((only_first == 0 || only_first == 1) && (only_target == 0 || only_target == 1)){
        return true;
    }
    return false;

}


int main() {

    int n;
    string first_word, target_word;
    int sum = 0;  // 총 비슷한 단어 수   
    vector<int> first(26,0); // 기준 단어의 빈도수 배열
    
    // 입력
    cin >> n;
    cin >> first_word;

    // 연산 
    countAlphabetNum(first, first_word); // 기준단어 빈도 배열 생성
    n--; 

    while(n--){
        cin >> target_word;
        if(similarWord(first, target_word)){
            sum++;
        }
    }

    // 출력
    cout << sum << "\n";

    return 0;
}
