#include <iostream>
#include <cstring>
using namespace std;

struct Knight{
    int r, c, h, w, k, d;
};
Knight knights[31];
int canMove[31];
int board[41][41];
int k_board[41][41];
int l, n, q;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

bool isRange(int x, int y){ return (x < 0 || x >= l || y < 0 || y >= l); }

bool isMove(int idx, int d){
    int x, y;
    if(d == 0){ x = knights[idx].r; y = knights[idx].c; }
    else if(d == 1){ x = knights[idx].r; y = knights[idx].c + knights[idx].w - 1; }
    else if(d == 2){ x = knights[idx].r + knights[idx].h - 1; y = knights[idx].c; }
    else{ x = knights[idx].r; y = knights[idx].c; }

    if(d % 2){
        for(int i=0; i<knights[idx].h; i++){
            int nx = x + i + dx[d], ny = y + dy[d];
            if(isRange(nx, ny)) return false;
            if(board[nx][ny] == 2) return false;
            if(k_board[nx][ny] >= 10 && !canMove[k_board[nx][ny] / 10]){
                if(!isMove(k_board[nx][ny] / 10, d)) return false;
                else canMove[k_board[nx][ny] / 10] = 1;
            }
        }
    } else{
        for(int i=0; i<knights[idx].w; i++){
            int nx = x + dx[d], ny = y + i + dy[d];
            if(isRange(nx, ny)) return false;
            if(board[nx][ny] == 2) return false;
            if(k_board[nx][ny] >= 10 && !canMove[k_board[nx][ny] / 10]){
                if(!isMove(k_board[nx][ny] / 10, d)) return false;
                else canMove[k_board[nx][ny] / 10] = 1;
            }
        }
    }

    return true;
}

void moving(int idx, int d){
    memset(canMove, 0, sizeof(canMove));
    if(!isMove(idx, d)) return;

    canMove[idx] = 1;
    for(int i=1; i<=n; i++){
        if(canMove[i]){ knights[i].r += dx[d]; knights[i].c += dy[d]; }
    }
}

void update(int start){
    memset(k_board, 0, sizeof(k_board));
    for(int i=1; i<=n; i++){
        for(int x=0; x<knights[i].h; x++){
            for(int y=0; y<knights[i].w; y++){
                k_board[knights[i].r+x][knights[i].c+y] = i * 10;
                if(canMove[i]){
                    if(i != start){
                        if(board[knights[i].r+x][knights[i].c+y] == 1) knights[i].d++;
                    }
                }
                
            }
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
        for(int x=0; x<h; x++){
            for(int y=0; y<w; y++){
                k_board[r-1+x][c-1+y] = i * 10;
            }
        }
    }

    for(int i=0; i<q; i++){
        int a, b; cin >> a >> b;
        if(knights[a].k <= knights[a].d) continue;

        moving(a, b);
        update(a);
    }

    int ans = 0;
    for(int i=1; i<=n; i++){
        if(knights[i].k > knights[i].d) ans += knights[i].d;
    }
    cout << ans;
    return 0;
}