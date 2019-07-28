/*#include "RKS.h"


vector<vector<double>> RKS::operator() (vector<Force*> funs, double t0, double t1, vector<double>& x0, double m, double h) {
	this->funs = funs;
	this->h = h;

	this->n = (int)((t1 - t0) / h) + 1;

	this->m = m;
	t.push_back(t0);
	for (int i = 1; i != n; i++){
		t.push_back(t.at(i - 1) + h);
	}

	for (int i = 0; i != x0.size(); i++){
		vector<double> foo;
		foo.push_back(x0.at(i));
		x.push_back(foo);
	}

	return(this->solve());
}

double RKS::k1(int i, Force* f){
	double a = (*f)(
		t.at(i),
		x.at(0).at(i),
		x.at(1).at(i),
		m
		);
	return h * a;
}

double RKS::k2(int i, Force* f){
	return h * (*f)(
		t.at(i) + h / 2,
		x.at(0).at(i) + k1(i, funs.at(0)) / 2,
		x.at(1).at(i) + k1(i, funs.at(1)) / 2,
		m
		);
}

double RKS::k3(int i, Force* f){
	return h * (*f)(
		t.at(i) + h / 2,
		x.at(0).at(i) + k2(i, funs.at(0)) / 2,
		x.at(1).at(i) + k2(i, funs.at(1)) / 2,
		m
		);
}

double RKS::k4(int i, Force* f){
	return h * (*f)(
        t.at(i) + h,
        x.at(0).at(i) + k3(i, funs.at(0)),
        x.at(1).at(i) + k3(i, funs.at(1)),
		m
		);
}

vector<vector<double>> RKS::solve(){
	for (int i = 0; i != n - 1; i++){
		for (int j = 0; j != 2; j++){
			x.at(j).push_back(
				x.at(j).at(i) + 1 / 6.0 * (
				k1(i, funs.at(j)) +
				2 * k2(i, funs.at(j)) +
				2 * k3(i, funs.at(j)) +
				k4(i, funs.at(j))
				)
				);
		}
	}
	return{ t, x.at(0), x.at(1) };
}*/
