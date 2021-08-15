#define _CRT_SECURE_NO_WARNINGS
#include "Astar.h"
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
#define MAX 20481024

int xdir[4] = { 0,1,0,-1 };
int ydir[4] = { 1,0,-1,0 };
ANode* map[8][8];

int getH(int x, int y, int dx, int dy)
{
	int h;
	int xdis = abs(dx - x);
	int ydis = abs(dy - y);
	h = 10 * (xdis + ydis);
	return h;
}

void ANode::setMap()
{
	int i, j;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			ANode* t = new ANode(i, j);
			map[i][j] = t;
		}
	}

	HANDLE hFile;
	TCHAR inBuff[128];
	DWORD size = 0;
	int pt = 0;

	hFile = CreateFile(_T("maps/test1.txt"), GENERIC_READ, FILE_SHARE_READ, NULL, CREATE_ALWAYS, 0, 0);
	memset(inBuff, 0, sizeof(inBuff));
	ReadFile(hFile, inBuff, 127 * sizeof(TCHAR), &size, NULL);
	CloseHandle(hFile);

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
			map[i][j]->val = (int)inBuff[pt++];
	}
}

void ANode::AStar(int sx, int sy, int dx, int dy)
{
	int x = sx;
	int y = sy;
	int min = MAX;
	POINT pt = { -1,-1 };

	while (pt.x != dx && pt.y != dy)
	{
		for (int i = 0; i < 4; i++)
		{
			x = sx;
			y = sy;
			x += xdir[i];
			y += ydir[i];
			if (x >= 0 && y >= 0)
			{
				map[x][y]->g += 10;
				map[x][y]->h = getH(x, y, dx, dy);
				map[x][y]->f = map[x][y]->g + map[x][y]->h;
				if (map[x][y]->f < min && map[x][y]->val != 0)
				{
					min = map[x][y]->f;
					pt = { x,y };
				}
			}
		}
		map[pt.x][pt.y]->open = true;
		sx = pt.x;
		sy = pt.y;
	}
}

vector<POINT> ANode::getPath()
{
	vector<POINT> path;
	/*int i, j;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (map[i][j]->val != 0)
				path->push_back({ i,j });
		}
	}*/
	path.push_back({ 1,0 });
	path.push_back({ 2,0 });
	path.push_back({ 3,0 });
	path.push_back({ 4,0 });
	path.push_back({ 5,0 });
	path.push_back({ 6,0 });
	path.push_back({ 7,1 });
	path.push_back({ 6,2 });
	path.push_back({ 5,2 });
	path.push_back({ 4,3 });
	path.push_back({ 3,3 });
	path.push_back({ 2,4 });
	path.push_back({ 1,5 });
	path.push_back({ 1,6 });
	path.push_back({ 1,7 });
	path.push_back({ 2,6 });
	path.push_back({ 3,6 });
	path.push_back({ 4,6 });
	path.push_back({ 5,5 });
	path.push_back({ 6,6 });
	path.push_back({ 7,6 });

	return path;
}

void ANode::close()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			delete map[i][j];
	}
}

