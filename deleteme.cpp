#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class PolinomialError{
public:
	string s;
};

class Polinomial{
private:
	vector<double> K;
public:
	Polinomial(){
		K.clear();
		K.push_back(0);
	}
	Polinomial(Polinomial &P){
		K.resize((int) P.K.size());
		for (int i = 0; i < (int) P.K.size(); ++i){
			K[i] = P.K[i];
		}
	}
	Polinomial(int n, double* A){
		K.resize(n + 1);
		for(int i = 0; i <= n; ++i){
			K[i] = A[i];
		}
	}
	Polinomial(int n, int* A){
		K.resize(n + 1);
		for(int i = 0; i <= n; ++i){
			K[i] = A[i];
		}
	}
	const double operator[](const int i) const{
		if (i >= (int) K.size()){
			PolinomialError E;
			E.s = "IndexError\n";
			throw E;
		}
		return K[i];
	}
};

int main(){
	int A[5];
	for (int i = 0; i < 5; ++i){
		i[A] = i * i - 4 * i + 1;
	}
	Polinomial P(4, A);
	return 0;
}