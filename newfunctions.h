#ifndef NEWFUNCTIONS_H
#define NEWFUNCTIONS_H

#define NMB_OF_COORDS 3
#define NMB_OF_PARAMS 7     //Ex: x1,y1,z1, vx1,vy1,vz1, m1,
//                                x2,y2,z2, vx2,vy2,vz2, m2,...

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

    virtual double operator()(double t, vector <double>& x) = 0;
};

class Zero_Function : public Function{
public:
    double operator()(double t, vector <double>& x){
        return(0);
    }
};

class Function_sum :public Function{
public:
    Function_sum(vector<Function*>& funs){
        this->funs = funs;
    }
    double operator()(double t, vector <double>& x){
        double result = 0;
        for (auto fun : this->funs){
            result += (*fun)(t, x);
        }
        return result;
    }
};


class Velocity : public Function{
public:
    Velocity(long index_of_particle,        //index in particle system
             int coordinate){               // x - 0, y - 1, z - 2
         coefs.push_back(index_of_particle);
         coefs.push_back(coordinate);
    }
    double operator()(double t, vector <double>& x){
        return x.at(coefs.at(0) * NMB_OF_PARAMS + NMB_OF_COORDS + coefs.at(1)); // Ex: x1,y1,z1, vx1,vy1,vz1, m1,
                                                                                //     x2,y2,z2, vx2,vy2,vz2, m2,...
    }
};

class Simple_Gravity : public Function{
public:
    Simple_Gravity(double g){
        coefs.push_back(g);
    }
    double operator()(double t, vector <double>& x){
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
    double operator()(double t, vector <double>& x){
        long i1 = coefs.at(0);
        long i2 = coefs.at(1);
        double r_sq = pow(x.at(i1 * NMB_OF_PARAMS) - x.at(i2 * NMB_OF_PARAMS),2) +
                pow(x.at(i1 * NMB_OF_PARAMS + 1) - x.at(i2 * NMB_OF_PARAMS + 1),2) +
                pow(x.at(i1 * NMB_OF_PARAMS + 2) - x.at(i2 * NMB_OF_PARAMS + 2),2);
        double abs_f = coefs.at(3) * x.at(i2 * NMB_OF_PARAMS + 2 * NMB_OF_COORDS) / r_sq;
        return  abs_f * (x.at(i2 * NMB_OF_PARAMS + coefs.at(2)) - x.at(i1 * NMB_OF_PARAMS + coefs.at(2)))/ sqrt(r_sq);
    }
};

class Friction : public Function{
public:
    Friction(long index_of_particle, int coord, double coef_of_friction){
        coefs.push_back(index_of_particle);
        coefs.push_back(coord);
        coefs.push_back(coef_of_friction);
    }
    double operator()(double t, vector <double>& x){
        return - coefs.at(2) * x.at(coefs.at(0) * NMB_OF_PARAMS + NMB_OF_COORDS + coefs.at(1)) / x.at(coefs.at(0) * NMB_OF_PARAMS + 2 * NMB_OF_COORDS);
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
    double operator ()(double t, vector <double>& x){
        double l = sqrt(pow(x.at(coefs.at(0) * NMB_OF_PARAMS) - coefs.at(2),2) + pow(x.at(coefs.at(0) * NMB_OF_PARAMS + 1) - coefs.at(3),2) + pow(x.at(coefs.at(0) * NMB_OF_PARAMS + 2) - coefs.at(4),2));
        double abs_f =  -(l - coefs.at(6)) * coefs.at(5) / (l * x.at(coefs.at(0) * NMB_OF_PARAMS + 2 * NMB_OF_COORDS));
        return abs_f * x.at(coefs.at(0) * NMB_OF_PARAMS + coefs.at(1));
    }
};

class Collision : public Function{
public:
    Collision(long number_of_particles, double precision = 0.01){
        coefs.push_back(precision);                  //0
        int n0 = 3 * pow(NMB_OF_PARAMS,2) * pow(number_of_particles,2)
                + 6 * NMB_OF_PARAMS * number_of_particles
                + 9;
        coefs.push_back(n0);                         //1
        int dn = pow(NMB_OF_PARAMS,3) * pow(number_of_particles,3)
                + 2 * pow(NMB_OF_PARAMS,2) * pow(number_of_particles,2)
                + 3 * NMB_OF_PARAMS * number_of_particles
                + 4;
        coefs.push_back(dn);                         //2
        coefs.push_back(0);                          //3
        coefs.push_back(number_of_particles);        //4
        for(int i = 0; i != coefs.at(4); i++){
            for(int j = i+1; j != coefs.at(4); j++){
                coefs.push_back(0);
            }
        }
    }
    double operator()(double t, vector <double>& x){


        if(int(coefs.at(3)) != 0 && int(coefs.at(3) - coefs.at(1)) % int(coefs.at(2)) == 0) {
           long ind = 5;
           for(int i = 0; i != coefs.at(4); i++){
               for(int j = i+1; j != coefs.at(4); j++){
                   long i1 = i;
                   long i2 = j;

                   double r_sq = pow(x.at(i1 * NMB_OF_PARAMS) - x.at(i2 * NMB_OF_PARAMS),2) +
                           pow(x.at(i1 * NMB_OF_PARAMS + 1) - x.at(i2 * NMB_OF_PARAMS + 1),2) +
                           pow(x.at(i1 * NMB_OF_PARAMS + 2) - x.at(i2 * NMB_OF_PARAMS + 2),2);

                    if (r_sq < coefs.at(0)){
                        if(coefs.at(ind) == 0){
                            coefs.at(ind++) += 1;

                            double m1 = x.at(i1 * NMB_OF_PARAMS + 2 * NMB_OF_COORDS);
                            double m2 = x.at(i2 * NMB_OF_PARAMS + 2 * NMB_OF_COORDS);

                            double dx = x.at(i2 * NMB_OF_PARAMS) - x.at(i1 * NMB_OF_PARAMS);
                            double dy = x.at(i2 * NMB_OF_PARAMS + 1) - x.at(i1 * NMB_OF_PARAMS + 1);
                            double phi;
                            if (dx == 0)
                                phi = M_PI;
                            else
                                phi = atan(dy/dx);

                            double v1 = sqrt(pow(x.at(i1 * NMB_OF_PARAMS + NMB_OF_COORDS),2) +
                                             pow(x.at(i1 * NMB_OF_PARAMS + NMB_OF_COORDS + 1),2) +
                                             pow(x.at(i1 * NMB_OF_PARAMS + NMB_OF_COORDS + 2),2));
                            double v2 = sqrt(pow(x.at(i2 * NMB_OF_PARAMS + NMB_OF_COORDS),2) +
                                             pow(x.at(i2 * NMB_OF_PARAMS + NMB_OF_COORDS + 1),2) +
                                             pow(x.at(i2 * NMB_OF_PARAMS + NMB_OF_COORDS + 2),2));

                            double ang1 = acos(x.at(i1 * NMB_OF_PARAMS + NMB_OF_COORDS) / v1);
                            double ang2 = acos(x.at(i2 * NMB_OF_PARAMS + NMB_OF_COORDS) / v2);

                            double v1xr = v1*cos((ang1-phi));
                            double v1yr = v1*sin((ang1-phi));
                            double v2xr = v2*cos((ang2-phi));
                            double v2yr = v2*sin((ang2-phi));

                            double v1fxr = ((m1-m2)*v1xr+(m2+m2)*v2xr)/(m1+m2);
                            double v2fxr = ((m1+m1)*v1xr+(m2-m1)*v2xr)/(m1+m2);
                            double v1fyr = v1yr;
                            double v2fyr = v2yr;

                            double v1fx = cos(phi)*v1fxr+cos(phi+M_PI/2)*v1fyr;
                            double v1fy = sin(phi)*v1fxr+sin(phi+M_PI/2)*v1fyr;
                            double v2fx = cos(phi)*v2fxr+cos(phi+M_PI/2)*v2fyr;
                            double v2fy = sin(phi)*v2fxr+sin(phi+M_PI/2)*v2fyr;

                            x.at(i1 * NMB_OF_PARAMS + NMB_OF_COORDS) = v1fx;

                            x.at(i1 * NMB_OF_PARAMS + NMB_OF_COORDS + 1) = v1fy;

                            x.at(i2 * NMB_OF_PARAMS + NMB_OF_COORDS) = v2fx ;
                            x.at(i2 * NMB_OF_PARAMS + NMB_OF_COORDS + 1) = v2fy;
                        }
                    }
                    else
                        coefs.at(ind++) = 0;
                }
            }
        }
        coefs.at(3) += 1;
        return 0;
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

#endif // NEWFUNCTIONS_H
