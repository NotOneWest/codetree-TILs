#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int r, c, k;
int forest[73][70]; // 초기 골렘 위치 + 출구 R이 3 더 필요
bool isExit[73][70]; // 초기 골렘 위치 + 출구 R이 3 더 필요
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };
int answer;

bool inRange(int x, int y) { return 3 <= x && x < (r+3) && 0 <= y && y < c; }

void resetForest() {
	for (int i = 0; i < (r+3); i++) {
		for (int j = 0; j < c; j++) {
			forest[i][j] = 0;
			isExit[i][j] = false;
		}
	}
}

bool canGo(int x, int y) {
	bool ans = (x < (r + 2) && (1 <= y && y < (c - 1)));

	ans = ans && (forest[x - 1][y - 1] == 0);
	//ans = ans && (forest[x - 1][y] == 0);
	ans = ans && (forest[x - 1][y + 1] == 0);

	ans = ans && (forest[x][y] == 0);
	ans = ans && (forest[x + 1][y] == 0);
	ans = ans && (forest[x][y - 1] == 0);
	ans = ans && (forest[x][y + 1] == 0);

	return ans;
}

int bfs(int x, int y) {
	int res = x;
	queue<pair<int, int>> q;
	bool visited[73][70];
	for (int i = 0; i < (r + 3); i++) {
		for (int j = 0; j < c; j++) visited[i][j] = false;
	}

	q.push(make_pair(x, y));
	visited[x][y] = true;
	while (!q.empty()) {
		int cx = q.front().first, cy = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = cx + dx[i], ny = cy + dy[i];
			if (inRange(nx, ny) && !visited[nx][ny]) {
				if (forest[nx][ny] == forest[cx][cy] || (forest[nx][ny] != 0 && isExit[cx][cy])) {
					q.push(make_pair(nx, ny));
					visited[nx][ny] = true;
					res = max(res, nx);
				}
			}
		}
	}

	return res;
}

void down(int x, int y, int d, int id) { // 골렘 이동
	if (canGo(x + 1, y)) down(x + 1, y, d, id);
	else if (canGo(x + 1, y - 1)) down(x + 1, y - 1, (d + 3) % 4, id);
	else if (canGo(x + 1, y + 1)) down(x + 1, y + 1, (d + 1) % 4, id);
	else {
		if (!inRange(x - 1, y - 1) || !inRange(x + 1, y + 1)) resetForest();
		else {
			forest[x][y] = id;
			for (int i = 0; i < 4; i++) forest[x + dx[i]][y + dy[i]] = id;
			isExit[x + dx[d]][y + dy[d]] = true;
			answer += (bfs(x, y) - 2);
		}
	}
}

int main() {
	cin >> r >> c >> k;
	for (int i = 0; i < k; i++) {
		int c, d; cin >> c >> d;
		down(1, c - 1, d, i + 1);
	}
	cout << answer << '\n';
	return 0;
}