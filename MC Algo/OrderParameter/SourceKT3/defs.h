#ifndef DEFS_H
#define DEFS_H


//Defines the lattice size
constexpr int L=24;

//Defines the magnetic field
constexpr double B = 1;     // Field norm      Theta and Phi are in rad
constexpr double Theta = 0; // 1.23095941734;
constexpr double Phi = 0; // 1.0471975512;

//Defines the system temperature.
constexpr double Ti = 2; //Initial temperature

//Defines the number of steps needed to equilibrate the lattice.
constexpr int Neq = 1000;

//How the code should be run?
constexpr bool DoYouWantNeutronScatteringPlot = false; //true = yes    false = no

//-------------MEASURES PARAMETERS------------- NO
//Define the temperature domain
constexpr double Tf = 10;   //Final   temperature
constexpr double dT = 0.1;  //Temperature step

//Defines the number of step to measure the system equilibrium properties.
constexpr int Nmeas = 5000;


//--------------NSP PARAMETERS------------------ YES
//Defines the number of NSP measures. (higher remove noise but last longer)
constexpr int NSpinConfig = 10;

//Choose the direction of the resulting NSP
constexpr int NSPdirections = 6;
//Available NSPdirections:
/*
0:	(h,  h, 0)	( 0, 0,  l)
1:	(h, -h, 0)	( 0, 0,  l)
2:	(h, -h, 0)	( k, k,-2k)
3:	(h, -h, 0)	( l, l,  l)
4:	(h,  h, 0)  ( l,-l,  l)
5:	(h,  h, 0)  (-k, k, 2k)
6:	(k,-k,-2k)  ( l,-l,  l)
*/

constexpr int xlim = 4; //Size of the reciprocal space. h, k or l (depending on NSPdirections) goes from -x(y)lim to x(y)lim.
constexpr int ylim = 4; //The x(y)axis will be normalised by a constant accordingly to reciprocal direction (sqrt(2) for hh0, sqrt(3) for lll, sqrt(6) for kk2k...)

constexpr int xdiv = xlim * 2*L; // Defines NSP Q's mesh. (bigger xdiv and ydiv are, better the resolution is
constexpr int ydiv = ylim * 2*L; //but the computation last longer)

#endif	