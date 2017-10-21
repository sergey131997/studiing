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

	void add(int i, int j) {
		if (H[i] == -1) {
			H[i] = L.size();
			I.push_back(j);
			L.push_back(-1);
			return;
		}
		int g = H[i];
		while (L[g] != -1)
			g = L[g];
		L[g] = I.size();
		L.push_back(-1);
		I.push_back(j);
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
					out << i << "->" << I[j] <<'\n';
			out << "}";
		return;
	}

	void Print(char* s) {
		std::ofstream output(s);
		Print(output);
	}
private:
	vector<int> L, H, I;
};

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n,m;
	cin >> n >> m;
	Puchok p(n);
	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		p.add(a, b);
	}
	p.Print("D:/out.gv");
	cout << p.BFS();
}