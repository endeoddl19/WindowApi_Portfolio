#pragma once

#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include "MapTool.h"
#include "Character.h"
#include <gdiplusgraphics.h>

class GameManager
{
private:
	GameStatus gs;
	Character ch;
	RECT rect;

	Image* Title;
	Image* MainMenu;
	Image* GameInfo[2];
	Image* PlayPause;
	Image* MapImage;
	Image* EnemyImage[6];
	Image* HeroImage;
	Image* HeroIcon;
	Image* HeroPixel;
	Image* HeroText;
	Image* HeroName;
	Image* Coin;
	Image* CoinText;
	Image* ProjImage[6];

	vector<Hero*> HeroInfo;
	CharStat Stats[8];
	vector<POINT> cpath;
	POINT respon = { 1,0 };
	POINT destin = { 7,6 };
	BOOL buyAble[6];
	int cost[6] = { 100,150,200,150,200,300 };
	int pcost[18] = { 1,0,0,1,5,0,2,0,0,1,5,0,2,0,0,3,0,0 };
	int MapInfo[ROW][COL] = { 0 };
	// 0: ºóÄ­ /  1: ±æ /  2: Ãâ¹ß / 3: µµÂø / 4: ¿µ¿õ
	int mapw, maph, mapx, mapy, state, hnum;
	// state < 0: ÇÃ·¹ÀÌ / 1: ÀÏ½ÃÁ¤Áö / 2: ¿µ¿õ¼±ÅÃ >

	void FindPath();
	void setImages();
	void DrawEnemy(HDC, Graphics*);
	void DrawHero(HDC, Graphics*);
	void DrawHpBar(HDC,POINT,FLOAT);
	void RangeSelected(Graphics*);
	void AdjSelected(Graphics*);
	void DrawBuyableTile(Graphics*);
	void DrawHeroInfo(HDC hdc, Graphics*);
	void DrawGameInfo(Graphics*);
	void DrawCoin(Graphics*);
public:
	vector<Hero*> heros;
	vector<Enemy*> enems;
	//vector<Projectile*> projs;
	GameManager();
	~GameManager() {}
	Utils ut;

	void SetGame(RECT);
	void DrawMain(HDC);
	void CreateEnemy();
	void CreateHero(POINT, int);
	BOOL CreatAble(POINT, int);
	void setState(int s) { state = s; }
	void setHnum(int h) { hnum = h; }
	BOOL isBuyable(int hnum) { return buyAble[hnum]; }
	void Collision(Enemy*);
	//void ShootProj(Hero*);
	void Attack(Enemy*);
	
	void Update();
	void Play(HDC);
	GameStatus CurStatus() { return gs; }
	void close();
};

#endif