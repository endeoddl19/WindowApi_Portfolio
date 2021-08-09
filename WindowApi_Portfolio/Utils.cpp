#include "Utils.h"

POINT Utils::ToTilePos(POINT pt, int mapw, int maph)
{
	POINT pos = { -1,-1 };
	int i, j;
	int w = mapw / ROW;
	int h = maph / COL + 1;

	for (i = 0; i < ROW; ++i)
	{
		for (j = 0; j < COL; ++j)
		{
			if (pt.x > i * w && pt.x < (i + 1) * w &&
				pt.y > j * h && pt.y < (j + 1) * h)
				pos = { i, j };
		}
	}
	return pos;
}

POINT Utils::ToMapPos(POINT pt, int mapw, int maph)
{
	POINT pos;
	pos.x = pt.x * mapw / ROW + mapw / ROW / 2;
	pos.y = pt.y * maph / COL + maph / COL / 2;
	return pos;
}
