#include "RKS_SYS.h"

vector<vector<double>> RKS_SYS::operator() (vector<Function*>& funs, double t0, double t1, vector<double>& x0, vector<double>& m, double h) {
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

double RKS_SYS::k1(int i, Function* f){
    vector<double> parameteres;
	for (int j = 0; j != this->x.size(); j++){
		parameteres.push_back(((this->x).at(j)).at(i));
	}
	return h * (*f)(t.at(i), parameteres, this->m);//////////////////
}

double RKS_SYS::k2(int i, Function* f){
    vector<double> parameteres;
    for(int j = 0; j != this->x.size(); j++){
		parameteres.push_back(((this->x).at(j)).at(i) + k1(i, funs.at(j)) / 2);
    }
    return h * (*f)(t.at(i) + h / 2, parameteres, this->m);
}

double RKS_SYS::k3(int i, Function* f){
	vector<double> parameteres;
	for (int j = 0; j != this->x.size(); j++){
		parameteres.push_back(((this->x).at(j)).at(i) + k2(i, funs.at(j)) / 2);
    }	
    return h * (*f)(t.at(i) + h / 2, parameteres, this->m);
}

double RKS_SYS::k4(int i, Function* f){
    vector<double> parameteres;
    for(int j = 0; j != this->x.size(); j++){
		parameteres.push_back(((this->x).at(j)).at(i) + k3(i, funs.at(j)) / 2);
    }
    return h * (*f)(t.at(i) + h / 2, parameteres, this->m);
}

vector<vector<double>> RKS_SYS::solve(){
    for (int i = 0; i != n - 1; i++){
        for (int j = 0; j != x.size(); j++){
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
    vector<vector<double>> result;
    result.push_back(t);
    result.insert(result.end(), x.begin(), x.end());
    return result;
}
