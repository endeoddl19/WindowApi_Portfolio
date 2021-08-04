#include "MapTool.h"

void MapTool::SetMapTool(RECT rt)
{
	imgs[0] = Image::FromFile((WCHAR*)L"images/green_sprites.png");
	imgs[1] = Image::FromFile((WCHAR*)L"images/snow_sprites.png");
	imgs[2] = Image::FromFile((WCHAR*)L"images/tower_sprites.png");
	imgs[3] = Image::FromFile((WCHAR*)L"images/background3.png");

	rect = rt;
	rtw = rt.right - rt.left;
	rth = rt.bottom - rt.top;
	mapw = rtw / 20 * 8;
	maph = mapw;
	mapx = rtw / 20;
	mapy = (rth - maph) / 2;
	sph = rth / 2;
	spw = sph;
	spx = rtw / 2 + rtw / 20;
	spy = rth / 10;
}

void MapTool::DrawSP(Graphics* graphic, int n)
{
	graphic->DrawImage(imgs[n], spx, spy, spw, sph);
}

void MapTool::Draw(HWND hWnd, HDC hdc,int n)
{
	HDC memDC;
	HBITMAP oldBit, newBit;
	TCHAR strTest[32];
	int sw = imgs[1]->GetWidth();
	int sh = imgs[1]->GetHeight();

	memDC = CreateCompatibleDC(hdc);

	newBit = CreateCompatibleBitmap(hdc, rtw, rth);
	oldBit = (HBITMAP)SelectObject(memDC, newBit);

	Graphics* graphic = new Graphics(memDC);

	DrawSP(graphic, n);
	DrawCurTile(graphic);
	//graphic->DrawImage(imgs[3], mapx, mapy, mapw, maph);
	
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			if (Map[i][j].spn != -1) 
			{
				graphic->DrawImage(imgs[Map[i][j].spn],
					mapx + i * mapw / ROW, mapy + j * maph / COL,
					Map[i][j].pt.x * sw / 7, Map[i][j].pt.y * sh / 7,
					sw / 7, sh / 7, Unit::UnitPixel);
			}
			else
			{
				_stprintf_s(strTest, _countof(strTest),
					_T("%d %d %d"), Map[i][j].spn, Map[i][j].pt.x, Map[i][j].pt.y);
				TextOut(hdc, mapx + i * mapw / ROW, mapy + j * maph / COL,
					strTest, _tcslen(strTest));
			}
		}
	}
	delete graphic;

	BitBlt(hdc, 0, 0, rect.right, rect.bottom, memDC, 0, 0, SRCCOPY);
	SelectObject(memDC, oldBit);
	DeleteObject(newBit);

	DeleteDC(memDC);
}

void MapTool::DrawCurTile(Graphics* graphic)
{
	int wh = spw / 7;
	Pen pen(Color(255, 0, 0));
	graphic->DrawRectangle(&pen, spx + curTile.x*wh, spy + curTile.y * wh, wh, wh);
}

void MapTool::SetTile(POINT pt)
{
	if (curTile.x == -10000)
		return;
	else
	{
		int i, j;
		int w = mapw / ROW;

		for (i = 0; i < ROW; ++i)
		{
			for (j = 0; j < COL; ++j)
			{
				if (pt.x > mapx + i * w && pt.x < mapx + (i + 1) * w &&
					pt.y > mapy + j * w && pt.y < mapy + (j + 1) * w)
					curPos = { i, j };
			}
		}
		Tile t;
		t.pt = curTile;
		t.spn = spnum;
		Map[curPos.x][curPos.y] = t;
	}
}

void MapTool::SelectTile(POINT pt, int n)
{
	spnum = n;

	int i, j;
	int w = spw / 7;
	for (i = 0; i < 7; ++i)
	{
		for (j = 0; j < 7; ++j)
		{
			if (pt.x > spx + i * w && pt.x < spx + (i + 1) * w &&
				pt.y > spy + j * w && pt.y < spy + (j + 1) * w)
			{
				curTile = { i, j};
				return;
			}
		}
	}
}


void MapTool::LoadMap()
{
}

void MapTool::SaveMap()
{
}

bool MapTool::posInMap(POINT pt)
{
	if (pt.x < mapx + mapw && pt.x >= mapx && pt.y < mapy + maph && pt.y >= mapy)
		return true;
	else
		return false;
}

bool MapTool::posInSp(POINT pt)
{
	if (pt.x < spx + spw && pt.x >= spx && pt.y < spy + sph && pt.y >= spy)
		return true;
	else
		return false;
}

MapTool::MapTool()
{
	curPos = { 0, 0 };
	curTile = { -10000, -10000 };
	rtw = 0;
	rth = 0;
	mapw =0;
	maph = 0;
	mapx = 0;
	mapy = 0;
	sph = 0;
	spw = 0;
	spx = 0;
	spy = 0;

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			Map[i][j].pt = { 0,0 };
			Map[i][j].spn = -1;
		}
	}
}