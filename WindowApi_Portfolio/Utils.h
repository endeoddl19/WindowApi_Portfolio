#pragma once

#ifndef _UTILS_H_
#define _UTILS_H_

#include "framework.h"

class Utils
{
public:
	POINT ToTilePos(POINT pt, int mapw, int maph);
	POINT ToMapPos(POINT pt, int mapw, int maph);
	BOOL inCircleRange(POINT pt1, POINT pt2, int sz);
	BOOL inRectRange(POINT pt1, POINT pt2, int sz);
};

#endif