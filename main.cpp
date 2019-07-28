//#include "body.h"
#include <QApplication>
#include "widget.h"
#define test1

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Zero_Function nf;

 #ifdef test1

    Collision col1(4, 50);
    Function_System f1(&col1, &nf, &nf);
    Function_System f2(&nf, &nf, &nf);


    vector<double> xs1 = { 100, 100, 0};
    vector<double> vs1 = { 0, 20, 0};
    Particle p1 = Particle(xs1, vs1, 30, f1);

    vector<double> xs2 = { 200, 200, 0};
    vector<double> vs2 = { -20, 0, 0};
    Particle p2 = Particle(xs2, vs2, 20, f2);

    vector<double> xs3 = { -170, 200, 0};
    vector<double> vs3 = { 45, 0, 0};
    Particle p3 = Particle(xs3, vs3, 500, f2);

    vector<double> xs4 = { 400, 200, 0};
    vector<double> vs4 = { -50, 0, 0};
    Particle p4 = Particle(xs4, vs4, 100, f2);



    vector<Particle*> v = {&p1, &p2, &p3, &p4};
    Particle_System ps = Particle_System(v);
    ps.calculate(3, 12, 0.02);
    Widget w(0, v, "collision");

 #endif

#ifdef test
    Elastic fx1(0, 0, 0, 0, 0, 10, 10);
    Elastic fy1(0, 1, 0, 0, 0, 10, 10);

    Friction dragy1(0, 1, 2);
    Friction dragx1(0, 0, 2);

    Simple_Gravity grav(9.8);

    vector<Function*> Forces1 = { &grav, &fy1};
    Function_sum sum1(Forces1);

    vector<Function*> Forces2 = { &fx1, &dragx1 };
    Function_sum sum2(Forces2);

    Function_System force(&sum2, &sum1, &nf);

    vector<double> xs = { 20, 0, 0};
    vector<double> vs = { 0, 0, 0};

    Particle p =  Particle(xs, vs, 60, force);

    vector<double> xs1 = { -20, 0, 0};    

    Elastic fx2(1, 0, 0, 0, 0, 10, 10);
    Elastic fy2(1, 1, 0, 0, 0, 10, 10);

    Friction dragy2(1, 1, 2);
    Friction dragx2(1, 0, 2);


    vector<Function*> Forces3 = { &grav, &fy2 };
    Function_sum sum3(Forces3);

    vector<Function*> Forces4 = { &fx2, &dragx2 };
    Function_sum sum4(Forces4);

    Function_System force2(&sum4, &sum3, &nf);

    Particle p1 =  Particle(xs1, vs, 60, force2);

    vector<Particle*> v = {&p, &p1};
    Particle_System ps = Particle_System(v);
    ps.calculate(0, 30, 0.05);
    Widget w(0, v, "2springs");
#endif
#ifdef test2
    double au = 149597870.7E3;
    double day = 86400;

///////////////////////////////////////////////////

    /*Gravity gravSunEarthX = Gravity(0, 1, 0);
    Gravity gravSunEarthY= Gravity(0, 1, 1);

    Gravity gravSunMarsX = Gravity(0, 2, 0);
    Gravity gravSunMarsY= Gravity(0, 2, 1);

    vector<Function*> vSunX = {&gravSunEarthX, &gravSunMarsX};
    vector<Function*> vSunY = {&gravSunEarthY, &gravSunMarsY};
    Function_sum sumSunX = Function_sum(vSunX);
    Function_sum sumSunY = Function_sum(vSunY);

    Function_System fsSun(&sumSunX, &sumSunY, &nf);*/
    Function_System fsSun(&nf, &nf, &nf);

    vector<double> xsSun = { 0, 0, 0};
    vector<double> vsSun = { 0, 0, 0};

    Particle Sun =  Particle(xsSun, vsSun, 1.989E30, fsSun);

////////////////////////////////////////////////

    Gravity gravEarthSunX = Gravity(1, 0, 0);
    Gravity gravEarthSunY = Gravity(1, 0, 1);

    /*Gravity gravEarthMarsX = Gravity(1, 2, 0);
    Gravity gravEarthMarsY= Gravity(1, 2, 1);

    vector<Function*> vEarthX = {&gravEarthSunX, &gravEarthMarsX};
    vector<Function*> vEarthY = {&gravEarthSunY, &gravEarthMarsY};
    Function_sum sumEarthX = Function_sum(vEarthX);
    Function_sum sumEarthY = Function_sum(vEarthY);

    Function_System fsEarth(&sumEarthX, &sumEarthY, &nf);*/
    Function_System fsEarth(&gravEarthSunX, &gravEarthSunY, &nf);

    vector<double> xsEarth = { 9.647837469671736E-01 * au, -2.857473355736947E-01 * au, 0};
    vector<double> vsEarth = { 4.717467451380634E-03 * au / day, 1.640378862638236E-02 * au / day, 0};

    Particle Earth =  Particle(xsEarth, vsEarth, 5.97219E24, fsEarth);

/////////////////////////////////////////////////////////

    Gravity gravMarsSunX = Gravity(2, 0, 0);
    Gravity gravMarsSunY = Gravity(2, 0, 1);

    /*Gravity gravMarsEarthX = Gravity(2, 1, 0);
    Gravity gravMarsEarthY= Gravity(2, 1, 1);

    vector<Function*> vMarsX = {&gravMarsSunX, &gravMarsEarthX};
    vector<Function*> vMarsY = {&gravMarsSunY, &gravMarsEarthY};
    Function_sum sumMarsX = Function_sum(vMarsX);
    Function_sum sumMarsY = Function_sum(vMarsY);

    vector<double> xsMars = { 1.190573346517945E+00 * au, -6.939524299973826E-01 * au, 0};
    vector<double> vsMars = { 7.625461460984199E-03 * au / day, 1.325745119453680E-02 * au / day, 0};

    Function_System fsMars(&sumMarsX, &sumMarsY, &nf);*/
    Function_System fsMars(&gravMarsSunX, &gravMarsSunY, &nf);

    vector<double> xsMars = { 1.190573346517945E+00 * au, -6.939524299973826E-01 * au, 0};
    vector<double> vsMars = { 7.625461460984199E-03 * au / day, 1.325745119453680E-02 * au / day, 0};

    Particle Mars =  Particle(xsMars, vsMars, 6.4171E23, fsMars);

////////////////////////////////////////////////////////

    Gravity gravVenusSunX = Gravity(3, 0, 0);
    Gravity gravVenusSunY = Gravity(3, 0, 1);

    Function_System fsVenus(&gravVenusSunX, &gravVenusSunY, &nf);

    vector<double> xsVenus = { 4.911306312873667E-01 * au, -5.295033595370370E-01 * au, 0};
    vector<double> vsVenus = { 1.478225674484075E-02 * au / day, 1.358223327294882E-02 * au / day, 0};

    Particle Venus =  Particle(xsVenus, vsVenus, 48.685E23, fsVenus);

////////////////////////////////////////////////////////////



    vector<Particle*> v = {&Sun, &Earth, &Mars, &Venus};
    Particle_System ps = Particle_System(v);
    ps.calculate(0, 60 * 60 * 24 * 100, 60 * 60 * 24);
    Widget w(0, v, "Venus&Earth&Mars");

#endif
#ifdef spr

    Friction FrictionX(0, 0, 5);
    Friction FrictionY(0, 1, 5);

    Elastic SpringX(0,0,0,0,0,20, 10);
    Elastic SpringY(0,1,0,0,0,20, 10);

    Simple_Gravity Grav(9.8);

    vector<Function*> SpringXForces = {&FrictionX, &SpringX};
    Function_sum Xsum(SpringXForces);

    vector<Function*> SpringYForces = {&FrictionY, &SpringY, &Grav};
    Function_sum Ysum(SpringYForces);

    Function_System Spring(&Xsum, &Ysum, &nf);

    vector<double> xs = { 0, 10, 0};
    vector<double> vs = { 1, 0, 0};

    Particle p_string =  Particle(xs, vs, 60, Spring);
    vector<Particle*> v = {&p_string};
    Particle_System ps = Particle_System(v);
    ps.calculate(0, 50, 0.05);
    Widget w(0, v, "spring");
#endif

#ifdef cn
    Simple_Gravity grav(9.8);
    Friction FrictionX (0, 0, 5);
    Friction FrictionY (0, 1, 5);

    vector<Function*> cannonForces = { &grav, &FrictionY };
    Function_sum sum(cannonForces);
    Function_System cannon = { &FrictionX, &sum, &nf };
    vector<double> xc = { 0, 0, 2};
    vector<double> vc = { 300, 200, 2};
    Particle p_cannon =  Particle(xc, vc, 60, cannon);
    vector<Particle*> v = {&p_cannon};
    Particle_System ps = Particle_System(v);
    ps.calculate(0, 40, 0.05);
    Widget w(0, v, "canon");
#endif

#ifdef ls

    Elastic el1X(0, 0, 0, 0, 0, 16, 1);
    //Elastic el1Y(0, 1, 0, 0, 0, 16, 1);

    //Elastic el2X(0, 0, 0, 0, 0, 36, 1);
    Elastic el2Y(0, 1, 0, 0, 0, 36, 1);

    //vector<Function*> v1 = {&el1X, &el2X};
    //Function_sum xsum = Function_sum(v1);

    //vector<Function*> v2 = {&el1Y, &el2Y};
    //Function_sum ysum = Function_sum(v2);

    Function_System lissajois(&el1X, &el2Y, &nf);

    vector<double> xl = { 0, 0, 2};
    vector<double> vl = { 10, 10, 2};

    Particle p_lissajois =  Particle(xl, vl, 60, lissajois);
    vector<Particle*> v = {&p_lissajois};
    Particle_System ps = Particle_System(v);
    ps.calculate(0, 60, 0.05);
    Widget w(0, v, "lissajois");
#endif

    w.show();
    return a.exec();
}
