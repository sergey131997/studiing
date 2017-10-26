#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

struct Puchok {

	Puchok() {
		L.clear();
		H.clear();
		I.clear();
	}

	Puchok(int n) {
		H.resize(n + 1, -1);
	}

	void add(int i, int j, int m = 0) {
		if (H[i] == -1) {
			H[i] = L.size();
			I.push_back(j);
			L.push_back(-1);
			M.push_back(m);
			return;
		}
		int g = H[i];
		while (L[g] != -1)
			g = L[g];
		L[g] = I.size();
		L.push_back(-1);
		I.push_back(j);
		M.push_back(m);
	}

	Puchok(vector<int>& a,
		vector<int>& b) {

		if (a.size() != b.size()) {
			throw std::exception("Bad_arguments");
		}

		int m = 0;
		for (int & i : a) {
			m = max(i, m);
		}
		H.clear();
		L.clear();
		I.clear();
		H.resize(m + 1, -1);
		for (int i = 0; i < a.size(); ++i)
			add(a[i], b[i]),
			add(b[i], a[i]);
		return;
	}

	void Remove(int i, int j) {
		if (H[i] == -1)
			return;
		if (I[H[i]] == j) {
			H[i] = L[H[i]];
			return;
		}
		int g = H[i];
		while (L[g] != -1 && I[L[g]] != j)
			g = L[g];
		if (L[g] == -1)
			return;
		L[g] = L[L[g]];
	}

	int BFS() {
		int ans = 0;
		vector<int> used(H.size());
		for (int i = 0; i < H.size(); ++i) {
			if (used[i])
				continue;
			ans++;
			used[i] = 1;
			vector<int> stack;
			stack.push_back(i);
			while (stack.size()) {
				int v = stack[stack.size() - 1];
				stack.pop_back();
				int h = H[v];
				while (h != -1) {
					if (!used[I[h]]) {
						used[I[h]] = 1;
						stack.push_back(I[h]);
					}
					h = L[h];
				}
			}
		}
		return ans;
	}

	void Print() {
		for (int i = 0; i < H.size(); ++i) {
			int g = H[i];
			while (g != -1) {
				cout << i + 1 << ' ' << I[g] + 1 << endl;
				g = L[g];
			}
			cout << "\n\n\n";
		}
	}	

	void Print(std::ostream& out) {
		out << "digraph {\n";
		for (int i = 0; i < H.size(); ++i)
			for (int j = H[i]; j != -1; j = L[j])
				out << i << "->" << I[j] <<"[label="<<M[j]<<"]" << '\n';
			out << "}";
		return;
	}

	void Print(char* s) {
		std::ofstream output(s);
		Print(output);
	}

	vector<pair<int,int>> Deicstra(int i) {
		vector<int> us(H.size());
		vector<pair<int, int>> qu;
		vector<pair<int, int>> ans(H.size(), { -1, -1});
		ans[i].first = 0;
		set(qu, { 0, i });
		while (qu.size()) {
			pair<int, int> v = qu[qu.size() - 1];
			qu.pop_back();
			if (us[v.second])
				continue;
			us[v.second] = 1;
			for (int j = H[v.second]; j != -1; j = L[j]) {
				if (ans[I[j]].first == -1 ||
					ans[I[j]].first > v.first + M[j]) {
					ans[I[j]].first = v.first + M[j];
					ans[I[j]].second = v.second;
					set(qu, { ans[I[j]].first, I[j] });
				}
			}
		}
		return ans;
	}

	void set(vector<pair<int, int>>& q, pair<int, int> a) {
		if (q.empty() || q[q.size() - 1].first >= a.first) {
			q.push_back(a);
			return;
		}
		int r = q.size() - 1, l = -1;
		while (r - l > 1) {
			int m = (r + l) / 2;
			if (q[m].first > a.first)
				l = m;
			else
				r = m;
		}
		q.insert(q.begin() + r, a);
	}

	void Print(std::string s, vector<pair<int, int>> a) {
		ofstream out(s);
		out << "digraph {\n";
		for (int i = 0; i < a.size(); ++i) {
			if (a[i].second == -1)
				continue;
			out << a[i].second << "->" << i << "[label=" << a[i].first - a[a[i].second].first << "]\n";
		}
		out << "}\n";
	}

private:
	vector<int> L, H, I, M;
};

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n,m;
	cin >> n >> m;
	Puchok p(n);
	for (int i = 0; i < m; ++i) {
		int a, b, m;
		cin >> a >> b >> m;
		a--, b--;
		p.add(a, b, m);
	}
	p.Print("D:/out.gv");
	vector<pair<int,int>> ans = p.Deicstra(4);
	p.Print("D:/d.gv", ans);
	for (pair<int,int> i : ans)
		cout << i.first << ' ';	
	p.Print("D:/out.gv");
}