// 5639 이진 검색 트리
#include <iostream>
#include <vector>

using namespace std;

// 후위 순회 함수 (왼 -> 오 -> 루트)
    // 왼쪽 & 오른쪽 서브 트리에 대해 재귀적으로 후위순회 수행 
void postOrder(int left, int right, vector<int> &tree) 
{
    if (left > right) // 종료 조건 
    {
        return;
    }

    int root = tree[left]; // 이해하기 쉽게 루트 따로 저장해주자!

    // 루트보다 처음으로 큰 노드 인덱스 찾기 -> left, right새로 설정하기 위해서!
    int tmp = left + 1;
    for (int i = left + 1; i <= right; i++)
    {
        if (tree[i] > root) // 루트보다 처음으로 큰 노드 = 루트의 오른쪽 자식노드 
        {
            tmp = i;
            break;
        }
    }

    // 후위 순회 순으로 다시 탐색 (왼 -> 오 -> 루트)

    // 1. 왼쪽 서브트리에 대해 후위 순회 (left+1가 left(root)의 왼쪽 자식이므로)
        // 루트보다 작은 노드들 
    postOrder(left + 1, tmp - 1, tree); // 30 24 5 28 45 
    
    // 2. 오른쪽 서브트리에 대해 후위 순회 (tmp가 left(root)의 오른쪽쪽 자식이므로)
        // 루트보다 큰 노드들
    postOrder(tmp, right, tree);  // 98 52 60

    // 3. left, right 탐색 끝났으므로 root 출력
    cout << root << '\n'; // 50
}

/*
 * 이진 검색 트리 : 루트의 왼쪽
 * 이진 검색 트리를 전위 순회환 결과 -> 후위 순회한 결과
 * 전위 순회 : 루트 왼쪽 오른쪽 -> 후위 순회 : 왼쪽 오른쪽 루트
 *  -> 탐색 결과 : 루트 -> 루트보다 작은 노드(왼쪽) -> 루트보다 큰 노드(오른쪽)
 *  -> 루트를 기준으로 left, right 나눠서 후위 순회 순으로 다시 탐색
 */

int main()
{

    ios::sync_with_stdio(false); // 빠른 입츌력을 위함 
    cin.tie(0);
    cout.tie(0);

    // 입력
    int num;
    vector<int> tree; // 트리
    while (cin >> num)  // 하나씩 입력 받아서 
    {
        tree.push_back(num); // 트리에 저장 :전위 순회 순서로 저장된 것
    }

    // 연산 + 출력
    postOrder(0, tree.size() - 1, tree); // 50 30 24 5 28 45 98 52 60
}

