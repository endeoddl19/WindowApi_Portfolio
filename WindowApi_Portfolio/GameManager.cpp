#include "GameManager.h"

void GameManager::FindPath()
{
	ANode* a = NULL;
	//a->setMap();
	//a->AStar(respon.x, respon.y, destin.x, destin.y);
	cpath = a->getPath();
	a->close();
}

void GameManager::DrawEnemy(HDC hdc)
{
	for (int i = 0; i < enems.size(); i++)
	{
		POINT pt = enems[i]->GetcurPos();
		Ellipse(hdc, pt.x - 20, pt.y - 20, pt.x + 20, pt.y + 20);
	}
}

void GameManager::DrawHero(HDC hdc)
{
	for (int i = 0; i < heros.size(); i++)
	{
		POINT pt = heros[i]->GetcurPos();
		Rectangle(hdc, pt.x - 20, pt.y - 20, pt.x + 20, pt.y + 20);
	}
}

GameManager::GameManager()
{
	mapw = 0;
	maph = 0;
	size = 20;
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

	/*for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (MapInfo[i][j] == 2)
				respon = { i,j };
			if (MapInfo[i][j] == 3)
				destin = { i,j };
		}
	}*/

	FindPath();
}

void GameManager::CreateEnemy()
{
	Enemy* e = new Enemy;
	POINT pt;
	pt.x = respon.x * rect.right / ROW + rect.right / ROW/2;
	pt.y = respon.y * rect.bottom / COL + rect.bottom / COL/2;
	e->SetInitPos(pt);
	e->setPath(cpath);
	enems.push_back(e);
	charcs.push_back(e);
}

void GameManager::CreateHero(POINT pt, int hnum)
{
	Hero* h = new Hero;
	h->SetInitPos(pt);
	h->setHero(hnum);
	heros.push_back(h);
	charcs.push_back(h);
}

void GameManager::Update()
{
	for (int i = 0; i < enems.size(); i++)
	{
		if (enems[i]->isArrive())
			enems.erase(enems.begin());
		else
			enems[i]->Move(rect);
	}
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
	DrawEnemy(memDC);
	DrawHero(memDC);

	delete graphic;

	BitBlt(hdc, 0, 0, rect.right, rect.bottom, memDC, 0, 0, SRCCOPY);
	SelectObject(memDC, oldBit);
	DeleteObject(newBit);

	DeleteDC(memDC);
}

void GameManager::Clear()
{
}