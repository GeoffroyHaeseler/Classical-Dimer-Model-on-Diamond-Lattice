#include "spin.h"
#include "defs.h"

extern int g_lattice[L][L][L][4];

void spinCoordinates(char spin_tetra, int spin_n, double* spin_coord_x, double* spin_coord_y, double* spin_coord_z)
{

    switch (spin_tetra) {
    case 'A':
        *spin_coord_x = *spin_coord_x + 0.25;
        *spin_coord_y = *spin_coord_y + 0.25;
        *spin_coord_z = *spin_coord_z + 0.25;
        break;
    case 'B':
        *spin_coord_x = *spin_coord_x + 0.25;
        *spin_coord_y = *spin_coord_y + 0.75;
        *spin_coord_z = *spin_coord_z + 0.75;
        break;
    case 'C':
        *spin_coord_x = *spin_coord_x + 0.75;
        *spin_coord_y = *spin_coord_y + 0.25;
        *spin_coord_z = *spin_coord_z + 0.75;
        break;
    case 'D':
        *spin_coord_x = *spin_coord_x + 0.75;
        *spin_coord_y = *spin_coord_y + 0.75;
        *spin_coord_z = *spin_coord_z + 0.25;
        break;
    }

    switch (spin_n) {
    case 0:
        *spin_coord_x = *spin_coord_x + 0.125;
        *spin_coord_y = *spin_coord_y + 0.125;
        *spin_coord_z = *spin_coord_z + 0.125;
        break;
    case 1:
        *spin_coord_x = *spin_coord_x + 0.125;
        *spin_coord_y = *spin_coord_y - 0.125;
        *spin_coord_z = *spin_coord_z - 0.125;
        break;
    case 2:
        *spin_coord_x = *spin_coord_x - 0.125;
        *spin_coord_y = *spin_coord_y + 0.125;
        *spin_coord_z = *spin_coord_z - 0.125;
        break;
    case 3:
        *spin_coord_x = *spin_coord_x - 0.125;
        *spin_coord_y = *spin_coord_y - 0.125;
        *spin_coord_z = *spin_coord_z + 0.125;
        break;
    }
}

int spinLine(int ix, int iy, int iz, char tetrahedron, int submit) {
    int N = 0; //N will correspond to the ligne {ix iy iz 'tetrahedron' + S0}
    N = ix + L * iy + L * L * iz;
    N = 80 * N; //There is 80 vertices per cell.
    //N is for now the number of the line {ix iy iz A + S0}

    switch (tetrahedron)
    {
    case'A':
        N = N + 0;
        break;
    case 'B':
        N = N + 20;
        break;
    case 'C':
        N = N + 40;
        break;
    case 'D':
        N = N + 60;
        break;
    }

    switch (submit)
    {
    case 0:
        N = N + 0;
        break;
    case 1:
        N = N + 5;
        break;
    case 2:
        N = N + 10;
        break;
    case 3:
        N = N + 15;
        break;
    }
    return(N);
}

/// <summary>
/// return 1 if the selected spin is in and -1 if it is out.
/// </summary>
/// <param name="ix"></param>
/// <param name="iy"></param>
/// <param name="iz"></param>
/// <param name="itetra"></param>
/// <param name="isubmit"></param>
/// <returns></returns>
int pseudospin(int ix, int iy, int iz, int itetra, int isubmit) {
    if (g_lattice[ix][iy][iz][itetra] == isubmit) {
        return(-1);
    }
    else
    {
        return(1);
    }
}