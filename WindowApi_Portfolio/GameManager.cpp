#include "GameManager.h"

void GameManager::FindPath()
{
	ANode* a = NULL;
	//a->setMap();
	//a->AStar(respon.x, respon.y, destin.x, destin.y);
	cpath = a->getPath();
	//a->close();
}

void GameManager::DrawEnemy(HDC hdc, Graphics* graphic)
{
	POINT pt;
	Pen pen(Color(255, 0, 0));
	SolidBrush brush(Color(255, 255, 0, 0));
	for (int i = 0; i < enems.size(); i++)
	{
		pt = enems[i]->GetcurPos();
		graphic->DrawImage(EnemyImage, Rect(pt.x - mapw / ROW / 2, pt.y - maph / COL / 2,
			mapw / ROW, maph / COL),
			0, 0, 50, 50, Unit::UnitPixel);

		DrawHpBar(hdc, pt, enems[i]->GetHP());
	}
}

void GameManager::DrawHero(HDC hdc, Graphics* graphic)
{
	POINT pt;
	for (int i = 0; i < heros.size(); i++)
	{
		pt = heros[i]->GetcurPos();
		graphic->DrawImage(HeroImage[heros[i]->getHnum()],
			Rect(pt.x - mapw / ROW / 2, pt.y - maph / COL/ 2,
				mapw / ROW, maph / COL),
			0, 0, 200, 200, Unit::UnitPixel);
		DrawHpBar(hdc, pt, heros[i]->GetHP());
	}
	Rectangle(hdc, 0, maph, mapw, rect.bottom);
	for (int i = 0; i < 6; i++)
	{
		graphic->DrawImage(HeroImage[i],
			Rect(i * mapw / 6, maph, mapw / 6, maph / COL),
			0, 0, 200, 200, Unit::UnitPixel);
	}
}

void GameManager::DrawProj(HDC hdc, Graphics* graphic)
{
	int sz;
	POINT pt;
	for (int i = 0; i < projs.size(); i++)
	{
		pt = projs[i]->GetcurPos();
		sz = projs[i]->getSize();
		if (sz != 1)
			Ellipse(hdc, pt.x - sz, pt.y - sz, pt.x + sz, pt.y + sz);
	}
}

void GameManager::DrawHpBar(HDC hdc, POINT pt, FLOAT hp)
{
	int w = mapw / ROW / 2 * hp;
	Rectangle(hdc, pt.x - mapw / ROW / 4, pt.y - maph / (COL + 1) / 2 + 5, 
		pt.x - mapw / ROW / 4 + w, pt.y - maph / (COL + 1) / 2);
}

void GameManager::DrawRangeTile(Graphics* graphic)
{
	SolidBrush brush(Color(125, 255, 0, 0));
	SolidBrush brush2(Color(0, 255, 0, 0));

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (MapInfo[i][j] == 0)
				graphic->FillRectangle(&brush2, i * mapw / ROW, j * maph / COL,
					mapw / ROW, maph / COL);
			else
				graphic->FillRectangle(&brush, i * mapw / ROW, j * maph / COL,
					mapw / ROW, maph / COL);
		}
	}
}

void GameManager::DrawAdjTile(Graphics* graphic)
{
	SolidBrush brush(Color(125, 255, 0, 0));
	SolidBrush brush2(Color(0, 255, 0, 0));

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if(MapInfo[i][j] == 1)
				graphic->FillRectangle(&brush2, i * mapw / ROW, j * maph / COL,
					mapw / ROW, maph / COL);
			else
				graphic->FillRectangle(&brush, i * mapw / ROW, j * maph / COL,
					mapw / ROW, maph / COL);
		}
	}
}

void GameManager::DrawBuyableTile(Graphics* graphic)
{
	SolidBrush brush(Color(150, 70, 70, 70));
	for (int i = 0; i < 6; i++)
	{
		if (buyAble[i] == false)
			graphic->FillRectangle(&brush, i * mapw / 6, maph,
				mapw / 6, maph / COL);
	}
}

GameManager::GameManager()
{
	gs = { 40, 300, 10, 1 };
	mapw = 0;
	maph = 0;
}

void GameManager::SetGame(RECT rt)
{
	// 나중에 for문으로 변경
	MapImage = Image::FromFile((WCHAR*)L"maps/test1.png");
	EnemyImage = Image::FromFile((WCHAR*)L"images/Enemy1.png");
	HeroImage[0] = Image::FromFile((WCHAR*)L"images/Khan.png");
	HeroImage[1] = Image::FromFile((WCHAR*)L"images/Chandra.png");
	HeroImage[2] = Image::FromFile((WCHAR*)L"images/Meh.png");
	HeroImage[3] = Image::FromFile((WCHAR*)L"images/Guan.png");
	HeroImage[4] = Image::FromFile((WCHAR*)L"images/Alex.png");
	HeroImage[5] = Image::FromFile((WCHAR*)L"images/YSS.png");
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

	for (i = 0; i < cpath.size(); i++)
		MapInfo[cpath[i].x][cpath[i].y] = 1;

	for (i = 0; i < 6; i++)
	{
		if (cost[i] > gs.coin)
			buyAble[i] = false;
		else
			buyAble[i] = true;
	}
}

void GameManager::CreateEnemy()
{
	Enemy* e = new Enemy;
	POINT pt;
	pt = ut.ToMapPos(respon, mapw, maph);
	e->SetInitPos(pt);
	e->setPath(cpath);
	enems.push_back(e);
	charcs.push_back(e);
}

void GameManager::CreateHero(POINT pt, int hnum)
{
	Hero* h = new Hero(hnum);
	pt = ut.ToTilePos(pt, mapw, maph);
	MapInfo[pt.x][pt.y] = 2;
	pt = ut.ToMapPos(pt, mapw, maph);
	h->SetInitPos(pt);
	h->FindAtkDir(cpath, rect);
	h->setCost(cost[hnum]);
	heros.push_back(h);
	charcs.push_back(h);
	gs.coin -= cost[hnum];
}

BOOL GameManager::canCreate(POINT pt, int hnum)
{
	if (hnum > 3)
	{
		if (MapInfo[pt.x][pt.y] == 1)
			return true;
		else
			return false;
	}
	else
	{
		if(MapInfo[pt.x][pt.y] == 0)
			return true;
		else
			return false;
	}
}

void GameManager::Update()
{
	int i;
	for (i = 0; i < enems.size(); i++)
	{
		if (enems[i]->isArrive())
		{
			enems.erase(enems.begin());
			gs.life--;
		}
		enems[i]->Collision(heros);
		if (enems[i]->getState() == 1)
			enems[i]->Move(rect);
		else if (enems[i]->getState() == 2)
			Shoot(enems[i]);
		if (enems[i]->Death())
		{
			enems.erase(enems.begin() + i);
			gs.coin += 5;
		}
	}

	for (i = 0; i < projs.size(); i++)
	{
		projs[i]->Move(rect);
		projs[i]->Collision(enems);
		if (projs[i]->Death())
		{
			projs.erase(projs.begin() + i);
		}
	}

	for (i = 0; i < heros.size(); i++)
	{
		heros[i]->Target(enems, rect);
		if (heros[i]->getState() == 2)
			Shoot(heros[i]);
		if (heros[i]->Death())
		{
			heros.erase(heros.begin() + i);
		}
	}

	for (i = 0; i < 6; i++)
	{
		if (cost[i] > gs.coin)
			buyAble[i] = false;
		else
			buyAble[i] = true;
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
	DrawEnemy(memDC,graphic);
	DrawHero(memDC, graphic);
	DrawProj(memDC, graphic);
	DrawBuyableTile(graphic);
	if (state == 1)
		DrawRangeTile(graphic);
	else if(state == 2)
		DrawAdjTile(graphic);

	delete graphic;

	BitBlt(hdc, 0, 0, rect.right, rect.bottom, memDC, 0, 0, SRCCOPY);
	SelectObject(memDC, oldBit);
	DeleteObject(newBit);

	DeleteDC(memDC);
}

void GameManager::Shoot(Character* charac)
{
	POINT pt;
	if (charac->canShoot())
	{
		Projectile* p = new Projectile;
		pt = charac->GetcurPos();
		pt.x += charac->GetDir().x/ROW;
		pt.y += charac->GetDir().y/COL;
		p->setProj(pt, charac->GetDir(), charac->setProjSize(),
			charac->setProjDmg(), charac->getRange());
		projs.push_back(p);
	}
	
}

void GameManager::close()
{
	int i;
	for (i = 0; i < charcs.size(); i++)
		delete charcs[i];
	for (i = 0; i < enems.size(); i++)
		delete enems[i];
	for (i = 0; i < heros.size(); i++)
		delete heros[i];
	for (i = 0; i < projs.size(); i++)
		delete projs[i];
}
