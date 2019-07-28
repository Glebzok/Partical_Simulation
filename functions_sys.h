#ifndef FUNCTIONS_SYS_H
#define FUNCTIONS_SYS_H


#include <vector>
#include <cmath>

using namespace std;

class Function{
public:
    vector<Function*> funs;
    vector<double> coefs;
    Function(){
        vector <double> coefs;
        this->coefs = coefs;
    }

    virtual double operator()(double t, vector <double>& x, vector <double>& m) = 0;
};

class Zero_Function : public Function{
public:
    double operator()(double t, vector <double>& x, vector<double>& m){
        return(0);
    }
};

class Function_sum :public Function{
public:
    Function_sum(vector<Function*>& funs){
        this->funs = funs;
    }
    double operator()(double t, vector <double>& x, vector<double>& m){
        double result = 0;
        for (auto fun : this->funs){
            result += (*fun)(t, x, m);
        }
        return result;
    }
};

class Velocity : public Function{
public:
    Velocity(long index_of_particle, //index in particle system
             int coordinate){ // x - 0, y - 1, z - 2
         coefs.push_back(index_of_particle);
         coefs.push_back(coordinate);
    }
    double operator()(double t, vector <double>& x, vector<double>& m){
        return x.at(coefs.at(0) * 6 + 3 + coefs.at(1)); // Ex: x1,y1,z1, vx1,vy1,vz1,
                                                        //     x2,y2,z2, vx2,vy2,vz2,...
    }
};

class Simple_Gravity : public Function{
public:
    Simple_Gravity(double g){
        coefs.push_back(g);
    }
    double operator()(double t, vector <double>& x, vector<double>& m){
        return(-coefs.at(0));
    }
};

class Gravity : public Function{
public:
    Gravity(long index_of_affected_particle, long index_of_affecting_particle, int coord, double G = 6.6E-11){
        coefs.push_back(index_of_affected_particle);
        coefs.push_back(index_of_affecting_particle);
        coefs.push_back(coord);
        coefs.push_back(G);
    }
    double operator()(double t, vector <double>& x, vector<double>& m){
        long i1 = coefs.at(0);
        long i2 = coefs.at(1);
        double r_sq = pow(x.at(i1 * 6) - x.at(i2 * 6),2) +
                pow(x.at(i1 * 6 + 1) - x.at(i2 * 6 + 1),2) +
                pow(x.at(i1 * 6 + 2) - x.at(i2 * 6 + 2),2);
        double abs_f = coefs.at(3) * m.at(i2) / r_sq;
        return  abs_f * (x.at(i2 * 6 + coefs.at(2)) - x.at(i1 * 6 + coefs.at(2)))/ sqrt(r_sq);
    }
};

class Friction : public Function{
public:
    Friction(long index_of_particle, int coord, double coef_of_friction){
        coefs.push_back(index_of_particle);
        coefs.push_back(coord);
        coefs.push_back(coef_of_friction);
    }
    double operator()(double t, vector <double>& x, vector<double>& m){
        return - coefs.at(2) * x.at(coefs.at(0) * 6 + 3 + coefs.at(1)) /
                m.at(coefs.at(0));
    }
};

class Elastic : public Function{
public:
    Elastic(long index_of_particle, int coord, double x, double y, double z, double k, double free_length){
        coefs.push_back(index_of_particle);
        coefs.push_back(coord);
        coefs.push_back(x);
        coefs.push_back(y);
        coefs.push_back(z);
        coefs.push_back(k);
        coefs.push_back(free_length);
    }
    double operator ()(double t, vector <double>& x, vector<double>& m){
        double l = sqrt(pow(x.at(coefs.at(0)*6) - coefs.at(1),2) + pow(x.at(coefs.at(0)*6+1) - coefs.at(2),2) + pow(x.at(coefs.at(0)*6+2) - coefs.at(3),2));
        double abs_f =  -(l - coefs.at(6)) * coefs.at(5) / (l * m.at(coefs.at(0)));
        return abs_f * x.at(coefs.at(0)*6 + coefs.at(1));
    }
};

class Function_System{
public:
    Function* x_force;
    Function* y_force;
    Function* z_force;
    Function_System(Function* f1, Function* f2, Function* f3) : x_force(f1), y_force(f2), z_force(f3){}
    Function_System(){}
};
#endif // FUNCTIONS_SYS_H
