// 아이디어
/* 
무조건 연속된 5개가 되는 경우는 1번만 일어남!
출력시 5개 돌 중 [i][j]에서 j와 i가 가장 작은 i,j 출력 (j가 우선(왼쪽 부터이니까))
* 5개가 연속되는 경우
1. 가로 5개
2. 세로 5개
3. 오른쪽 아래 대각선 5개 \ 
4. 왼쪽 아래 대각선 5개 / 
* 0이 아닌 모든 돌들에 대해서 위의 경우를 체크, 만약 true가 되는 경우 그 돌이 win!
* 6목 체크 필요!
이때 border보다 밖에 있는 돌들은 체크하지 않아도 됨(어차피 불가한 경우)
*/

#include <iostream>
#include <vector>
#include <string> // getline() 
#include <sstream> // istringstream ()  // 공백 기준 파싱 

using namespace std; 

vector<vector<int>> table; // 바둑판
int n; // 바둑판 행 수 (= 열 수) 

// 1. 가로 5개 연속 
bool case1(int &o, int &i, int &j){
    if(j > n-5){ return false;}  // 할 필요가 없음 (border 밖)
    for(int k =1; k <5; k++){
        if (table[i][j+k] != o){ // 연속 깨짐
            return false;
        }
    }
    // 양 끝 체크: 6목 이상 방지
    if(j + 5 < n && table[i][j+5] == o) return false; 
    if(j > 0 && table[i][j-1] == o) return false;
    return true;
}

// 2. 세로 5개 연속 
bool case2(int &o, int &i, int &j){
    if(i > n-5){ return false; }  // 할 필요가 없음 (border 밖)
    for(int k =1; k <5; k++){
        if (table[i+k][j] != o){ // 연속 깨짐
            return false;
        }
    }
    // 양 끝 체크: 6목 이상 방지
    if(i + 5 < n && table[i+5][j] == o) return false; 
    if(i > 0 && table[i-1][j] == o) return false;
    return true;
}


// 3. 오른쪽 아래 대각선 5개 '\' 
bool case3(int &o, int &i, int &j){
    if((i > n-5) || (j > n-5)){ return false; }  // 할 필요가 없음 (border 밖)
    for(int k =1; k <5; k++){
        if (table[i+k][j+k] != o){ // 연속 깨짐
            return false;
        }
    }
    // 양 끝 체크: 6목 이상 방지
    if(i + 5 < n && j + 5 < n && table[i+5][j+5] == o) return false; 
    if(i > 0 && j > 0 && table[i-1][j-1] == o) return false;
    return true;
}

// 4. 왼쪽 아래 대각선 '/' 
bool case4(int &o, int &i, int &j) {
    if (i < 4 || j > n - 5) return false;
    for (int k = 1; k < 5; k++) {
        if (table[i - k][j + k] != o) return false;
    }
    if (i >= 5 && j < n - 5 && table[i - 5][j + 5] == o) return false;
    if (i < n - 1 && j > 0 && table[i + 1][j - 1] == o) return false;
    return true;
}


bool checkTheCase(int &owner, int &i, int &j){
    bool res1 = case1(owner, i, j);
    bool res2 = case2(owner, i, j);
    bool res3 = case3(owner, i, j);
    bool res4 = case4(owner, i, j);
    if(res1 || res2 || res3 || res4){
        return true;
    }
    return false;
}


void playGame(int &winner, int &row_num, int &col_num){
    int owner; // 돌 주인 

    for(int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if(table[i][j] != 0){
                owner = table[i][j];
                if(checkTheCase(owner, i, j)){
                    winner = owner;
                    row_num = i + 1; // 진짜 바둑둑판은 1부터 시작하므로 +1
                    col_num = j + 1;
                    return; // 5개 연속나오면 확인 종료 
                }
            }
        }
    }
    
}


int main () {
    // 입력
    string line;

    // *테이블 내용 이차원 배열에 저장 
    while(getline(cin, line)){ // EOF까지 반복
        istringstream iss(line); // 공백으로 파싱 
        vector<int> row; // 한 개의 행 저장하는 임시 배열
        int num;
        while (iss >> num) { // 한 줄의 각 원소들 임시 배열에 저장 
            row.push_back(num);
        }
        if (!row.empty()) {
            table.push_back(row); // 저장한 한 행 진짜 table에 저장! 
        }
    } 
    n = table.size(); // 전체 행 수 

    // 연산 
    int winner = 0; 
    int row_num, col_num;
    playGame(winner, row_num, col_num);

    // 출력
    cout << winner << "\n";
    if(winner != 0){
        cout << row_num << " " << col_num;
    }


    return 0;
}
