#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

struct Knight{
    int r, c, h, w, k, d;
};
Knight knights[31];
int damage[31];
int board[41][41];
int canMove[31]; // 이동 가능한 idx
int nr[31], nc[31]; // 다음 위치 저장
int l, n, q;

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

bool isRange(int x, int y){ return (x < 0 || x >= l || y < 0 || y >= l); }

bool isMove(int idx, int dir){
    for(int i=1; i<=n; i++){
        damage[i] = 0;
        canMove[i] = 0;
        nr[i] = knights[i].r; nc[i] = knights[i].c;
    }

    queue<int> q;
    q.push(idx);
    canMove[idx] = 1;

    while(!q.empty()){
        int curr = q.front(); q.pop();

        nr[curr] += dr[dir]; nc[curr] += dc[dir];

        if(isRange(nr[curr], nc[curr])) return false;
        for(int i = nr[curr]; i <= nr[curr] + knights[curr].h - 1; i++) {
            for(int j = nc[curr]; j <= nc[curr] + knights[curr].w - 1; j++) {
                if(board[i][j] == 1) damage[curr]++;
                if(board[i][j] == 2) return false;
            }
        }

        for(int i=1; i<=n; i++){
            if(canMove[i] || knights[i].k <= knights[i].d) continue;
            if(knights[i].r > nr[curr] + knights[curr].h - 1 || nr[curr] > knights[i].r + knights[curr].h - 1) continue;
            if(knights[i].c > nc[curr] + knights[curr].w - 1 || nc[curr] > knights[i].c + knights[curr].w - 1) continue;
            
            canMove[i] = true;
            q.push(i);
        }
    }

    damage[idx] = 0;
    return true;
}

void moving(int idx, int dir){
    if(knights[idx].k <= knights[idx].d) return;
    if(!isMove(idx, dir)) return;

    for(int i=1; i<=n; i++){
        if(canMove[i]){
            knights[i].r = nr[i];
            knights[i].c = nc[i];
            knights[i].d += damage[i];
        }
    }
}

int main() {
    cin >> l >> n >> q;
    for(int i=0; i<l; i++){
        for(int j=0; j<l; j++) cin >> board[i][j];
    }

    for(int i=1; i<=n; i++){
        int r, c, h, w, k; cin >> r >> c >> h >> w >> k;
        knights[i] = {r-1, c-1, h, w, k, 0};
    }

    for(int i=0; i<q; i++){
        int a, b; cin >> a >> b;
        moving(a, b);
    }

    long long ans = 0;
    for(int i = 1; i <= n; i++) {
        if(knights[i].k > knights[i].d) {
            ans += knights[i].d;
        }
    }
    cout << ans;
    return 0;
}