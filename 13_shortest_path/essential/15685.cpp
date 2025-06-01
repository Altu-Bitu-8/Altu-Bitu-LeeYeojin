// 아이디어
/*
정사각형? => 네 꼭짓점이 모두 true이면 정사각형!
즉, 평면에 드래곤 커브를 표시하고 정사각형 개수 메소드로 구하면 됨!
*/
#include <iostream>
#include <vector>

using namespace std;

const int SIZE = 100; // 평면 크기 

// 방향: 우(0), 상(1), 좌(2), 하(3)
int dy[4] = { 0, -1, 0, 1 }; // y좌표(열)의 변화
int dx[4] = { 1, 0, -1, 0 }; // x좌표(행)의 변화 

// 1x1 정사각형 개수 계산
int cntSquares(vector<vector<bool>>& plane) {
    int ans = 0; // 개수 초기화 
    for (int i = 0; i < SIZE; i++) { // 행의 인덱스 
        for (int j = 0; j < SIZE; j++) { // 열의 인덱스 순회 
            // 현재 칸과 오른쪽, 아래, 오른쪽 아래 칸이 모두 true면 정사각형임 
            if (plane[i][j] && plane[i + 1][j] && plane[i][j + 1] && plane[i + 1][j + 1]) {
                ans++; // 정사각형 개수  +1
            }
        }
    }
    return ans; // 총 개수 반환 
}

// 평면에 드래곤 커브를 표시
void drawDragonCurve(vector<vector<bool>>& plane, int x, int y, int d, int g) {
    vector<int> direct; // 현재 방향 저장
    plane[y][x] = plane[y + dy[d]][x + dx[d]] = true; // 평면에 표시 (초기화)
    
    x += dx[d]; // x좌표 
    y += dy[d]; // y좌표 
    direct.push_back(d);  // 처음 방향 저장 

    while (g--) { // 1 ~ g 세대
        int size_d = direct.size(); // 저장된 방향 개수 
        for (int j = size_d - 1; j >= 0; j--) { // 방향 계산
            int next_d = (direct[j] + 1) % 4; // 시계 방향으로 90도 회전 
            x += dx[next_d]; // x좌표 움직이기
            y += dy[next_d]; // y좌표 움직이기
            plane[y][x] = true; // 평면에 표시
            direct.push_back(next_d); // 새로운 방향 저장 
        }
    }
}

/*
* 규칙
* 0 세대: 0
* 1 세대: 0 1
* 2 세대: 0 1 2 1
* 3 세대: 0 1 2 1 2 3 2 1
* ...
* N 세대: concat((N-1세대), ((N-1세대 거꾸로) + 1)%4)
* 평면(좌측 상단이 (0, 0))에 드래곤 커브를 그린 후 정사각형의 개수를 계산
* 드래곤 커브는 평면 밖으로 나가지 않음으로 범위를 확인할 필요 없음
* 1. 0 세대의 드래곤 커브를 먼저 저장 (초기 조건)
* 2. 세대를 거듭하면서 드래곤 커브를 그림 (규칙을 파악하는 것이 중요)
* 3. 드래곤 커브가 그려진 평면 상의 정사각형의 개수 계산 (네 꼭짓점 확인)
*/

int main()
{
    int n, x, y, d, g; // 커브 개수, 시작점 x좌표, 시작점 y좌표, 방향 
    vector<vector<bool>> plane(SIZE + 1, vector<bool>(SIZE + 1, false)); // 평면

    // 입력
    cin >> n; // 커브 개수 

    // 연산
    while (n--) { // n개의 드래곤 커브 그리기
        cin >> x >> y >> d >> g; // 시작점 x좌표, 시작점 y좌표, 방향, 세대 
        drawDragonCurve(plane, x, y, d, g); // 연산 - 커브 그리기 
    }

    // 출력
    cout << cntSquares(plane) << '\n'; // 정사각형 수 반환 
    return 0;
}