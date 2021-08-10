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
		graphic->DrawEllipse(&pen, pt.x - SIZE, pt.y - SIZE, SIZE * 2, SIZE * 2);
		graphic->FillEllipse(&brush, pt.x - SIZE, pt.y - SIZE, SIZE * 2, SIZE * 2);
		graphic->DrawRectangle(&pen, pt.x - SIZE, pt.y - SIZE - 8,
			(int)(SIZE * 2 * enems[i]->GetHP()), 3);
		graphic->FillRectangle(&brush, pt.x - SIZE, pt.y - SIZE - 8,
			(int)(SIZE * 2 * enems[i]->GetHP()), 3);
	}
}

void GameManager::DrawHero(HDC hdc, Graphics* graphic)
{
	int type;
	POINT pt;
	Pen pen(Color(0, 0, 255));
	Pen pen2(Color(0, 0, 0));
	SolidBrush brush(Color(255, 0, 0, 255));
	SolidBrush brush2(Color(255, 0, 0, 0));
	for (int i = 0; i < heros.size(); i++)
	{
		pt = heros[i]->GetcurPos();
		type = heros[i]->getHnum();
		switch (type)
		{
		case 1:
			graphic->DrawRectangle(&pen, pt.x - SIZE, pt.y - SIZE, SIZE * 2, SIZE * 2);
			graphic->FillRectangle(&brush, pt.x - SIZE, pt.y - SIZE, SIZE * 2, SIZE * 2);
			break;
		case 2:
			graphic->DrawRectangle(&pen2, pt.x - SIZE, pt.y - SIZE, SIZE * 2, SIZE * 2);
			graphic->FillRectangle(&brush2, pt.x - SIZE, pt.y - SIZE, SIZE * 2, SIZE * 2);
			break;
		}
		graphic->DrawRectangle(&pen, pt.x - SIZE, pt.y - SIZE - 8,
			(int)(SIZE * 2 * heros[i]->GetHP()), 3);
		graphic->FillRectangle(&brush, pt.x - SIZE, pt.y - SIZE - 8,
			(int)(SIZE * 2 * heros[i]->GetHP()), 3);
		/*pt.x += size * heros[i]->GetDir().x;
		pt.y += size * heros[i]->GetDir().y;
		graphic->DrawEllipse(&pen2, pt.x - size - 3, pt.y - size - 3, 6, 6);
		graphic->FillEllipse(&brush2, pt.x - size - 3, pt.y - size - 3, 6, 6);*/
	}
}

void GameManager::DrawProj(HDC hdc, Graphics* graphic)
{
	int sz;
	POINT pt, d;
	Point poly[3];
	Pen pen(Color(0, 0, 0));
	for (int i = 0; i < projs.size(); i++)
	{
		pt = projs[i]->GetcurPos();
		d = projs[i]->GetDir();
		sz = projs[i]->getSize();
		if (d.y == 0)
		{
			poly[0] = { pt.x + sz * d.x,pt.y};
			poly[1] = { pt.x - sz * d.x,pt.y + sz };
			poly[2] = { pt.x - sz * d.x,pt.y - sz };
		}
		else
		{
			poly[0] = { pt.x,pt.y + sz * d.y };
			poly[1] = { pt.x + sz ,pt.y - sz * d.y};
			poly[2] = { pt.x - sz ,pt.y - sz * d.y};
		}
		graphic->DrawPolygon(&pen, poly, 3);
	}
}

GameManager::GameManager()
{
	mapw = 0;
	maph = 0;
}

GameStatus GameManager::SetGame(RECT rt)
{
	// 나중에 for문으로 변경
	MapImage = Image::FromFile((WCHAR*)L"maps/test1.png");
	rect = rt;
	mapw = rt.right - rt.left;
	maph = (rt.bottom - rt.top) / (COL + 1) * COL;
	//int i, j;
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
	return gs;
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
	pt = ut.ToMapPos(pt, mapw, maph);
	h->SetInitPos(pt);
	h->FindAtkDir(cpath, rect);
	h->setCost(cost[hnum]);
	heros.push_back(h);
	charcs.push_back(h);
}

void GameManager::Update()
{
	for (int i = 0; i < enems.size(); i++)
	{
		if (enems[i]->isArrive())
			enems.erase(enems.begin());
		else if (enems[i]->getState() == 1)
			enems[i]->Move(rect);
		/*else if (enems[i]->getState() == 2)
			continue;*/
		if (enems[i]->Death())
		{
			enems.erase(enems.begin() + i);
		}
	}

	for (int i = 0; i < projs.size(); i++)
	{
		projs[i]->Move(rect);
		projs[i]->Collision(enems);
		if (projs[i]->Death())
		{
			projs.erase(projs.begin() + i);
		}
	}

	for (int i = 0; i < heros.size(); i++)
	{
		heros[i]->HasTarget(enems);
		if (heros[i]->getState() == 2)
			Shoot(heros[i]);
		if (heros[i]->Death())
		{
			heros.erase(heros.begin() + i);
		}
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

	delete graphic;

	BitBlt(hdc, 0, 0, rect.right, rect.bottom, memDC, 0, 0, SRCCOPY);
	SelectObject(memDC, oldBit);
	DeleteObject(newBit);

	DeleteDC(memDC);
}

void GameManager::Shoot(Hero* hero)
{
	POINT pt;
	if (hero->canShoot())
	{
		Projectile* p = new Projectile;
		pt = hero->GetcurPos();
		pt.x += SIZE * hero->GetDir().x;
		pt.y += SIZE * hero->GetDir().y;
		p->SetInitPos(pt);
		p->setDir(hero->GetDir());
		p->setSize(hero->setProjSize());
		p->setDmg(hero->setProjDmg());
		projs.push_back(p);
	}
	
}

BOOL GameManager::Purchase(int hnum)
{
	if ( cost[hnum] > gs.coin)
		return false;
	else
		return true;
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
