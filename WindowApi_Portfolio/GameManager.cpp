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
	int d;
	POINT pt, dir;
	Pen pen(Color(255, 0, 0));
	SolidBrush brush(Color(255, 255, 0, 0));
	for (int i = 0; i < enems.size(); i++)
	{
		pt = enems[i]->cs.curPos;
		dir = enems[i]->curDir;
		if (dir.x == 1)
			d = 1;
		else d = 0;
		if (enems[i]->cs.state == 1)
			graphic->DrawImage(EnemyImage[d], Rect(pt.x - mapw / ROW / 2, pt.y - maph / COL / 2,
				mapw / ROW, maph / COL),
				0, 0, 48, 48, Unit::UnitPixel);
		else if (enems[i]->cs.state == 2)
			graphic->DrawImage(EnemyImage[d + 2], Rect(pt.x - mapw / ROW / 2, pt.y - maph / COL / 2,
				mapw / ROW, maph / COL),
				enems[i]->getAtk() * 48, 0, 48, 48, Unit::UnitPixel);

		DrawHpBar(hdc, pt, enems[i]->GetHP());
	}
}

void GameManager::DrawHero(HDC hdc, Graphics* graphic)
{
	POINT pt;
	for (int i = 0; i < heros.size(); i++)
	{
		pt = heros[i]->cs.curPos;
		graphic->DrawImage(HeroImage[heros[i]->heronum],
			Rect(pt.x - mapw / ROW / 2, pt.y - maph / COL/ 2,
				mapw / ROW, maph / COL),
			0, 0, 200, 200, Unit::UnitPixel);
		DrawHpBar(hdc, pt, heros[i]->GetHP());
	}
	Rectangle(hdc, 0, maph, mapw, rect.bottom);
	for (int i = 0; i < 6; i++)
	{
		graphic->DrawImage(HeroBackImage[i],
			Rect(i * mapw / 6, maph, mapw / 6, rect.bottom/WCOL*2),
			0, 0, 200, 200, Unit::UnitPixel);
	}
}

void GameManager::DrawProj(HDC hdc, Graphics* graphic)
{
	int pnum;
	POINT pt;
	for (int i = 0; i < projs.size(); i++)
	{
		pt = projs[i];
		
	}
}

void GameManager::DrawHpBar(HDC hdc, POINT pt, FLOAT hp)
{
	int w = mapw / ROW / 2 * hp;
	Rectangle(hdc, pt.x - mapw / ROW / 4, pt.y - maph / (WCOL) / 2 + 5, 
		pt.x - mapw / ROW / 4 + w, pt.y - maph / (WCOL) / 2);
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
	SolidBrush brush(Color(150, 40, 40, 40));
	for (int i = 0; i < 6; i++)
	{
		if (buyAble[i] == false)
			graphic->FillRectangle(&brush, i * mapw / 6, maph,
				mapw / 6, rect.bottom / WCOL * 2 + 8);
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
	EnemyImage[0] = Image::FromFile((WCHAR*)L"images/EnemyLeft.png");
	EnemyImage[1] = Image::FromFile((WCHAR*)L"images/EnemyRight.png");
	EnemyImage[2] = Image::FromFile((WCHAR*)L"images/EnemyAtkLeft.png");
	EnemyImage[3] = Image::FromFile((WCHAR*)L"images/EnemyAtkRight.png");
	EnemyImage[4] = Image::FromFile((WCHAR*)L"images/EnemyDeadLeft.png");
	EnemyImage[5] = Image::FromFile((WCHAR*)L"images/EnemyDeadRight.png");
	HeroImage[0] = Image::FromFile((WCHAR*)L"images/Khan.png");
	HeroImage[1] = Image::FromFile((WCHAR*)L"images/Ram.png");
	HeroImage[2] = Image::FromFile((WCHAR*)L"images/Meh.png");
	HeroImage[3] = Image::FromFile((WCHAR*)L"images/Guan.png");
	HeroImage[4] = Image::FromFile((WCHAR*)L"images/Leo.png");
	HeroImage[5] = Image::FromFile((WCHAR*)L"images/YSS.png");
	HeroBackImage[0] = Image::FromFile((WCHAR*)L"images/Khan.png");
	HeroBackImage[1] = Image::FromFile((WCHAR*)L"images/Ram_Back.png");
	HeroBackImage[2] = Image::FromFile((WCHAR*)L"images/Meh_Back2.png");
	HeroBackImage[3] = Image::FromFile((WCHAR*)L"images/Guan.png");
	HeroBackImage[4] = Image::FromFile((WCHAR*)L"images/Leo_Back.png");
	HeroBackImage[5] = Image::FromFile((WCHAR*)L"images/YSS.png");
	rect = rt;
	mapw = rt.right - rt.left;
	maph = (rt.bottom - rt.top) / (WCOL) * COL;
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
	gs.wave--;
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

BOOL GameManager::CreatAble(POINT pt, int hnum)
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
			enems.erase(enems.begin() + i);
			gs.life--;
			if (gs.life == 0)
				system("exit");
		}
		else if (enems.size() > 0)
		{
			Collision();
			if (enems[i]->cs.state == 1)
				enems[i]->Move(rect);
			else if (enems[i]->cs.state == 2)
				ShootProj(enems[i]);
			if (enems[i]->cs.death)
			{
				enems.erase(enems.begin() + i);
				gs.coin += 10;
			}
		}
	}

	for (i = 0; i < heros.size(); i++)
	{
		heros[i]->Target(enems, rect);
		if (heros[i]->cs.state == 2)
			ShootProj(heros[i]);
		if (heros[i]->cs.death)
		{
			heros.erase(heros.begin() + i);
		}
	}

	for (i = 0; i < projs.size(); i++)
	{
		projs[i]->Move(rect);
		if (projs[i]->cs.death)
		{
			projs.erase(projs.begin() + i);
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
	int h = rect.bottom / (WCOL);

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

void GameManager::ShootProj(Hero* hero)
{
	POINT pt;
	if (hero->AttackAble())
	{
		Projectile* p = new Projectile;
		pt = hero->cs.curPos;
		p->setProj(pt, hero->GetDir(), hero->getRange());
		projs.push_back(p);
	}
}

void GameManager::Collision()
{
	POINT pt;
	for (int i = 0; i < enems.size(); i++)
	{
		pt = enems[i]->moving;
		if (MapInfo[pt.x][pt.y] == 1 && enems[i]->GetcurPos().x)
		{
			enems[i]->state = 2;
			if (enems[i]->AttackAble())
			{
				for (int j = 0; j < heros.size(); j++)
				{
					if (heros[i]->curPos.x == pt.x && heros[i]->curPos.y == pt.y)
						if (enems[i]->AttackAble())
							heros[i]->Damaged(enems[i]->dmg)
				}
			}
		}

		else
			enems[i]->state = 1;
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