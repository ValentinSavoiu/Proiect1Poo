#pragma once
template <class T>
class Matrice {
	friend class ComplexNumber;
private:
	int X, Y;
	T **p;
public:
	Matrice(int X = 3, int Y = 3) {
		this->X = X;
		this->Y = Y;
		p = new T*[X];
		for (int i = 0; i < X; ++i)
			p[i] = new T[Y];
	}
	Matrice(const Matrice<T> &M) {
		X = M.X;
		Y = M.Y;
		p = new T*[X];
		for (int i = 0; i < X; ++i)
			p[i] = new T[Y];
		for (int i = 0; i < X; ++i)
			for (int j = 0; j < Y; ++j)
				p[i][j] = M.p[i][j];

	}
	friend Matrice operator+ (const Matrice &A, const Matrice &B) {
		if (A.X != B.X || A.Y != B.Y)
			throw("Matrice de tipuri diferite");
		Matrice<T> Res(A.X, A.Y);
		for (int i = 0; i < Res.X; ++i)
			for (int j = 0; j < Res.Y; ++j)
				Res.p[i][j] = A.p[i][j] + B.p[i][j];
		return Res;
	}
	friend Matrice operator- (const Matrice &A, const Matrice &B) {
		return A + (-B);
	}
	friend Matrice operator- (const Matrice &A) {
		Matrice <T> Res(A);
		for (int i = 0; i < Res.X; ++i)
			for (int j = 0; j < Res.Y; ++j) {
				Res.p[i][j] = -Res.p[i][j];
			}
		return Res;
	}
	friend T determinant(Matrice A) {
		if (A.X != A.Y) throw("Matricea nu este patratica!");
		if (A.X == 2) {
			return A.p[0][0] * A.p[1][1] - A.p[0][1] * A.p[1][0];
		}
		if (A.X == 0) return 0;
		if (A.X == 1) return A.p[0][0];
		Matrice <T> B(A.X - 1, A.X - 1);
		int j, I, J;
		int X = A.X, Y = A.Y;
		for (j = 0; j < X; ++j)
			if (A.p[0][j] != 0) break;
		if (j == X) return 0;
		for (J = 0; J < X; ++J) {
			if (J == j) continue;
			T rap = A.p[0][J] / A.p[0][j];
			A.p[0][J] = 0;
			for (I = 1; I < X; ++I)
				A.p[I][J] = A.p[I][J] - rap * A.p[I][j];
		}
		for (I = 1; I < X; ++I) {
			for (J = 0; J < X; ++J) {
				if (J < j) {
					B.p[I - 1][J] = A.p[I][J];
				}
				else if (J > j) {
					B.p[I - 1][J - 1] = A.p[I][J];
				}
			}
		}
		if (j % 2) return  -1 * A.p[0][j] * determinant(B);
		return A.p[0][j] * determinant(B);
	}

	friend Matrice operator* (const Matrice &A, const Matrice &B) {
		if (A.Y != B.X) throw("Inmultire imposibila de matrice");
		Matrice <T> Res(A.X, B.Y);
		for (int i = 0; i < Res.X; ++i)
			for (int j = 0; j < Res.Y; ++j) {
				Res.p[i][j] = 0;
				for (int k = 0; k < A.Y; ++k) {
					Res.p[i][j] = Res.p[i][j] + A.p[i][k] * B.p[k][j];
				}
			}
		return Res;
	}
	friend Matrice operator* (const Matrice &A, T r) {
		Matrice <T> Res(A);
		for (int i = 0; i < Res.X; ++i)
			for (int j = 0; j < Res.Y; ++j)
				Res.p[i][j] = Res.p[i][j] * r;
		return Res;
	}

	friend Matrice operator/ (const Matrice &A, T r) {
		return A * (1.0 / r);
	}

	friend bool operator == (const Matrice &A, const Matrice &B) {
		if (A.X != B.X || A.Y != B.Y) return false;
		for (int i = 0; i < A.X; ++i)
			for (int j = 0; j < A.Y; ++j)
				if (A.p[i][j] != B.p[i][j])
					return false;
		return true;
	}

	friend bool operator != (const Matrice &A, const Matrice &B) {
		return !(A == B);
	}

	friend bool operator < (const Matrice &A, const Matrice &B) {
		if (A.X != B.X) return A.X < B.X;
		if (A.Y != B.Y) return A.Y < B.Y;
		for (int i = 0; i < A.X; ++i)
			for (int j = 0; j < A.Y; ++j) {
				if (A.p[i][j] != B.p[i][j])
					return A.p[i][j] < B.p[i][j];
			}
		return false;
	}

	Matrice &operator = (const Matrice &A) {
		if (this == &A)
			return *this;
		for (int i = 0; i < X; ++i)
			delete[]p[i];
		delete[]p;
		X = A.X;
		Y = A.Y;
		p = new T*[X];
		for (int i = 0; i < X; ++i)
			p[i] = new T[Y];
		for (int i = 0; i < X; ++i)
			for (int j = 0; j < Y; ++j)
				p[i][j] = A.p[i][j];
		return *this;
	}

	bool operator == (const Matrice &A) {
		if (X != A.X) return false;
		if (Y != A.Y) return false;
		for (int i = 0; i < X; ++i)
			for (int j = 0; j < Y; ++j)
				if (p[i][j] != A.p[i][j])
					return false;
		return true;
	}

	Matrice invers() {
		if (X != Y) throw("Matricea nu este patratica");
		if (X == 1) {
			Matrice <T> Inv(*this);
			return Inv / p[0][0] / p[0][0];
		}
		T det = determinant(*this);
		if (det == 0) throw("Determinant nul");
		Matrice <T> Inv(X, X);
		Matrice <T> B(X - 1, X - 1);
		for (int i = 0; i < X; ++i)
			for (int j = 0; j < X; ++j) {
				for (int I = 0; I < X; ++I) {
					if (i == I) continue;
					for (int J = 0; J < X; ++J) {
						if (j == J) continue;
						int linie = I, coloana = J;
						if (I > i) --linie;
						if (J > j) --coloana;
						B.p[linie][coloana] = p[I][J];
					}
				}
				T dete = determinant(B);
				Inv.p[j][i] = dete;
				if ((i + j) % 2) Inv.p[j][i] = Inv.p[j][i] * -1;
			}
		return Inv / det;
	}

	void matI(int n) {
		Matrice aux(n, n);
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				if (i != j) aux.p[i][j] = 0;
				else aux.p[i][j] = 1;
		*this = aux;
	}

	friend std::istream& operator >> (std::istream& is, Matrice<T> &c) {

		for (int i = 0; i < c.X; ++i)
			delete[]c.p[i];
		delete[]c.p;
		is >> c.X >> c.Y;
		c.p = new T*[c.X];
		for (int i = 0; i < c.X; ++i)
			c.p[i] = new T[c.Y];
		for (int i = 0; i < c.X; ++i)
			for (int j = 0; j < c.Y; ++j)
				is >> c.p[i][j];
		return is;
	}
	friend std::ostream& operator << (std::ostream& os, const Matrice<T> &c) {
		os << c.X << ' ' << c.Y << '\n';
		for (int i = 0; i < c.X; ++i) {
			for (int j = 0; j < c.Y; ++j) {
				os << c.p[i][j] << ' ';
			}
			os << '\n';
		}
		return os;
	}
	~Matrice() {
		for (int i = 0; i < X; ++i)
			delete[]p[i];
		delete[]p;
	}
};