#pragma once
#include <math.h>
#define WORLDSIZE = 64;
struct CellSearch {
public:
	int xCoord, yCoord;
	int m_id;
	CellSearch * parent;
	float G;
	float H;

	CellSearch() : parent(0) {}
	CellSearch(int x, int y, CellSearch *parent = 0) : xCoord(x), yCoord(y), parent(parent), m_id(y * WORLDSIZE + x), G(0), H(0) {};
	float GetF() { return G + H; }
	float ManHattanDistance(CellSearch *nodeEnd) {
		float x = (float)(fabs(this->xCoord - nodeEnd->xCoord));
		float y = (float)(fabs(this->yCoord - nodeEnd->yCoord));

		return x + y;
	}

};