#ifndef DEFS_H
#define DEFS_H


//Defines the lattice size
constexpr int L = 6;


//-------------MEASURES PARAMETERS-------------
//Defines the magnetic field
constexpr double B = 1;     // Field norm      Theta and Phi are in rad
constexpr double Theta = 0.25 * 0.79609718166;//< 0.955316618
constexpr double Phi = 0;// 1.0471975512;

//Defines the temperature domain.
constexpr double Ti = 2.3;
constexpr double Tf = 4;
constexpr double dT = 0.1;

//Defines the number of steps needed to equilibrate the lattice.
constexpr int Neq = L * L;

//Defines the number of step to measure the system equilibrium properties.
constexpr int Nmeas = 2000;


//--------------NSP PARAMETERS-------------------
constexpr bool DoYouWantNeutronScatteringPlot = false; //true = yes    false = no

//Defines the number of NSP measures.
constexpr int NSpinConfig = 2000;

//Size of the reciprocal space.
constexpr int xmult = 2;
constexpr int ymult = 2;





//DO NOT TOUCH :(
constexpr double S[4][3] = { { 0 , 0 , -1 }, { -0.94280904158 , 0 , 0.33333333333  }, { +0.47140452079 , -0.81649658092 , +0.33333333333  }, { +0.47140452079 , +0.81649658092 , +0.33333333333  } };

constexpr double pi2 = 2 * 3.14159265358979323846; //2*pi
constexpr double _r3 = 0.57735026919; // 1/sqrt(3)

constexpr double S_NSP[4][3] = { { -_r3 , -_r3 , -_r3 }, { -_r3 , _r3 , _r3  }, { _r3 , -_r3 , _r3  }, { _r3 , _r3 , -_r3  } };

constexpr double ReaL[3][3] = { {  0  , 0.5, 0.5 }, { 0.5,  0  , 0.5 }, { 0.5, 0.5,  0  } };//ReaL lattice basis
constexpr double RecL[3][3] = { { -pi2, pi2, pi2 }, { pi2, -pi2, pi2 }, { pi2, pi2, -pi2 } };//Reciprocal lattice basis

constexpr int xdiv = 4 * xmult * 2 * L; //defines NSP Q's mesh.
constexpr int ydiv = 4 * ymult * 2 * L;
#endif //DEFS_H
