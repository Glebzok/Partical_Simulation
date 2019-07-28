#include "rk4.h"

vector<vector<double>> RK4::operator() (vector<Function*>& funs, double t0, double t1, vector<double>& x0, double h) {
    this->funs = funs;
    this->h = h;

    this->n = (int)((t1 - t0) / h) + 1;
    t.push_back(t0);
    for (int i = 1; i != n; i++){
        vector<double> foo;
        t.push_back(t.at(i - 1) + h);
    } 
    x.push_back(x0);

    return(this->solve());
}

double RK4::k1(int i, Function* f){
    return h * (*f)(t.at(i), x.at(i));//////////////////
}

double RK4::k2(int i, Function* f){
    vector<double> parameteres;
    for(int j = 0; j != this->x.at(0).size(); j++){
        parameteres.push_back((this->x.at(i)).at(j) + k1(i, funs.at(j)) / 2);
    }
    return h * (*f)(t.at(i) + h / 2, parameteres);
}

double RK4::k3(int i, Function* f){
    vector<double> parameteres;
    for (int j = 0; j != this->x.at(0).size(); j++){
        parameteres.push_back(((this->x).at(i)).at(j) + k2(i, funs.at(j)) / 2);
    }
    return h * (*f)(t.at(i) + h / 2, parameteres);
}

double RK4::k4(int i, Function* f){
    vector<double> parameteres;
    for(int j = 0; j != this->x.at(0).size(); j++){
        parameteres.push_back(((this->x).at(i)).at(j) + k3(i, funs.at(j)) / 2);
    }
    return h * (*f)(t.at(i) + h / 2, parameteres);
}

vector<vector<double>> RK4::solve(){
    for (int i = 0; i != n - 1; i++){
        vector<double> foo = {};
        for (int j = 0; j != x.at(0).size(); j++){
            double a =  k1(i, funs.at(j));
            double b = 2 * k2(i, funs.at(j));
            double c = 2 * k3(i, funs.at(j));
            double d = k4(i, funs.at(j));
            foo.push_back(
                x.at(i).at(j) + 1 / 6.0 * (
                a +
                b +
                c +
                d
                )
                );
        }
        x.push_back(foo);
    }
    vector<vector<double>> result;
    result.push_back(t);
    for(int i = 0; i != x.at(0).size(); i++){
        vector<double> foo = {};
        for (int j = 0; j != x.size(); j++){
            foo.push_back(x.at(j).at(i));
        }
        result.push_back(foo);
    }
    //result.insert(result.end(), x.begin(), x.end());
    return result;
}
