
#include <iostream>
#include <exception>
#include "ComplexNumber.h"
#include "Matrice.h"
#include <algorithm>
using namespace std;
int main() {
	Matrice <ComplexNumber> *vec, Im, A, B;
	try {
		int N, M;
		cin >> N >> M;
		vec = new Matrice <ComplexNumber>[N];
		Im.matI(M);
		cin >> A;
		for (int i = 0; i < N; ++i) {
			vec[i] = Im * ComplexNumber(i + 3, i - 1) + A * ComplexNumber(2 - i, i + (1 - i) * (3 - i));
		}
		sort(vec, vec + N);
		for (int i = 0; i < N; ++i)
			cout << vec[i] << '\n' << '\n';
	}
	catch (const char* exc) {
		cerr << exc << '\n';
	}
	delete[]vec;
	return 0;
}