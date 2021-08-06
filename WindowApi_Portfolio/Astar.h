#pragma once
#include "framework.h"
#include <vector>
using std::vector;

class ANode
{
private:
	POINT p;
	int val = 0;
	int g = 0, h = 0, f = 0;
	bool open = false;
public:
	ANode(int _x, int _y)
	{
		p.x = _x; p.y = _y; g = 0; h = 0; f = 0;
	}

	void setMap();
	void AStar(int sx, int sy, int dx, int dy);
	vector<POINT> getPath();
	void close();
};