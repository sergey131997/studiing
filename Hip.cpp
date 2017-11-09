#define _CRT_SECURE_NO_WARNINGS
#include<iostream>

using namespace std;

class Hip {
public:
	Hip() {};

	~Hip() {
		if (mas_ != nullptr)
			delete[] mas_;
	}

	void build(int* old, int n) {
		if (mas_ != nullptr)
			delete mas_;
		n_ = n;
		mas_ = new int[n];
		mec(mas_, old, n);
		for (int i = 0; i * 2 + 1 < n; ++i) {
			int child = ((2*i + 2 >= n || mas_[2 * i + 1] > mas_[2 * i + 2])
				? 2 * i + 1 : 2 * i + 2);
			if (mas_[i] <= mas_[child])
				swap(mas_[i], mas_[child]);
		}
	}

	void mec(int* a, int* b, int n) {
		for (int i = 0; i < n; ++i)
			a[i] = b[i];
	}

	int* sort() {
		int* cur = new int[n_];
		int* dst = new int[n_];
		mec(cur, mas_, n_);
		int min_ = cur[0];
		
		for (int i = 0; i < n_; ++i) {
			dst[i] = cur[0];
			cur[0] = cur[n_ - i - 1];
			for (int j = 0; j *2 + 1  < (n_ - i);) {
				int child = ((2 * j + 2 >= (n_ - i) || cur[2 * j + 1] > cur[2 * j + 2])? 
					2 * j + 1 : 2 * j + 2);
				if (cur[j] < cur[child]) {
					swap(cur[j], cur[child]);
					j = child;
				}
				else
					break;
			}
		}
		delete[] cur;
		return dst;
	}
	
private:
	int * mas_ = nullptr;
	int n_ = 0;
	int min = 0;
};

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int* b = new int[14]{39,211,12,5,60,132,4,6,0,12,12,4,5,6};
	Hip a;
	a.build(b,14);
	int* m = a.sort();
	for (int i = 0; i < 14; ++i)
		cout << m[i] << ' ';
	delete[] m;
}