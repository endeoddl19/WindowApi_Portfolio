#include "GameManager.h"

void GameManager::FindPath()
{
	ANode* a = NULL;
	//a->setMap();
	//a->AStar(respon.x, respon.y, destin.x, destin.y);
	cpath = a->getPath();
	//a->close();
}

void GameManager::setImages()
{
	Title = Image::FromFile((WCHAR*)L"images/Title.png");
	MainMenu = Image::FromFile((WCHAR*)L"images/MainBackground.png");
	PlayPause = Image::FromFile((WCHAR*)L"images/playpause.png");
	GameInfo[0] = Image::FromFile((WCHAR*)L"images/GameInfo.png");
	GameInfo[1] = Image::FromFile((WCHAR*)L"images/GameInfo2.png");
	MapImage = Image::FromFile((WCHAR*)L"maps/back2_2.png");
	EnemyImage[0] = Image::FromFile((WCHAR*)L"images/EnemyLeft.png");
	EnemyImage[1] = Image::FromFile((WCHAR*)L"images/EnemyRight.png");
	EnemyImage[2] = Image::FromFile((WCHAR*)L"images/EnemyAtkLeft.png");
	EnemyImage[3] = Image::FromFile((WCHAR*)L"images/EnemyAtkRight.png");
	EnemyImage[4] = Image::FromFile((WCHAR*)L"images/EnemyDeadLeft.png");
	EnemyImage[5] = Image::FromFile((WCHAR*)L"images/EnemyDeadRight.png");
	HeroPixel = Image::FromFile((WCHAR*)L"images/Heros_p.png");
	HeroIcon = Image::FromFile((WCHAR*)L"images/Heros_icon.png");
	HeroImage = Image::FromFile((WCHAR*)L"images/Heros_img.png");
	HeroName = Image::FromFile((WCHAR*)L"images/Heros_name.png");
	HeroText = Image::FromFile((WCHAR*)L"images/Heros_info.png");
	ProjImage[0] = Image::FromFile((WCHAR*)L"images/speer.png");
	ProjImage[1] = Image::FromFile((WCHAR*)L"images/speer.png");
	ProjImage[2] = Image::FromFile((WCHAR*)L"images/canon.png");
	ProjImage[3] = Image::FromFile((WCHAR*)L"images/speer.png");
	ProjImage[4] = Image::FromFile((WCHAR*)L"images/speer.png");
	ProjImage[5] = Image::FromFile((WCHAR*)L"images/speer.png");
	Coin = Image::FromFile((WCHAR*)L"images/coin.png");
	CoinText = Image::FromFile((WCHAR*)L"images/coin_text.png");
}

void GameManager::DrawEnemy(HDC hdc, Graphics* graphic)
{
	int d;
	POINT pt, dir;
	Pen pen(Color(255, 0, 0));
	SolidBrush brush(Color(125, 255, 0, 0));
	for (int i = 0; i < enems.size(); i++)
	{
		pt = enems[i]->cs.curPos;
		dir = enems[i]->curDir;
		if (dir.x == -1) d = 0;
		else d = 1;
		if (enems[i]->cs.state == 1 || enems[i]->cs.state == 3)
		{
			graphic->DrawImage(EnemyImage[d],
				Rect(pt.x - mapw / ROW / 2, pt.y - maph / COL / 2,
					mapw / ROW, maph / COL),
				0, 0, 48, 48, Unit::UnitPixel);
			if (enems[i]->cs.state == 3)
				graphic->FillEllipse(&brush, INT(pt.x-20), INT(pt.y-20), 40, 40);
		}
		else if (enems[i]->cs.state == 2)
			graphic->DrawImage(EnemyImage[d+2], 
				Rect(pt.x - mapw / ROW / 2, pt.y - maph / COL / 2,
				mapw / ROW, maph / COL),
				(int)ch.getAtk(enems[i]) * 48, 0, 
				48, 48, Unit::UnitPixel);
				
		DrawHpBar(hdc, pt, ch.GetHP(enems[i]));
	}
}

void GameManager::DrawHero(HDC hdc, Graphics* graphic)
{
	POINT pt;
	for (int i = 0; i < heros.size(); i++)
	{
		pt = heros[i]->cs.curPos;
		graphic->DrawImage(HeroPixel,
			Rect(pt.x - mapw / ROW / 2, pt.y - maph / COL/ 2,
				mapw / ROW, maph / COL),
			heros[i]->heronum * 64, 0, 64, 64, Unit::UnitPixel);
		DrawHpBar(hdc, pt,ch.GetHP(heros[i]));
		if (heros[i]->cs.state == 2)
			graphic->DrawImage(ProjImage[heros[i]->heronum], 
				Rect(pt.x - mapw / ROW / 2, pt.y - maph / COL / 2,
				mapw / ROW, maph / COL),
				(int)ch.getAtk(heros[i]) * 32, 0, 32, 32, Unit::UnitPixel);
	}
	for (int i = 0; i < 6; i++)
	{
		graphic->DrawImage(HeroIcon,
			Rect(i * rect.right / WCOL + rect.right * 4 / WCOL,
				mapy + maph + rect.bottom * 2 / WCOL / 5, 
				rect.right / WCOL, rect.bottom * 8 / WCOL / 5),
			i * 100, 0, 100, 100, Unit::UnitPixel);
	}
}

void GameManager::DrawHpBar(HDC hdc, POINT pt, FLOAT hp)
{
	int w = mapw / ROW / 2 * hp;
	Rectangle(hdc, pt.x - mapw / ROW / 4,pt.y + maph / COL / 2,
		pt.x - mapw / ROW / 4 + w, pt.y + maph / COL / 2 + 4);
}

void GameManager::RangeSelected(Graphics* graphic)
{
	Pen pen(Color(255, 255, 0, 0), 3);
	SolidBrush brush(Color(125, 255, 0, 0));
	SolidBrush brush2(Color(0, 0, 0, 0));
	graphic->DrawRectangle(&pen, mapx, mapy,
		mapw, maph);

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (MapInfo[i][j] == 0)
				graphic->FillRectangle(&brush2, mapx + i * mapw / ROW, mapy + j * maph / COL,
					mapw / ROW, maph / COL);
			else
				graphic->FillRectangle(&brush, mapx + i * mapw / ROW, mapy + j * maph / COL,
					mapw / ROW, maph / COL);
		}
	}
}

void GameManager::AdjSelected(Graphics* graphic)
{
	Pen pen(Color(255, 255, 0, 0),3);
	SolidBrush brush(Color(125, 255, 0, 0));
	SolidBrush brush2(Color(0, 0, 0, 0));
	graphic->DrawRectangle(&pen, mapx, mapy,
		mapw, maph);

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if(MapInfo[i][j] == 1)
				graphic->FillRectangle(&brush2, mapx + i * mapw / ROW, mapy + j * maph / COL,
					mapw / ROW, maph / COL);
			else
				graphic->FillRectangle(&brush, mapx + i * mapw / ROW, mapy + j * maph / COL,
					mapw / ROW, maph / COL);
		}
	}
}

void GameManager::DrawBuyableTile(Graphics* graphic)
{
	SolidBrush brush(Color(170, 30, 30, 30));
	for (int i = 0; i < 6; i++)
	{
		if (buyAble[i] == false)
			graphic->FillRectangle(&brush, i * rect.right / WCOL + rect.right * 4 / WCOL
				, mapy + maph, rect.right / WCOL, rect.bottom / WCOL * 2 + 8);
	}
}

void GameManager::DrawHeroInfo(HDC hdc, Graphics* graphic)
{
	int arr[6] = { 266, 386, 327, 253, 352, 325 };
	int s = 0;
	for (int i = 0; i < hnum; i++)
		s += arr[i];
	SolidBrush brush1(Color(170, 30, 30, 30));
	SolidBrush brush2(Color(220, 198, 0, 0));
	SolidBrush brush3(Color(220, 255, 89, 30));
	SolidBrush brush4(Color(220, 255, 148, 30));
	SolidBrush brush5(Color(220, 255, 231, 30));

	graphic->FillRectangle(&brush1, mapx + mapw, rect.bottom * 2 / WCOL,
		rect.right * 2 / WCOL, rect.bottom * 6 / WCOL);

	graphic->DrawImage(HeroName, Rect(5 + mapx + mapw, rect.bottom * 5 / WCOL / 2,
		rect.right * 2 / WCOL - 10, rect.bottom / WCOL),
		s, 0, arr[hnum], 58, Unit::UnitPixel);

	graphic->DrawImage(HeroImage, Rect(mapx + mapw, rect.bottom * 7 / WCOL / 2,
		rect.right * 2 / WCOL, rect.bottom * 2 / WCOL),
		hnum * 200, 0, 200, 200, Unit::UnitPixel);

	graphic->DrawImage(HeroText, Rect(mapx + mapw, rect.bottom * 11 / WCOL / 2,
		rect.right * 2 / WCOL / 3, rect.bottom * 5 / WCOL / 2),
		0, 0, 364, 480, Unit::UnitPixel);

	graphic->FillRectangle(&brush2, INT(5 +mapx + mapw + rect.right * 2 / WCOL / 3), INT(rect.bottom * 11 / WCOL / 2 + 2),
		INT(rect.right * 4 / WCOL / 3 * HeroInfo[hnum]->cs.hp / 350), INT(rect.bottom * 5 / WCOL / 8 - 5));
	graphic->FillRectangle(&brush3, INT(5 + mapx + mapw + rect.right * 2 / WCOL / 3), INT(rect.bottom * 49 / WCOL / 8 + 2),
		INT(rect.right * 4 / WCOL / 3 * HeroInfo[hnum]->cs.dmg / 40), INT(rect.bottom * 5 / WCOL / 8 - 5));
	graphic->FillRectangle(&brush4, INT(5 + mapx + mapw + rect.right * 2 / WCOL / 3), INT(rect.bottom * 27 / WCOL / 4 + 2),
		INT(rect.right * 4 / WCOL / 3 * (90 - HeroInfo[hnum]->cs.atkspd) / 90), INT(rect.bottom * 5 / WCOL / 8 - 5));
	graphic->FillRectangle(&brush5, INT(5 + mapx + mapw + rect.right * 2 / WCOL / 3), INT(rect.bottom * 59 / WCOL / 8 + 2),
		INT(rect.right * 4 / WCOL / 3 * HeroInfo[hnum]->cs.range * ROW / mapw / 3), INT(rect.bottom * 5 / WCOL / 8 - 5));
}

void GameManager::DrawGameInfo(Graphics* graphic)
{
	graphic->DrawImage(GameInfo[1],
		Rect(10, rect.bottom * 3 / WCOL, rect.right / WCOL - 20, rect.bottom * 4 / WCOL),
		0, 0, 59, 437, Unit::UnitPixel);
	graphic->DrawImage(GameInfo[0],
		Rect(rect.right * 3 / WCOL / 2, rect.bottom / WCOL / 4, rect.right * 2 / WCOL, rect.bottom / WCOL ),
		0, 0, 387, 160, Unit::UnitPixel);
	graphic->DrawImage(GameInfo[0],
		Rect(rect.right * 21 / WCOL / 4, rect.bottom / WCOL / 4, rect.right * 2 / WCOL, rect.bottom / WCOL ),
		387, 0, 340, 160, Unit::UnitPixel);
	int s = state;
	if (s > 1) s = 1;
	graphic->DrawImage(PlayPause,
		Rect(rect.right * 19 / WCOL / 2 - 20, 20, rect.right / WCOL / 2, rect.bottom / WCOL / 2),
		s * 256, 0, 256, 256, Unit::UnitPixel);
}

void GameManager::DrawCoin(Graphics* graphic)
{
	int arr[10] = { 73, 60, 64, 64, 71, 65, 69, 63, 71, 69 };
	int a1, a2, s1 = 0, s2 = 0, i, j;

	graphic->DrawImage(Coin,
		Rect(rect.right * 2 / WCOL, mapy + maph + rect.bottom / WCOL / 2,
			rect.right / WCOL, rect.bottom / WCOL),
		0, 0, 200, 200, Unit::UnitPixel);
	
	for (i = 0; i < 6; i++) // 영웅 가격
	{
		graphic->DrawImage(Coin,
			Rect(i * rect.right / WCOL + rect.right * 4 / WCOL + rect.right / WCOL / 6,
				mapy + maph + 10, rect.right / WCOL / 6, rect.bottom * 2 / WCOL / 5),
			0, 0, 200, 200, Unit::UnitPixel);

		s1 = s2 = 0;
		for (j = 0; j < pcost[3 * i]; j++)
			s1 += arr[j];
		for (j = 0; j < pcost[3 * i + 1]; j++)
			s2 += arr[j];

		graphic->DrawImage(CoinText,
			Rect(i * rect.right / WCOL + rect.right * 4 / WCOL + rect.right / WCOL / 3,
				mapy + maph + 10, rect.right / WCOL / 6, rect.bottom * 2 / WCOL / 5),
			s1, 0, arr[pcost[3*i]], 120, Unit::UnitPixel);
		graphic->DrawImage(CoinText,
			Rect(i * rect.right / WCOL + rect.right * 4 / WCOL + rect.right / WCOL / 2,
				mapy + maph + 10, rect.right / WCOL / 6, rect.bottom * 2 / WCOL / 5),
			s2, 0, arr[pcost[1 + 3 * i]], 120, Unit::UnitPixel);
		graphic->DrawImage(CoinText,
			Rect(i * rect.right / WCOL + rect.right * 4 / WCOL + rect.right / WCOL * 2 / 3,
				mapy + maph + 10, rect.right / WCOL / 6, rect.bottom * 2 / WCOL / 5),
			0, 0, 73, 120, Unit::UnitPixel);
			
	}

	// 전체 코인
	s1 = s2 = 0; 
	a1 = gs.coin / 100;
	for (i = 0; i < a1; i++)
		s1 += arr[i];
	a2 = gs.coin / 10;
	a2 -= a1 * 10;
	for (i = 0; i < a2; i++)
		s2 += arr[i];

	graphic->DrawImage(CoinText,
		Rect(rect.right * 3 / WCOL, mapy + maph + rect.bottom / WCOL / 2,
			rect.right / WCOL / 3, rect.bottom / WCOL),
		s1, 0, arr[a1], 120, Unit::UnitPixel);
	graphic->DrawImage(CoinText,
		Rect(rect.right * 3 / WCOL + rect.right / WCOL / 3, mapy + maph + rect.bottom / WCOL / 2,
			rect.right / WCOL / 3, rect.bottom / WCOL),
		s2, 0, arr[a2], 120, Unit::UnitPixel);
	graphic->DrawImage(CoinText,
		Rect(rect.right * 3 / WCOL + rect.right * 2 / WCOL / 3, mapy + maph + rect.bottom / WCOL / 2,
			rect.right / WCOL / 3, rect.bottom / WCOL),
		0, 0, 73, 120, Unit::UnitPixel);

	// wave, life
	s1 = s2 = 0;
	a1 = gs.wave / 10;
	for (i = 0; i < a1; i++)
		s1 += arr[i];
	a2 = gs.wave - a1 * 10;
	for (i = 0; i < a2; i++)
		s2 += arr[i];

	graphic->DrawImage(CoinText,
		Rect(rect.right * 15 / WCOL / 4, rect.bottom / WCOL / 4, rect.right / WCOL / 2, rect.bottom / WCOL),
		s1, 0, arr[a1], 120, Unit::UnitPixel);
	graphic->DrawImage(CoinText,
		Rect(rect.right * 17 / WCOL / 4, rect.bottom / WCOL / 4, rect.right / WCOL / 2, rect.bottom / WCOL),
		s2, 0, arr[a2], 120, Unit::UnitPixel);

	s1 = s2 = 0;
	a1 = gs.life / 10;
	for (i = 0; i < a1; i++)
		s1 += arr[i];
	a2 = gs.life - a1 * 10;
	for (i = 0; i < a2; i++)
		s2 += arr[i];

	graphic->DrawImage(CoinText,
		Rect(rect.right * 15 / WCOL / 2, rect.bottom / WCOL / 4, rect.right / WCOL / 2, rect.bottom / WCOL),
		s1, 0, arr[a1], 120, Unit::UnitPixel);
	graphic->DrawImage(CoinText,
		Rect(rect.right * 8 / WCOL, rect.bottom / WCOL / 4, rect.right / WCOL / 2, rect.bottom / WCOL),
		s2, 0, arr[a2], 120, Unit::UnitPixel);
}

GameManager::GameManager()
{
	gs = { 40, 300, 10, 1 };
	mapw = 0;
	maph = 0;
}

void GameManager::SetGame(RECT rt)
{
	setImages();
	
	rect = rt;
	mapw = (rt.right - rt.left) * 7 / WCOL;
	maph = (rt.bottom - rt.top) * 6 / WCOL;
	mapx = rt.right / WCOL;
	mapy = rt.bottom * 2 / WCOL;
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

	Stats[0] = { {0,0},{0,0},100,100,15,20,(FLOAT)(mapw / ROW * 2),1,0,false };
	Stats[1] = { {0,0},{0,0},100,100,30,40,(FLOAT)(mapw / ROW * 3),1,0,false };
	Stats[2] = { {0,0},{0,0},100,100,40,70,(FLOAT)(mapw / ROW * 3),1,0,false };
	Stats[3] = { {0,0},{0,0},200,200,25,40,(FLOAT)(mapw / ROW),1,0,false };
	Stats[4] = { {0,0},{0,0},400,400,15,65,(FLOAT)(mapw / ROW),1,0,false };
	Stats[5] = { {0,0},{0,0},250,250,40,80,(FLOAT)(mapw / ROW),1,0,false };
	Stats[6] =  {{0,0},{0,0},130,130,30,50,(FLOAT)(mapw / ROW / 2),1,1,false};
	
	for (i = 0; i < 6; i++)
	{
		Hero* h = new Hero;
		h->cs = Stats[i];
		h->cost = cost[i];
		h->heronum = i;
		HeroInfo.push_back(h);
	}

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

void GameManager::DrawMain(HDC hdc)
{
	HDC memDC;
	HBITMAP oldBit, newBit;
	static int cnt=1;

	memDC = CreateCompatibleDC(hdc);

	newBit = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
	oldBit = (HBITMAP)SelectObject(memDC, newBit);

	Graphics* graphic = new Graphics(memDC);

	graphic->DrawImage(MainMenu, 0, 0, rect.right, rect.bottom);
	graphic->DrawImage(Title,
		Rect(rect.right * 2 / WCOL, rect.bottom * 2 / WCOL, rect.right * 6 / WCOL, rect.bottom * 3 / WCOL),
		0, 0, 465, 95, Unit::UnitPixel);

	graphic->DrawImage(HeroPixel,
		Rect(rect.right / WCOL + 70, rect.bottom * 5 / WCOL, 50, 50),
		128, 0, 64, 64, Unit::UnitPixel);
	graphic->DrawImage(HeroPixel,
		Rect(rect.right * 3 / WCOL + 50, rect.bottom * 5 / WCOL + 20, 50, 50),
		64, 0, 64, 64, Unit::UnitPixel);
	graphic->DrawImage(HeroPixel,
		Rect(rect.right * 4 / WCOL - 10, rect.bottom * 5 / WCOL + 80, 50, 50),
		192, 0, 64, 64, Unit::UnitPixel);
	graphic->DrawImage(HeroPixel,
		Rect(rect.right * 6 / WCOL + 180, rect.bottom * 5 / WCOL + 80, 50, 50),
		0, 0, 64, 64, Unit::UnitPixel);
	graphic->DrawImage(EnemyImage[3],
		Rect(rect.right / WCOL + 20, rect.bottom * 5 / WCOL, 50, 50),
		cnt / 10 * 48, 0, 48, 48, Unit::UnitPixel);
	graphic->DrawImage(EnemyImage[2],
		Rect(rect.right * 3 / WCOL + 100, rect.bottom * 5 / WCOL + 20, 50, 50),
		cnt / 10 * 48, 0, 48, 48, Unit::UnitPixel);
	graphic->DrawImage(EnemyImage[2],
		Rect(rect.right * 4 / WCOL + 40, rect.bottom * 5 / WCOL + 80, 50, 50),
		cnt / 10 * 48, 0, 48, 48, Unit::UnitPixel);
	graphic->DrawImage(EnemyImage[3],
		Rect(rect.right * 6 / WCOL + 130, rect.bottom * 5 / WCOL + 80, 50, 50),
		cnt / 10 * 48, 0, 48, 48, Unit::UnitPixel);
	
	if (cnt == 50) cnt = 1;
	else cnt++;
		
	delete graphic;

	BitBlt(hdc, 0, 0, rect.right, rect.bottom, memDC, 0, 0, SRCCOPY);
	SelectObject(memDC, oldBit);
	DeleteObject(newBit);

	DeleteDC(memDC);
}

void GameManager::CreateEnemy()
{
	Enemy* e = new Enemy;
	POINT pt;
	e->cs = Stats[6];
	pt = ut.ToMapPos(respon, mapw, maph);
	pt.x += mapx;
	pt.y += mapy;
	e->cs.curPos = pt;
	e->path = cpath;
	e->cs.cnt = e->cs.atkspd;
	enems.push_back(e);
	gs.wave--;
}

void GameManager::CreateHero(POINT pt, int hnum)
{
	Hero* h = new Hero;
	h = HeroInfo[hnum];
	pt.x -= mapx;
	pt.y -= mapy;
	pt = ut.ToTilePos(pt, mapw, maph);
	MapInfo[pt.x][pt.y] = 4;
	pt = ut.ToMapPos(pt, mapw, maph);
	pt.x += mapx;
	pt.y += mapy;
	h->cs.curPos = pt;
	ch.FindAtkDir(h, cpath, rect);
	h->cs.cnt = h->cs.atkspd;
	heros.push_back(h);
	gs.coin -= h->cost;
}

BOOL GameManager::CreatAble(POINT pt, int hnum)
{
	if (hnum > 2)
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
		if (enems[i]->path.size() == enems[i]->pathcount + 1)
		{
			enems.erase(enems.begin() + i);
			gs.life--;
		}
		else if (enems.size() > 0)
		{
			Collision(enems[i]);
			if (enems[i]->cs.state == 1 || enems[i]->cs.state == 3)
				ch.Move(enems[i], rect);
			else if (enems[i]->cs.state == 2)
				Attack(enems[i]);
			if (enems[i]->cs.death)
			{
				enems.erase(enems.begin() + i);
				gs.coin += 10;
			}
		}
	}

	for (i = 0; i < heros.size(); i++)
	{
		ch.Target(heros[i], enems, rect);
		if (heros[i]->cs.state == 2)
		{
			//if (heros[i]->heronum < 3)
			//	ShootProj(heros[i]);
		}
		if (heros[i]->cs.death)
		{
			heros.erase(heros.begin() + i);
		}
	}

	/*for (i = 0; i < projs.size(); i++)
	{
		ch.Move(projs[i], rect);
		if (projs[i]->cs.death)
		{
			projs.erase(projs.begin() + i);
		}
	}*/

	for (i = 0; i < 6; i++)
	{
		if (cost[i] > gs.coin)
			buyAble[i] = false;
		else
			buyAble[i] = true;
	}
}

void GameManager::Play(HDC hdc)
{
	HDC memDC;
	HBITMAP oldBit, newBit;
	int w = rect.right / ROW;
	int h = rect.bottom / WCOL;

	memDC = CreateCompatibleDC(hdc);

	newBit = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
	oldBit = (HBITMAP)SelectObject(memDC, newBit);

	Graphics* graphic = new Graphics(memDC);

	SolidBrush brush(Color(130, 170, 170, 170));
	graphic->DrawImage(MapImage, 0, 0, rect.right, rect.bottom);
	graphic->FillRectangle(&brush, 0, 0, rect.right, rect.bottom * 2 / WCOL);
	graphic->FillRectangle(&brush, 0, mapy, rect.right / WCOL, rect.bottom * 6 / WCOL);
	graphic->FillRectangle(&brush, 0, mapy + maph, rect.right, rect.bottom * 2 / WCOL);
	graphic->FillRectangle(&brush, mapx + mapw, mapy, rect.right * 2 / WCOL, rect.bottom * 6 / WCOL);
	DrawEnemy(memDC,graphic);
	DrawHero(memDC, graphic);
	DrawBuyableTile(graphic);
	DrawGameInfo(graphic);
	DrawCoin(graphic);
	if (state == 1)
	{
		RangeSelected(graphic);
		DrawHeroInfo(memDC, graphic);
	}
	else if (state == 2)
	{
		AdjSelected(graphic);
		DrawHeroInfo(memDC, graphic);
	}

	delete graphic;

	BitBlt(hdc, 0, 0, rect.right, rect.bottom, memDC, 0, 0, SRCCOPY);
	SelectObject(memDC, oldBit);
	DeleteObject(newBit);

	DeleteDC(memDC);
}

//void GameManager::ShootProj(Hero* hero)
//{
//	POINT pt;
//	if (hero->cs.cnt == hero->cs.atkspd)
//	{
//		Projectile* p = new Projectile;
//		pt = hero->cs.curPos;
//		p->cs.curPos = p->init = pt;
//		p->cs.dir = hero->cs.dir;
//		p->cs.range = hero->cs.range;
//		projs.push_back(p);
//	}
//}

void GameManager::Attack(Enemy* e)
{
	int i = 0;
	POINT pt;
	pt = e->path[e->pathcount + 1];
	pt = ut.ToMapPos(pt, mapw, maph);
	pt.x += mapx;
	pt.y += mapy;

	if (e->cs.cnt == e->cs.atkspd)
	{
		e->cs.cnt = 1;
		while (i < heros.size())
		{
			if (heros[i]->cs.curPos.x == pt.x && 
				heros[i]->cs.curPos.y == pt.y)
			{
				ch.Damaged(heros[i], e->cs.dmg);
				if (heros[i]->cs.hp <= 0)
				{
					heros[i]->cs.death = true;
					pt = e->path[e->pathcount + 1];
					MapInfo[pt.x][pt.y] = 1;
				}
				break;
			}
			i++;
		}
	}
	else
		e->cs.cnt++;
}

void GameManager::Collision(Enemy* e)
{
	POINT pt, mpt;
	mpt = e->path[e->pathcount];
	mpt = ut.ToMapPos(mpt, mapw, maph);
	mpt.x += mapx + e->curDir.x * mapw/ROW/2;
	mpt.y += mapy + e->curDir.y * maph / COL / 4;
	pt = e->path[e->pathcount + 1];
	if (MapInfo[pt.x][pt.y] == 4)
	{
		if (abs(e->cs.curPos.x - mpt.x) < mapw / ROW / 4)
			e->cs.state = 2;
	}
	else
		e->cs.state = 1;

	for (int i = 0; i < enems.size(); i++)
	{
		if (enems[i]->cs.curPos.x == e->cs.curPos.x
			&& enems[i]->cs.curPos.y == e->cs.curPos.y)
		{
			e->cs.curPos.y += 3;
			enems[i]->cs.curPos.y -= 3;
		}
	}
}

void GameManager::close()
{
	int i;
	for (i = 0; i < enems.size(); i++)
		delete enems[i];
	for (i = 0; i < heros.size(); i++)
		delete heros[i];
	/*for (i = 0; i < projs.size(); i++)
		delete projs[i];*/
}