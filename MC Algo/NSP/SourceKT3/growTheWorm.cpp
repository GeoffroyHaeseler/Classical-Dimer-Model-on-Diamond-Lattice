#include <iostream>     /*in/out console print*/
#include <stdlib.h>     /* srand, rand */

#include "growTheWorm.h"
#include "defs.h"
#include "next.h"

extern double g_proba[4][4];
extern int g_lattice[L][L][L][4];

extern double g_systemEnergy;
extern double g_energyDifference[4][4];

extern double g_magnetisationDifference[4][4];
extern double g_systemMagnetisation;


void growTheWorm(int* x, int* y, int* z, char* tetra, int* n) {
	//x, y, z, tetra and n indicates the position and the new direction of the last dimer flip
	int prev_n = *n; //contains the previous direction

	//We need to pass the down triangle to go into the next up triangle. To do this, we must follow the dimer.
	int i = 0;
	bool isDownTetraPassed = false;
	int look_x, look_y, look_z, look_dimer;
	char look_tetra;
	//We are in a down tetrahedron, we reach the next up tetrahedron while following the 3 out 1 in rule
	for (i = 0; i < 4; i++) {//We look the four spins around us. Each one is coming from a different up tetrahedron.
		if (*n != i && !isDownTetraPassed) {//If it's not the one we come from
			next(*x, *y, *z, *tetra, *n, i, 0, &look_x, &look_y, &look_z, &look_tetra, &look_dimer); //we take up tetrahedron's coordinates,
			//							      next dimer __/    \__ local = 0 : we change tetrahedron.
			switch (look_tetra)
			{
			case 'A':
				if (g_lattice[look_x][look_y][look_z][0] == i) {//and if it is the down tetrahedron dimer
					*x = look_x;//we leave the down triangle through it.
					*y = look_y;
					*z = look_z;
					*tetra = look_tetra;
					*n = i;
					isDownTetraPassed = true;
				}
				break;
			case 'B':
				if (g_lattice[look_x][look_y][look_z][1] == i) {//and if it is the down tetrahedron dimer
					*x = look_x;//we leave the down triangle through it.
					*y = look_y;
					*z = look_z;
					*tetra = look_tetra;
					*n = i;
					isDownTetraPassed = true;
				}
				break;
			case 'C':
				if (g_lattice[look_x][look_y][look_z][2] == i) {//and if it is the down tetrahedron dimer
					*x = look_x;//we leave the down triangle through it.
					*y = look_y;
					*z = look_z;
					*tetra = look_tetra;
					*n = i;
					isDownTetraPassed = true;
				}
				break;
			case 'D':
				if (g_lattice[look_x][look_y][look_z][3] == i) {//and if it is the down tetrahedron dimer
					*x = look_x;//we leave the down triangle through it.
					*y = look_y;
					*z = look_z;
					*tetra = look_tetra;
					*n = i;
					isDownTetraPassed = true;
				}
				break;
			}
		}
	}

	//We must now choose which down triangle Worm1 will enter.
	double rng = (double)rand() / RAND_MAX;
	//We choose spin 0
	if (rng < g_proba[0][*n]) { next(*x, *y, *z, *tetra, *n, 0, 1, x, y, z, tetra, n); }

	//We choose spin 1
	else if (g_proba[0][*n] <= rng && rng < g_proba[0][*n] + g_proba[1][*n]) { next(*x, *y, *z, *tetra, *n, 1, 1, x, y, z, tetra, n); }

	//We choose spin 2
	else if (g_proba[0][*n] + g_proba[1][*n] <= rng && rng < g_proba[0][*n] + g_proba[1][*n] + g_proba[2][*n]) { next(*x, *y, *z, *tetra, *n, 2, 1, x, y, z, tetra, n); }

	//We choose spin 3
	else { next(*x, *y, *z, *tetra, *n, 3, 1, x, y, z, tetra, n); }

	//we are now able to create a new metamere. We still didn't add it to the worm which stay in the previous down tetrahedron.
	switch (*tetra)
	{
	case 'A':
		g_lattice[*x][*y][*z][0] = *n;
		break;
	case 'B':
		g_lattice[*x][*y][*z][1] = *n;
		break;
	case 'C':
		g_lattice[*x][*y][*z][2] = *n;
		break;
	case 'D':
		g_lattice[*x][*y][*z][3] = *n;
		break;
	}
}