#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

struct Node {
	long long id, w, gone, line;

	Node* prev;
	Node* next;
};

Node nodes[100001];
unordered_map<long long, long long> id_map;

struct List {
	Node head;
	Node tail;
	int broke;

	void link(Node* front, Node* back) {
		front->next = back;
		back->prev = front;
	}

	void init() { link(&head, &tail); broke = 0; }

	void insert(Node* node) {
		link((tail.prev), node);
		link(node, &tail);
	}

	bool empty() { return head.next == &tail; }
};

List belt[11];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int q; cin >> q;
	long long n, m;
	for (int tc = 0; tc < q; tc++) {
		int cmd; cin >> cmd;
		if (cmd == 100) {
			cin >> n >> m;

			for (int i = 0; i <= m; i++) belt[i].init();

			for (long long i = 0; i < n; i++) {
				cin >> nodes[i].id;
				nodes[i].gone = 0; nodes[i].line = i / (n / m);
				id_map[nodes[i].id] = i;
			}
			for (int i = 0; i < n; i++) cin >> nodes[i].w;

			for(long long i=0; i<n; i++) belt[i / (n / m)].insert(&nodes[i]);
		}
		else if (cmd == 200) {
			long long w_max; cin >> w_max;
			long long sum = 0;
			for (int i = 0; i < m; i++) {
				if (belt[i].broke) continue;

				Node* curr = belt[i].head.next;
				if ((curr->w) <= w_max) {
					sum += curr->w;
					curr->gone = 1;
					belt[i].link(curr->prev, curr->next);
				}
				else {
					belt[i].link(curr->prev, curr->next);
					belt[i].link(belt[i].tail.prev, curr);
					belt[i].link(curr, &belt[i].tail);
				}
			}
			cout << sum << '\n';
		}
		else if (cmd == 300) {
			long long r_id; cin >> r_id;
			if (id_map.count(r_id) == 1) {
				long long now = id_map[r_id];
				if (nodes[now].gone) cout << "-1\n";
				else {
					belt[nodes[now].line].link(nodes[now].prev, nodes[now].next);
					nodes[now].gone = 1;
					cout << r_id << "\n";
				}
			}
			else cout << "-1\n";
		}
		else if (cmd == 400) {
			long long f_id; cin >> f_id;
			if (id_map.count(f_id) == 1) {
				long long now = id_map[f_id];
				if (nodes[now].gone) cout << "-1\n";
				else {
					belt[nodes[now].line].link(belt[nodes[now].line].tail.prev, belt[nodes[now].line].head.next);
					belt[nodes[now].line].link(nodes[now].prev, &belt[nodes[now].line].tail);
					belt[nodes[now].line].link(&belt[nodes[now].line].head , &nodes[now]);
					cout << (nodes[now].line) + 1 << "\n";
				}
			}
			else cout << "-1\n";
		}
		else {
			long long b_num; cin >> b_num;
			if (belt[b_num - 1].broke) { cout << "-1\n"; continue; }
			
			belt[b_num - 1].broke = 1;
			long long move_idx = (b_num % m);

			while (1) {
				if (belt[move_idx].broke == 0) {
					Node* curr = belt[b_num-1].head.next;
					while (curr != &belt[b_num - 1].tail) {
						curr->line = move_idx;
						curr = curr->next;
					}

					belt[move_idx].link(belt[move_idx].tail.prev, belt[b_num - 1].head.next);
					belt[move_idx].link(belt[b_num - 1].tail.prev, &belt[move_idx].tail);
					break;
				}
				move_idx = (move_idx + 1) % m;
			}
			cout << b_num << '\n';
		}
	}
	return 0;
}