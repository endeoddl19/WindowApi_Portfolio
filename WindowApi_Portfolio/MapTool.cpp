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

void MapTool::DrawSP(HDC hdc, int n)
{
	Graphics* graphic = new Graphics(hdc);
	graphic->DrawImage(imgs[n], spx, spy, spw, sph);
	delete graphic;
}

void MapTool::Draw(HWND hWnd, HDC hdc,int n)
{
	HDC memDC;
	HBITMAP oldBit, newBit;
	Pen pen(Color(255, 255, 0, 0));
	TCHAR strTest[32];
	int sw = imgs[1]->GetWidth();
	int sh = imgs[1]->GetHeight();

	memDC = CreateCompatibleDC(hdc);

	newBit = CreateCompatibleBitmap(hdc, rtw, rth);
	oldBit = (HBITMAP)SelectObject(memDC, newBit);

	Graphics* graphic = new Graphics(memDC);

	DrawSP(memDC, n);
	DrawCurTile(graphic);
	graphic->DrawRectangle(&pen, mapx, mapy, mapw, maph);
	
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
	Pen pen(Color(255, 0, 0), 3);
	graphic->DrawRectangle(&pen, spx + curTile.x * wh, spy + curTile.y * wh, wh, wh);
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
		t.index = 1;
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


void MapTool::LoadMap(HWND hWnd, OPENFILENAME OFN)
{
	HANDLE hFile;
	int point = 0;

	memset(&OFN, 0, sizeof(OPENFILENAME)); 
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = hWnd;
	OFN.lpstrFilter = filter;
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 256;
	OFN.lpstrInitialDir = L"."; 
	if (GetOpenFileName(&OFN) != 0) {
		wsprintf(str, L"%s 파일을 여시겠습니까 ?", OFN.lpstrFile);
		MessageBox(hWnd, str, L"열기 선택", MB_OK);
	}
	hFile = CreateFileW(lpstrFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);
	ReadFile(hFile, info, sizeT, &sizeT, NULL);
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
			Map[i][j].index = info[point++] - '0';
	}
	CloseHandle(hFile);
}

void MapTool::SaveMap(HWND hWnd, OPENFILENAME OFN, OPENFILENAME SFN)
{
	HANDLE hFile;
	WORD wd = 0xFEFF;
	int point = 0;

	memset(&OFN, 0, sizeof(OPENFILENAME));  
	SFN.lStructSize = sizeof(OPENFILENAME);
	SFN.hwndOwner = hWnd;
	SFN.lpstrFilter = filter;
	SFN.lpstrFile = lpstrFile;
	SFN.nMaxFile = 256;
	SFN.lpstrInitialDir = L".";
	if (GetSaveFileName(&SFN) != 0) {
		wsprintf(str, L"%s 파일에 저장하시겠습니까 ?", SFN.lpstrFile);
		MessageBox(hWnd, str, L"저장하기 선택", MB_OK);
	}
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
			info[point++] = Map[i][j].index - '0';
	}
	hFile = CreateFileW(lpstrFile, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, 0);
	
	SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
	WriteFile(hFile, info, 2 * lstrlen(info), &c, NULL);
	CloseHandle(hFile);
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
	spnum = 0;

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			Map[i][j].pt = { 0,0 };
			Map[i][j].spn = -1;
			Map[i][j].index = 0;
		}
	}
}