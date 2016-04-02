#include <cmath>

class DRandom{
private:
	double x;
	bool have;
public:
	DRandom(){
		have = false;
	}
	double random(double mu, double sigma){
		if (have){
			have = false;
			return mu + x * sigma;
		}
		double _x = (double) (rand()) / RAND_MAX * 2 - 1;
		double _y = (double) (rand()) / RAND_MAX * 2 - 1;
		double s = _x * _x + _y * _y;
		if (not(s == 0 || s > 1)){
			x = _x * sqrt(-2 * log(s) / log(2) / s);
			have = true;
			return mu + _y * sqrt(-2 * log(s) / log(2) / s) * sigma;
		}
		return random(mu, sigma);
	}
	int RangeRandom(int x, int y){
		double m = (double) (x + y) / 2;
		double k = random(m, m / 8) + 0.5;
		while ((int) k < x || (int) k >= y){
			k = random(m, m / 8) + 0.5;
		}
		return (int) k;
	}
};