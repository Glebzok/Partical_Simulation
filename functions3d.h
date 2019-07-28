#ifndef FUNCTIONS3D_H
#define FUNCTIONS3D_H


#include <vector>
#include <cmath>

using namespace std;

class Force{
public:
    vector<Force*> forces;
    vector<double> koefs;
    Force(){
        vector <double> ks;
        koefs = ks;
    }

    virtual double operator()(double t,
                              double x, double y, double z,
                              double vx, double vy,double vz,
                              double m = 1) = 0;
};

class Force_System{
public:
    Force* x_force;
    Force* y_force;
    Force* z_force;
    Force_System(Force* f1, Force* f2, Force* f3) : x_force(f1), y_force(f2), z_force(f3){}
    Force_System(){}
};


class NoForce : public Force{
public:
    double operator()(double t,
                      double x, double y, double z,
                      double vx, double vy,double vz,
                      double m){
        return(0);
    }
};

class Force_Sum :public Force{
public:
    Force_Sum(vector<Force*> fs){
        this->forces = fs;
    }
    double operator()(double t,
                      double x, double y, double z,
                      double vx, double vy,double vz,
                      double m){
        double res = 0;
        for (auto force : this->forces){
            res += (*force)(t, x, y, z, vx, vy, vz, m);
        }
        return res;
    }
};

class Vel : public Force{
public:
    Vel(char coord){
        koefs.push_back(coord);
    }
    double operator()(double t,
                      double x, double y, double z,
                      double vx, double vy,double vz,
                      double m){
        if (koefs.at(0) == 'x')
            return vx;
        else if (koefs.at(0) == 'y')
            return vy;
        else if (koefs.at(0) == 'z')
            return vz;
        else return 0;
    }
};

class Gravity : public Force{
public:
    Gravity(double g){
        koefs.push_back(g);
    }
    double operator()(double t,
                      double x, double y, double z,
                      double vx, double vy,double vz,
                      double m){
        return(-koefs.at(0));
    }
};

class Viscous_Drag : public Force{
public:
    Viscous_Drag(char coord, double k_drag){
        koefs.push_back(coord);
        koefs.push_back(k_drag);
    }
    double operator()(double t,
                      double x, double y, double z,
                      double vx, double vy,double vz,
                      double m){
        if (koefs.at(0) == 'x')
            return - koefs.at(1) * vx / m;
        else if (koefs.at(0) == 'y')
            return - koefs.at(1) * vy / m;
        else if (koefs.at(0) == 'z')
            return - koefs.at(1) * vz / m;
        else return 0;
    }
};

class Elastic : public Force{
public:
    Elastic(double coord, double k, double offset){
        koefs.push_back(coord);
        koefs.push_back(k);
        koefs.push_back(offset);
    }
    double operator ()(double t,
                       double x, double y, double z,
                       double vx, double vy,double vz,
                       double m){
        if (koefs.at(0) == 'x')
            return -koefs[1]*(x - koefs[2])/m;
        else if (koefs.at(0) == 'y')
            return -koefs[1]*(y - koefs[2])/m;
        else if (koefs.at(0) == 'z')
            return -koefs[1]*(z - koefs[2])/m;
        else return 0;
    }
};

class Elastic3D : public Force{
public:
    Elastic3D(char coord, double x, double y, double z, double k, double length){
        koefs.push_back(coord);
        koefs.push_back(x);
        koefs.push_back(y);
        koefs.push_back(z);
        koefs.push_back(k);
        koefs.push_back(length);
    }
    double operator ()(double t,
                       double x, double y, double z,
                       double vx, double vy,double vz,
                       double m){
        double l = sqrt(pow(x - koefs.at(1),2) + pow(y - koefs.at(2),2) + pow(z - koefs.at(3),2));
        double abs_f = -(l - koefs.at(5)) * koefs.at(4) / (l * m);
        if (koefs.at(0) == 'x')
            return abs_f * x;
        else if (koefs.at(0) == 'y')
            return abs_f * y;
        else if (koefs.at(0) == 'z')
            return abs_f * z;
        else return 0;
    }
};

#endif // FUNCTIONS3D_H
