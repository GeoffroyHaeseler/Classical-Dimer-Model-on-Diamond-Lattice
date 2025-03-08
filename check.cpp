#include "check.h"

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
	return(false);
}