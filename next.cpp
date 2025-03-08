#include <iostream>
#include <stdio.h>

#include "defs.h"
#include "next.h"

void next(const int next_xin, const int next_yin, const int next_zin, const char next_tetrain, const int next_nin, const int next_nnew, const int next_local, int* next_xout, int* next_yout, int* next_zout, char* next_tetraout, int* next_nout)
{

    /*
    xin, yin, zin correspond to the cube coordinates in the canonical basis. (This is a Faces Centered Cubic, FCC, cell)
    tetrain correspound to a specific tetrahedron in the cube.
    Theses information define the worm head position.
    nin correspond to a specific spin in the tetrahedron.
    This information depend on the previous worm position.

    But we also need to know where the worm will go.
    To do this we need it's next location :
    The worm might stay in the same up tetrahedron, in this case local=1, in the other case local=0.
    It will also change spin, so the user must entered the next nout, which is made through nnew.

    The goal of this algorithm is there to compute mout (poistion of the potential new cell) and xout oyut and zout
                 _________________________
                /|                      / |
               /    D                  /  |
              /  |                    /   |
        ^    /_______________________/    |
       / \   |   |                   |    |
        |    |                 B     |    |
        |    |   |                   |    |
     -> |    |                       |    |
     ez |    |   |_ _ _ _ _ _ _ _ _ _|_C_ |
        |   _|   /                   |   /
        |-> /|     A                 |  /
        |ey/ | /                     | /
        | /  |_______________________|/
        |/
        0------------------------->
                    ->
                    ex



    -->    -->  -->    -->  -->    -->
    AB = 2*ux   AC = 2*uy   AB = 2*uz

                                               0             1             1
    where, in the (ex, ey, ez) base : ux =1/4  1    uy =1/4  0    uz =1/4  1
                                               1             1             0

    */


    //The out spin will be the asked one.
    *next_nout = next_nnew;

    //If the tetrahedron is not changed, nothing reaaly change except the spin
    if (next_local == 1)
    {
        *next_xout = next_xin;
        *next_yout = next_yin;
        *next_zout = next_zin;
        *next_tetraout = next_tetrain;
    }
    else //local == 0 => The tetrahedron is changed
    {
        switch (next_tetrain)
        {
        case 'A':
            switch (next_nin) {
            case 0: //Handle the cases where we leave a tetrahedron A from a spin 0
                switch (next_nnew) {
                case 1: //From tetrahedron A to B, from a spin 0 to 1, follow  +ux  axis
                    *next_xout = next_xin;
                    *next_yout = next_yin;
                    *next_zout = next_zin;
                    *next_tetraout = 'B';
                    break;
                case 2: //From tetrahedron A to C, from a spin 0 to 2, follow  +uy  axis
                    *next_xout = next_xin;
                    *next_yout = next_yin;
                    *next_zout = next_zin;
                    *next_tetraout = 'C';
                    break;
                case 3: //From tetrahedron A to D, from a spin 0 to 3, follow  +uz  axis
                    *next_xout = next_xin;
                    *next_yout = next_yin;
                    *next_zout = next_zin;
                    *next_tetraout = 'D';
                    break;
                }
                break;

            case 1: //Handle the cases where we leave a tetrahedron A from a spin 1
                switch (next_nnew) {
                case 0: //From tetrahedron A to B, from a spin 1 to 0, follow  -ux  axis
                    *next_xout = next_xin;
                    *next_yout = next_yin - 1;
                    *next_zout = next_zin - 1;
                    *next_tetraout = 'B';
                    break;
                case 2: //From tetrahedron A to D, from a spin 1 to 2, follow uy-ux axis
                    *next_xout = next_xin;
                    *next_yout = next_yin - 1;
                    *next_zout = next_zin;
                    *next_tetraout = 'D';
                    break;
                case 3: //From tetrahedron A to C, from a spin 1 to 3, follow uz-ux axis
                    *next_xout = next_xin;
                    *next_yout = next_yin;
                    *next_zout = next_zin - 1;
                    *next_tetraout = 'C';
                    break;
                }
                break;

            case 2: //Handle the cases where we leave a tetrahedron A from a spin 2
                switch (next_nnew) {
                case 0: //From tetrahedron A to C, from a spin 2 to 0, follow  -uy  axis
                    *next_xout = next_xin - 1;
                    *next_yout = next_yin;
                    *next_zout = next_zin - 1;
                    *next_tetraout = 'C';
                    break;
                case 1: //From tetrahedron A to D, from a spin 2 to 1, follow ux-uy axis
                    *next_xout = next_xin - 1;
                    *next_yout = next_yin;
                    *next_zout = next_zin;
                    *next_tetraout = 'D';
                    break;
                case 3: //From tetrahedron A to B, from a spin 2 to 3, follow uz-uy axis
                    *next_xout = next_xin;
                    *next_yout = next_yin;
                    *next_zout = next_zin - 1;
                    *next_tetraout = 'B';
                    break;
                }
                break;

            case 3: //Handle the cases where we leave a tetrahedron A from a spin 3
                switch (next_nnew) {
                case 0: //From tetrahedron A to D, from a spin 3 to 0, follow  -uz  axis
                    *next_xout = next_xin - 1;
                    *next_yout = next_yin - 1;
                    *next_zout = next_zin;
                    *next_tetraout = 'D';
                    break;
                case 1: //From tetrahedron A to C, from a spin 3 to 1, follow ux-uz axis
                    *next_xout = next_xin - 1;
                    *next_yout = next_yin;
                    *next_zout = next_zin;
                    *next_tetraout = 'C';
                    break;
                case 2: //From tetrahedron A to B, from a spin 3 to 2, follow uy-uz axis
                    *next_xout = next_xin;
                    *next_yout = next_yin - 1;
                    *next_zout = next_zin;
                    *next_tetraout = 'B';
                    break;
                }
                break;
            }
            break;

        case 'B':
            switch (next_nin) {
            case 0: //Handle the cases where we leave a tetrahedron B from a spin 0
                switch (next_nnew) {
                case 1: //From tetrahedron B to A, from a spin 0 to 1, follow  +ux  axis
                    *next_xout = next_xin;
                    *next_yout = next_yin + 1;
                    *next_zout = next_zin + 1;
                    *next_tetraout = 'A';
                    break;
                case 2: //From tetrahedron B to D, from a spin 0 to 2, follow  +uy  axis
                    *next_xout = next_xin;
                    *next_yout = next_yin;
                    *next_zout = next_zin + 1;
                    *next_tetraout = 'D';
                    break;
                case 3: //From tetrahedron B to C, from a spin 0 to 3, follow  +uz  axis
                    *next_xout = next_xin;
                    *next_yout = next_yin + 1;
                    *next_zout = next_zin;
                    *next_tetraout = 'C';
                    break;
                }
                break;

            case 1: //Handle the cases where we leave a tetrahedron B from a spin 1
                switch (next_nnew) {
                case 0: //From tetrahedron B to A, from a spin 1 to 0, follow  -ux  axis
                    *next_xout = next_xin;
                    *next_yout = next_yin;
                    *next_zout = next_zin;
                    *next_tetraout = 'A';
                    break;
                case 2: //From tetrahedron B to C, from a spin 1 to 2, follow uy-ux axis
                    *next_xout = next_xin;
                    *next_yout = next_yin;
                    *next_zout = next_zin;
                    *next_tetraout = 'C';
                    break;
                case 3: //From tetrahedron B to D, from a spin 1 to 3, follow uz-ux axis
                    *next_xout = next_xin;
                    *next_yout = next_yin;
                    *next_zout = next_zin;
                    *next_tetraout = 'D';
                    break;
                }
                break;

            case 2: //Handle the cases where we leave a tetrahedron B from a spin 2
                switch (next_nnew) {
                case 0: //From tetrahedron B to D, from a spin 2 to 0, follow  -uy  axis
                    *next_xout = next_xin - 1;
                    *next_yout = next_yin;
                    *next_zout = next_zin;
                    *next_tetraout = 'D';
                    break;
                case 1: //From tetrahedron B to C, from a spin 2 to 1, follow ux-uy axis
                    *next_xout = next_xin - 1;
                    *next_yout = next_yin + 1;
                    *next_zout = next_zin;
                    *next_tetraout = 'C';
                    break;
                case 3: //From tetrahedron B to A, from a spin 2 to 3, follow uz-uy axis
                    *next_xout = next_xin;
                    *next_yout = next_yin + 1;
                    *next_zout = next_zin;
                    *next_tetraout = 'A';
                    break;
                }
                break;

            case 3: //Handle the cases where we leave a tetrahedron B from a spin 3
                switch (next_nnew) {
                case 0: //From tetrahedron B to C, from a spin 3 to 0, follow  -uz  axis
                    *next_xout = next_xin - 1;
                    *next_yout = next_yin;
                    *next_zout = next_zin;
                    *next_tetraout = 'C';
                    break;
                case 1: //From tetrahedron B to D, from a spin 3 to 1, follow ux-uy axis
                    *next_xout = next_xin - 1;
                    *next_yout = next_yin;
                    *next_zout = next_zin + 1;
                    *next_tetraout = 'D';
                    break;
                case 2: //From tetrahedron B to A, from a spin 3 to 2, follow uy-uz axis
                    *next_xout = next_xin;
                    *next_yout = next_yin;
                    *next_zout = next_zin + 1;
                    *next_tetraout = 'A';
                    break;
                }
                break;
            }
            break;

        case 'C':
            switch (next_nin) {
            case 0: //Handle the cases where we leave a tetrahedron C from a spin 0
                switch (next_nnew) {
                case 1: //From tetrahedron C to D, from a spin 0 to 1, follow  -ux  axis
                    *next_xout = next_xin;
                    *next_yout = next_yin;
                    *next_zout = next_zin + 1;
                    *next_tetraout = 'D';
                    break;
                case 2: //From tetrahedron C to A, from a spin 0 to 2, follow  +uy  axis
                    *next_xout = next_xin + 1;
                    *next_yout = next_yin;
                    *next_zout = next_zin + 1;
                    *next_tetraout = 'A';
                    break;
                case 3: //From tetrahedron C to B, from a spin 0 to 3, follow  +uz  axis
                    *next_xout = next_xin + 1;
                    *next_yout = next_yin;
                    *next_zout = next_zin;
                    *next_tetraout = 'B';
                    break;
                }
                break;

            case 1: //Handle the cases where we leave a tetrahedron C from a spin 1
                switch (next_nnew) {
                case 0: //From tetrahedron C to D, from a spin 1 to 0, follow  -ux  axis
                    *next_xout = next_xin;
                    *next_yout = next_yin - 1;
                    *next_zout = next_zin;
                    *next_tetraout = 'D';
                    break;
                case 2: //From tetrahedron C to B, from a spin 1 to 2, follow uy-ux axis
                    *next_xout = next_xin + 1;
                    *next_yout = next_yin - 1;
                    *next_zout = next_zin;
                    *next_tetraout = 'B';
                    break;
                case 3: //From tetrahedron C to A, from a spin 1 to 3, follow uz-ux axis
                    *next_xout = next_xin + 1;
                    *next_yout = next_yin;
                    *next_zout = next_zin;
                    *next_tetraout = 'A';
                    break;
                }
                break;

            case 2: //Handle the cases where we leave a tetrahedron C from a spin 2
                switch (next_nnew) {
                case 0: //From tetrahedron C to A, from a spin 2 to 0, follow  -uy  axis
                    *next_xout = next_xin;
                    *next_yout = next_yin;
                    *next_zout = next_zin;
                    *next_tetraout = 'A';
                    break;
                case 1: //From tetrahedron C to B, from a spin 2 to 1, follow ux-uy axis
                    *next_xout = next_xin;
                    *next_yout = next_yin;
                    *next_zout = next_zin;
                    *next_tetraout = 'B';
                    break;
                case 3: //From tetrahedron C to D, from a spin 2 to 3, follow uz-uy axis
                    *next_xout = next_xin;
                    *next_yout = next_yin;
                    *next_zout = next_zin;
                    *next_tetraout = 'D';
                    break;
                }
                break;

            case 3: //Handle the cases where we leave a tetrahedron C from a spin 3
                switch (next_nnew) {
                case 0: //From tetrahedron C to B, from a spin 3 to 0, follow  -uz  axis
                    *next_xout = next_xin;
                    *next_yout = next_yin - 1;
                    *next_zout = next_zin;
                    *next_tetraout = 'B';
                    break;
                case 1: //From tetrahedron C to A, from a spin 3 to 1, follow ux-uz axis
                    *next_xout = next_xin;
                    *next_yout = next_yin;
                    *next_zout = next_zin + 1;
                    *next_tetraout = 'A';
                    break;
                case 2: //From tetrahedron C to D, from a spin 3 to 2, follow uy-uz axis
                    *next_xout = next_xin;
                    *next_yout = next_yin - 1;
                    *next_zout = next_zin + 1;
                    *next_tetraout = 'D';
                    break;
                }
                break;
            }
            break;

        case 'D':
            switch (next_nin) {
            case 0: //Handle the cases where we leave a tetrahedron D from a spin 0
                switch (next_nnew) {
                case 1: //From tetrahedron D to C, from a spin 0 to 1, follow  +ux  axis
                    *next_xout = next_xin;
                    *next_yout = next_yin + 1;
                    *next_zout = next_zin;
                    *next_tetraout = 'C';
                    break;
                case 2: //From tetrahedron D to B, from a spin 0 to 2, follow  +uy  axis
                    *next_xout = next_xin + 1;
                    *next_yout = next_yin;
                    *next_zout = next_zin;
                    *next_tetraout = 'B';
                    break;
                case 3: //From tetrahedron D to A, from a spin 0 to 3, follow  +uz  axis
                    *next_xout = next_xin + 1;
                    *next_yout = next_yin + 1;
                    *next_zout = next_zin;
                    *next_tetraout = 'A';
                    break;
                }
                break;

            case 1: //Handle the cases where we leave a tetrahedron D from a spin 1
                switch (next_nnew) {
                case 0: //From tetrahedron D to C, from a spin 1 to 0, follow  -ux  axis
                    *next_xout = next_xin;
                    *next_yout = next_yin;
                    *next_zout = next_zin - 1;
                    *next_tetraout = 'C';
                    break;
                case 2: //From tetrahedron D to A, from a spin 1 to 2, follow uy-ux axis
                    *next_xout = next_xin + 1;
                    *next_yout = next_yin;
                    *next_zout = next_zin;
                    *next_tetraout = 'A';
                    break;
                case 3: //From tetrahedron D to B, from a spin 1 to 3, follow uz-ux axis
                    *next_xout = next_xin + 1;
                    *next_yout = next_yin;
                    *next_zout = next_zin - 1;
                    *next_tetraout = 'B';
                    break;
                }
                break;

            case 2: //Handle the cases where we leave a tetrahedron D from a spin 2
                switch (next_nnew) {
                case 0: //From tetrahedron D to B, from a spin 2 to 0, follow  -uy  axis
                    *next_xout = next_xin;
                    *next_yout = next_yin;
                    *next_zout = next_zin - 1;
                    *next_tetraout = 'B';
                    break;
                case 1: //From tetrahedron D to A, from a spin 2 to 1, follow ux-uy axis
                    *next_xout = next_xin;
                    *next_yout = next_yin + 1;
                    *next_zout = next_zin;
                    *next_tetraout = 'A';
                    break;
                case 3: //From tetrahedron D to C, from a spin 2 to 3, follow uz-uy axis
                    *next_xout = next_xin;
                    *next_yout = next_yin + 1;
                    *next_zout = next_zin - 1;
                    *next_tetraout = 'C';
                    break;
                }
                break;

            case 3: //Handle the cases where we leave a tetrahedron D from a spin 3
                switch (next_nnew) {
                case 0: //From tetrahedron D to A, from a spin 3 to 0, follow  -uz  axis
                    *next_xout = next_xin;
                    *next_yout = next_yin;
                    *next_zout = next_zin;
                    *next_tetraout = 'A';
                    break;
                case 1: //From tetrahedron D to B, from a spin 3 to 1, follow ux-uz axis
                    *next_xout = next_xin;
                    *next_yout = next_yin;
                    *next_zout = next_zin;
                    *next_tetraout = 'B';
                    break;
                case 2: //From tetrahedron D to C, from a spin 3 to 2, follow uy-uz axis
                    *next_xout = next_xin;
                    *next_yout = next_yin;
                    *next_zout = next_zin;
                    *next_tetraout = 'C';
                    break;
                }
                break;
            }
            break;
        } //end switch(next_tetrain)
    }   //end else(next_local=0)



    //We must now take in account the PBC.
    //Since we took a complicated cell made of 4 tetrahedrons (16 spins) the PBC are trivial.
    //We just need to reset the extrem value to the other extrem :
    //  xout=L <=> xout=0 and xout=-1 <=> xout=L-1
    //  yout=L <=> yout=0 and yout=-1 <=> yout=L-1
    //  zout=L <=> zout=0 and zout=-1 <=> zout=L-1

    if (*next_xout == L) { *next_xout = 0; }

    if (*next_yout == L) { *next_yout = 0; }

    if (*next_zout == L) { *next_zout = 0; }


    if (*next_xout == -1) { *next_xout = L - 1; }

    if (*next_yout == -1) { *next_yout = L - 1; }

    if (*next_zout == -1) { *next_zout = L - 1; }
}
