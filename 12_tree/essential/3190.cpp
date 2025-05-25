// 아이디어
/*
2차원 배열 0으로 초기화 
// 사과 있는 곳 -1로 표시 
// 뱀이 있는 곳은 1로 표시 
북동남서  dx[4] = {0, 1, 0, -1}, dy[4] = {-1, 0, 1, 0}; 이용용
// 현재 뱀의 방향 : 북동남서 = 0123
// 뱀의 이동 (count++)
    // 다음 칸에 사과가 있으면(-1)이면 1로 표시
    // 다음 칸에 사과 없으면 (0)이면 1로 표시 & 꼬리 칸 0으로 변경 & 꼬리 업데이트
    // 다음 칸이 인덱스를 벗어나거나, 1이면 -> stop!
// 방향 전황 체크 
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int dx[4] = {0, 1, 0, -1}, dy[4] = {-1, 0, 1, 0}; // 북 동 남 서

int snakeMove(int n, int k, int l, vector<vector<int>> &board, queue<pair<int, char>> &change){
    int count = 0; // 시간
    int direc = 1; // 뱀 머리 방향 : 북=0, 동=1, 남=2, 서=3
    queue<pair<int, int>> snake;  // 뱀 몸통 front=꼬리, back=머리
    snake.push({1, 1});
    board[1][1] = 1;
    int nx, ny; // 다음 칸 

    while(true){
        // 0. 시간 추가 
        count++; 
        
        // 1. 다음 칸 구하기  
        nx = snake.back().first + dy[direc]; // 다음 행
        ny = snake.back().second + dx[direc]; // 다음 열

        // 2. 예외 체크
        // 범위 벗어남 or 몸통에 닿음
        if(board[nx][ny] == -2 || board[nx][ny] == 1){
           break;
        }

        // 3. 사과가 없는 경우 - 꼬리 삭제
        if(board[nx][ny] != -1)
        {
            board[snake.front().first][snake.front().second] = 0; // 보드에서 꼬리 삭제
            snake.pop(); // 뱀 몸통에서 꼬리 삭제 
        }

        // 4. 뱀 머리 추가(이동)
        board[nx][ny] = 1; // 뱀 있음 표시
        snake.push({nx, ny});// 새로운 뱀 머리

        // 6. 방향 전환
        if(!change.empty() && count == change.front().first)
        {
            if(change.front().second  == 'D'){
                direc = (direc + 1) % 4; //오른쪽으로 전환
            }
            else if(change.front().second  == 'L'){
                direc = (direc + 3) % 4; //왼쪽으로 전환
            }
            change.pop();
        }

    }

    return count;
    
}

int main() {
    // 입력
    int n, k, l; // 보드 크기, 사과개수, 방향 변환 횟수

    // 보드 초기화 
    cin >> n;
    // 이차원 벡터 n+2*n+2사이즈, 0으로 초기화 
    vector<vector<int>> board(n+2, vector<int>(n+2,0)); 
    for(int a=0; a < n+2; a++){ // 경계 표시
        board[0][a] = -2;
        board[a][0] = -2;
        board[n+1][a] = -2;
        board[a][n+1] = -2;
    }

    // 사과 넣기 
    cin >> k;
    int p,q;
    for(int i = 0; i < k; i++){
        cin >> p >> q;
        board[p][q] = -1; // 보드에 사과 표시 
    }

    // 방향 전환 리스트 저장 
    cin >> l; 
    queue<pair<int, char>> change;// 방향 변환 
    int x; // x초가 끝난 후
    char c; // c방향으로
    for(int j=0; j < l; j++){
        cin >> x >> c;
        change.push({x,c});
    }

    // 연산 & 출력
    cout << snakeMove(n, k, l , board, change);
    
    return 0;
}