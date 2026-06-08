#include <iostream>
#include <stdlib.h>
#include <fstream> 
#include <cmath>

#include "addAWorm.h"
#include "defs.h"
#include "next.h"
#include "growTheWorm.h"


int wormSize;
extern int g_lattice[L][L][L][4];
extern double g_proba[4][4];

extern int wormSize;

extern double g_systemEnergy;
extern double g_energy;
extern double g_energy_sq;

extern double g_systemMagnetisation;
extern double g_mag;
extern double g_mag_sq;

extern int g_wormLength;
extern int g_length;

extern int xA;
extern int yA;
extern int zA;
extern char tetraA;
extern int nA;

extern int xB;
extern int yB;
extern int zB;
extern char tetraB;
extern int nB;

extern int xC;
extern int yC;
extern int zC;
extern char tetraC;
extern int nC;

extern int xD;
extern int yD;
extern int zD;
extern char tetraD;
extern int nD;

/// <summary>
/// Add a loop of flipped spins. Might measure the system.
/// </summary>
/// <param name="doWeMeasure"></param> If true, measure the thermodynamic variables, else, don't
void addAWorm() {
	wormSize = 0;
	//First, we place the head of the worm somewhere on the lattice.
	//		First the coordinates of the cell
	int x = rand() % L; // e[0;L-1]
	int y = rand() % L;
	int z = rand() % L;

	//And then the tetrahedron
	int rng = rand() % 4;
	char tetra = 'A';
	switch (rng)
	{
	case 0:
		tetra = 'A';
		break;
	case 1:
		tetra = 'B';
		break;
	case 2:
		tetra = 'C';
		break;
	case 3:
		tetra = 'D';
		break;
	}
	int initialDefect = g_lattice[x][y][z][rng];


	     if (initialDefect == 0) {nA = 1; nB = 2; nC = 3;}
	else if (initialDefect == 1) {nA = 0; nB = 2; nC = 3;}
	else if (initialDefect == 2) {nA = 0; nB = 1; nC = 3;}
	else                         {nA = 0; nB = 1; nC = 2;}
	nD = initialDefect;
	/*
	std::cout << x << " " << y << " " << z << "  " << tetra << g_lattice[x][y][z][rng] << std::endl;
	*/

	//We identify the three spins that are on the same down tetrahedron as the first to use for closing check. one of these must be the last in the loop
	/*
	std::cout << nA << " " << nB << " " << nC << std::endl;
	*/
	next(x, y, z, tetra, initialDefect, nA, 0, &xA, &yA, &zA, &tetraA, &nA);
	next(x, y, z, tetra, initialDefect, nB, 0, &xB, &yB, &zB, &tetraB, &nB);
	next(x, y, z, tetra, initialDefect, nC, 0, &xC, &yC, &zC, &tetraC, &nC);
	xD = x;	yD = y;	zD = z;	tetraD = tetra;



	//We also need to choose the spin where it will exit
	double rng2 = (double)rand() / RAND_MAX;
	int dimer;
	if (                                                                      rng2 < g_proba[0][initialDefect]) {
		dimer = 0;
		wormSize += 1;
	}
	else if (                            g_proba[0][initialDefect] <= rng2 && rng2 < g_proba[0][initialDefect] + g_proba[1][initialDefect]) {
		dimer = 1;
		wormSize += 1;
	}
	else if (g_proba[0][initialDefect] + g_proba[1][initialDefect] <= rng2 && rng2 < g_proba[0][initialDefect] + g_proba[1][initialDefect] + g_proba[2][initialDefect]) {
		dimer = 2;
		wormSize += 1;
	}
	else {
		dimer = 3;
		wormSize += 1;
	}


	g_lattice[x][y][z][rng] = dimer;

	/*
	std::cout << std::endl << "The final dimers can be:" << std::endl;
	std::cout << xA << " " << yA << " " << zA << "  " << tetraA << nA << std::endl;
	std::cout << xB << " " << yB << " " << zB << "  " << tetraB << nB << std::endl;
	std::cout << xC << " " << yC << " " << zC << "  " << tetraC << nC << std::endl;
	std::cout << xD << " " << yD << " " << zD << "  " << tetraD << nD << std::endl;

	std::cout << std::endl << "The worm is made of:" << std::endl;//*/

	//The worm propagate
	while (!check(x, y, z, tetra, dimer)) {
		growTheWorm(&x, &y, &z, &tetra, &dimer);
		//std::cout << x << " " << y << " " << z << "  " << tetra << dimer << std::endl;
		wormSize += 1;
	}
}

bool check(int x, int y, int z, char tetra, int n) {
	if (x == xA && y == yA && z == zA && tetra == tetraA && n == nA) {
		return(true);
	}
	if (x == xB && y == yB && z == zB && tetra == tetraB && n == nB) {
		return(true);
	}
	if (x == xC && y == yC && z == zC && tetra == tetraC && n == nC) {
		return(true);
	}
	if (x == xD && y == yD && z == zD && tetra == tetraD && n == nD) {
		return(true);
	}
	return(false);
}