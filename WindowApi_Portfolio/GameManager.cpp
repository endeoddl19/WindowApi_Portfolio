#include "GameManager.h"

GameManager::GameManager()
{
	mapw = 0;
	maph = 0;
}

void GameManager::SetGame(RECT rt)
{
	// 나중에 for문으로 변경
	MapImage = Image::FromFile((WCHAR*)L"maps/test1.png");
	rect = rt;
	mapw = rt.right - rt.left;
	maph = (rt.bottom - rt.top) / (COL + 1) * COL;
	int i, j;
	/*OPENFILENAME OFN;
	HANDLE hFile;
	int point = 0;
	TCHAR info[128], lpstrFile[128] = L"maps/test1.txt";
	DWORD sizeT = 1000;

	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 256;
	OFN.lpstrInitialDir = L".";
	hFile = CreateFileW(lpstrFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);
	ReadFile(hFile, info, sizeT, &sizeT, NULL);
	for (i = 0; i < 8; ++i)
	{
		for (j = 0; j < 8; ++j)
			MapInfo[i][j] = info[point++] - '0';
	}
	CloseHandle(hFile);*/

	/*std::ifstream fin("maps/test1.txt", std::ios::in);

	int* score;

	for (i = 0; i < 8; ++i)
	{
		for (j = 0; j < 8; ++j)
			fin.read((char*)&MapInfo[i][j],sizeof(int));
	}

	fin.close();*/
}

void GameManager::Play(HWND hWnd, HDC hdc)
{
	HDC memDC;
	HBITMAP oldBit, newBit;
	int w = rect.right / ROW;
	int h = rect.bottom / (COL + 1);

	memDC = CreateCompatibleDC(hdc);

	newBit = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
	oldBit = (HBITMAP)SelectObject(memDC, newBit);

	Graphics* graphic = new Graphics(memDC);

	graphic->DrawImage(MapImage, 0, 0, mapw, maph);

	delete graphic;

	BitBlt(hdc, 0, 0, rect.right, rect.bottom, memDC, 0, 0, SRCCOPY);
	SelectObject(memDC, oldBit);
	DeleteObject(newBit);

	DeleteDC(memDC);
}
