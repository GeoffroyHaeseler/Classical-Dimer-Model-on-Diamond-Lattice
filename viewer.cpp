#include <iostream>
#include <fstream> 
#include <math.h>

#include "defs.h"
#include "viewer.h"
#include "spin.h"

extern int g_lattice[L][L][L][4];

void addVertices(char tetrahedron, int submit, double ix, double iy, double iz) {
	std::fstream myfile;
	myfile.open("results.ply", std::fstream::out | std::fstream::app);

	spinCoordinates(tetrahedron, submit, &ix, &iy, &iz);

	switch (submit)
	{
	case 0:
		myfile << ix       << " " << iy       << " " << iz       << "    {Vertex " << int(ix) << " " << int(iy) << " " << int(iz) << " " << tetrahedron << " + S" << submit << "}" << std::endl;
		myfile << ix       << " " << iy - 0.1 << " " << iz - 0.1 << std::endl; //vertex from 0 to 1
		myfile << ix - 0.1 << " " << iy       << " " << iz - 0.1 << std::endl; //vertex from 0 to 2
		myfile << ix - 0.1 << " " << iy - 0.1 << " " << iz       << std::endl; //vertex from 0 to 3
		myfile << ix - 0.3 << " " << iy - 0.3 << " " << iz - 0.3 << std::endl; //vertex between 1 2 and 3
		break;
	case 1:
		myfile << ix       << " " << iy       << " " << iz       << "    {Vertex " << int(ix) << " " << int(iy) << " " << int(iz) << " " << tetrahedron << " + S" << submit << "}" << std::endl;
		myfile << ix       << " " << iy + 0.1 << " " << iz + 0.1 << std::endl; //vertex from 1 to 0
		myfile << ix - 0.1 << " " << iy       << " " << iz + 0.1 << std::endl; //vertex from 1 to 2
		myfile << ix - 0.1 << " " << iy + 0.1 << " " << iz       << std::endl; //vertex from 1 to 3
		myfile << ix - 0.3 << " " << iy + 0.3 << " " << iz + 0.3 << std::endl; //vertex between 0 2 and 3
		break;
	case 2:
		myfile << ix       << " " << iy       << " " << iz       << "    {Vertex " << int(ix) << " " << int(iy) << " " << int(iz) << " " << tetrahedron << " + S" << submit << "}" << std::endl;
		myfile << ix       << " " << iy - 0.1 << " " << iz + 0.1 << std::endl; //vertex from 2 to 0
		myfile << ix + 0.1 << " " << iy       << " " << iz + 0.1 << std::endl; //vertex from 2 to 1
		myfile << ix + 0.1 << " " << iy - 0.1 << " " << iz       << std::endl; //vertex from 2 to 3
		myfile << ix + 0.3 << " " << iy - 0.3 << " " << iz + 0.3 << std::endl; //vertex between 0 1 and 3
		break;
	case 3:
		myfile << ix       << " " << iy       << " " << iz       << "    {Vertex " << int(ix) << " " << int(iy) << " " << int(iz) << " " << tetrahedron << " + S" << submit << "}" << std::endl;
		myfile << ix       << " " << iy + 0.1 << " " << iz - 0.1 << std::endl; //vertex from 3 to 0
		myfile << ix + 0.1 << " " << iy       << " " << iz - 0.1 << std::endl; //vertex from 3 to 1
		myfile << ix + 0.1 << " " << iy + 0.1 << " " << iz       << std::endl; //vertex from 3 to 2
		myfile << ix + 0.3 << " " << iy + 0.3 << " " << iz - 0.3 << std::endl; //vertex between 0 1 and 2
		break;
	}
	myfile.close();
}

void addFaces(char tetrahedron, int ix, int iy, int iz) {
	std::fstream myfile;
	myfile.open("results.ply", std::fstream::out | std::fstream::app);

	int N; //N will correspond to the ligne {ix iy iz 'tetrahedron' + S0}
	N = spinLine(ix, iy, iz, tetrahedron, 0);

	//Only now N is is number of the line {ix iy iz tetrahedron + S0}

	myfile << 3 << " " << N     << " " << N + 4  << " " << N + 8  << "    {Face " << ix << " " << iy << " " << iz << " " << tetrahedron << "}" << std::endl;
	myfile << 3 << " " << N     << " " << N + 8  << " " << N + 12 << std::endl;
	myfile << 3 << " " << N     << " " << N + 12 << " " << N + 4  << std::endl;
	myfile << 3 << " " << N + 4 << " " << N + 8  << " " << N + 12 << std::endl;

	myfile.close();
}

void addArrow(int ix, int iy, int iz, char tetrahedron, int submit){
	std::fstream myfile;
	myfile.open("results.ply", std::fstream::out | std::fstream::app); 
	
	int N; //N is the {ix iy iz tetrahedron + Ssubmit}
	N = spinLine(ix, iy, iz, tetrahedron, submit);

	myfile << 3 << " " << N     << " " << N + 1 << " " << N + 2 << "    {Arrow " << ix << " " << iy << " " << iz << " " << tetrahedron << " + S" << submit << "}" << std::endl;
	myfile << 3 << " " << N     << " " << N + 2 << " " << N + 3 << std::endl;
	myfile << 3 << " " << N     << " " << N + 3 << " " << N + 1 << std::endl;
	myfile << 3 << " " << N + 4 << " " << N + 1 << " " << N + 2 << std::endl;
	myfile << 3 << " " << N + 4 << " " << N + 2 << " " << N + 3 << std::endl;
	myfile << 3 << " " << N + 4 << " " << N + 3 << " " << N + 1 << std::endl;
	myfile.close();
}


void viewer() {
	std::ofstream myfile("results.ply");

	myfile << "ply" << std::endl;
	myfile << "format ascii 1.0" << std::endl;
	myfile << "comment author: Geoffroy Haeseler" << std::endl;
	myfile << "comment object: results" << std::endl;

	//We need to know precisly how many vertices (Nv) and faces (Nf) they will be.
	 
	/*Nv is the number of cell (L³) times the number of vertices per cell. There's 4 tetrahedrons per cell.
	Nv is therefor 4*L³ times the number of vertices per tetrahedron.
	Since there are four submits in a tetrahedron, we could guess there's 4*4*L³ vertices in the lattice.
	However we need to take in count the vertices use to print dimers. Which count as three more per submits.
	Therefor:*/
	int Nv = 80 * L * L * L;

	/*Nf is the number of faces in a cell.There's 4 tetrahedrons per cell.
	Nf is therefor 4*L³ times the number of faces per tetrahedron.
	Since there are four faces in a tetrahedron, we could guess there's 4*4*L³ faces in the lattice.
	However we need to take in count the faces use to print dimers. Which count as four more per tetrahedron.*/
	int Nf = 24 * L * L * L;

	myfile << "element vertex " << Nv << "                     {Vertex type definition}" << std::endl;
	myfile << "property double x" << std::endl;
	myfile << "property double y" << std::endl;
	myfile << "property double z" << std::endl;

	myfile << "element face " << Nf << "                       {Face type definition}" << std::endl;
	myfile << "property list uchar int vertex_index" << std::endl;

	myfile << "end_header                            {Start the vertex list}" << std::endl;
	

	//Start the vertices list.
	int ix = 0;
	int iy = 0;
	int iz = 0;

	myfile.close();

	for (iz = 0; iz < L; iz++)
	{
		for (iy = 0; iy < L; iy++)
		{
			for (ix = 0; ix < L; ix++)
			{
				addVertices('A', 0, ix, iy, iz);
				addVertices('A', 1, ix, iy, iz);
				addVertices('A', 2, ix, iy, iz);
				addVertices('A', 3, ix, iy, iz);

				addVertices('B', 0, ix, iy, iz);
				addVertices('B', 1, ix, iy, iz);
				addVertices('B', 2, ix, iy, iz);
				addVertices('B', 3, ix, iy, iz);

				addVertices('C', 0, ix, iy, iz);
				addVertices('C', 1, ix, iy, iz);
				addVertices('C', 2, ix, iy, iz);
				addVertices('C', 3, ix, iy, iz);

				addVertices('D', 0, ix, iy, iz);
				addVertices('D', 1, ix, iy, iz);
				addVertices('D', 2, ix, iy, iz);
				addVertices('D', 3, ix, iy, iz);
			}
		}
	}

	
	//Start the main tetrahedrons faces list.
	/*
	ix = 0;
	iy = 0;
	iz = 0;
	
	for (iz = 0; iz < L; iz++)
	{
		for (iy = 0; iy < L; iy++)
		{
			for (ix = 0; ix < L; ix++)
			{
				addFaces('A', ix, iy, iz);
				addFaces('B', ix, iy, iz);
				addFaces('C', ix, iy, iz);
				addFaces('D', ix, iy, iz);
			}
		}
	}
	*/

	//Start the arrow face list.
	ix = 0;
	iy = 0;
	iz = 0;
	for (iz = 0; iz < L; iz++) {
		for (iy = 0; iy < L; iy++) {
			for (ix = 0; ix < L; ix++) {
				addArrow(ix, iy, iz, 'A', g_lattice[ix][iy][iz][0]);
				addArrow(ix, iy, iz, 'B', g_lattice[ix][iy][iz][1]);
				addArrow(ix, iy, iz, 'C', g_lattice[ix][iy][iz][2]);
				addArrow(ix, iy, iz, 'D', g_lattice[ix][iy][iz][3]);
			}
		}
	}

	//Handle cube.ply
	myfile.open("cube.ply", std::fstream::out | std::fstream::app);

	myfile << "ply" << std::endl;
	myfile << "format ascii 1.0" << std::endl;
	myfile << "comment author: Geoffroy Haeseler" << std::endl;
	myfile << "comment object: cube" << std::endl;

	Nv = (L + 1) * (L + 1) * (L + 1);
	Nf = 8 * L * L * L;

	myfile << "element vertex " << Nv << "                     {Vertex type definition}" << std::endl;
	myfile << "property double x" << std::endl;
	myfile << "property double y" << std::endl;
	myfile << "property double z" << std::endl;

	myfile << "element face " << Nf << "                       {Face type definition}" << std::endl;
	myfile << "property list uchar int vertex_index" << std::endl;

	myfile << "end_header                            {Start the vertex list}" << std::endl;

	//Start the vertices list.
	ix = 0;
	iy = 0;
	iz = 0;

	for (iz = 0; iz < L + 1; iz++)
	{
		for (iy = 0; iy < L + 1; iy++)
		{
			for (ix = 0; ix < L + 1; ix++)
			{
				myfile << ix << " " << iy << " " << iz << std::endl;
			}
		}
	}

	//Start the face list
	ix = 0;
	iy = 0;
	iz = 0;
	
	for (iz = 0; iz < L + 1; iz++)
	{
		for (iy = 0; iy < L + 1; iy++)
		{
			for (ix = 0; ix < L + 1; ix++)
			{
				//0 0 1 planes
				myfile << 4 << " " << ix + iy * (L + 1) + iz * (L + 1) * (L + 1) << " " << (ix + 1) + iy * (L + 1) + iz * (L + 1) * (L + 1) << " " << (ix + 1) + (iy + 1) * (L + 1) + iz * (L + 1) * (L + 1) << " " << ix + (iy + 1) * (L + 1) + iz * (L + 1) * (L + 1) << std::endl;
				//0 1 0 planes
				myfile << 4 << " " << ix + iy * (L + 1) + iz * (L + 1) * (L + 1) << " " << (ix + 1) + iy * (L + 1) + iz * (L + 1) * (L + 1) << " " << (ix + 1) + iy * (L + 1) + (iz + 1) * (L + 1) * (L + 1) << " " << ix + iy * (L + 1) + (iz + 1) * (L + 1) * (L + 1) << std::endl;
				//1 0 0 planes
				myfile << 4 << " " << ix + iy * (L + 1) + iz * (L + 1) * (L + 1) << " " << ix + (iy + 1) * (L + 1) + iz * (L + 1) * (L + 1) << " " << ix + (iy + 1) * (L + 1) + (iz + 1) * (L + 1) * (L + 1) << " " << ix + iy * (L + 1) + (iz + 1) * (L + 1) * (L + 1) << std::endl;
			}
		}
	}

}