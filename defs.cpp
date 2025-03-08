#include "defs.h"

int g_lattice[L][L][L][4];
double g_proba[4][4];
double g_magneticField[3];

int g_Nspins;

//thermodynamical properties
double g_magnetisationDifference[4][4];
double g_systemMagnetisation;
double g_mag;
double g_magx;
double g_mag_sq;

double g_energyDifference[4][4];
double g_systemEnergy;
double g_energy;
double g_energy_sq;

int g_wormLength;
int g_length;

int N_external_loop;

int xA;
int yA;
int zA;
char tetraA;
int nA;

int xB;
int yB;
int zB;
char tetraB;
int nB;

int xC;
int yC;
int zC;
char tetraC;
int nC;

//NSP values

double g_spinUsefull[2 * xdiv][2 * xdiv][4][3];
double g_SpinPosition[L][L][L][4][4][3]; //IX ([2*L]), IY([2*L]), ispin([3]) and a position in the lattice ([2*L])
double g_Q[2 * xdiv][2 * xdiv][3];
double g_X[2 * xdiv][2 * xdiv];
double g_Y[2 * xdiv][2 * xdiv];
double g_QHat[2 * xdiv][2 * xdiv][3];
double g_NSP[2 * xdiv][2 * xdiv];
double g_BraggsPeak[2 * xdiv][2 * xdiv];
double g_qlim;
int g_nspCount;
