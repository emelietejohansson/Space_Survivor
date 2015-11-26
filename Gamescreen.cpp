#include "Gamescreen.h"
#include "BlinkScreen.h"
#include "Gameover.h"
#include "GameApp.h"
#include "Graphics.h"
#include "Rymdskepp.h"
#include "Res.h"
#include "ProjectileSpaceship.h"
#include "ProjectileEnemy.h"
#include "Enemy.h"
#include "WeaponEnemy.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <algorithm>
#include "audiere.h"
#include "Font.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
Gamescreen::Gamescreen() {

	// audiere.
	sMusic->play();
	sMusic->setRepeat(true);
	//

	mGameobject = 0;	

	//L�s in bakgrundsbild

	mBGSurface = BG_SURFACE;
	mTio = TIO;
	mNio = NIO;
	m�tta = �TTA;
	mSju = SJU;
	mSex = SEX;
	mFem = FEM;
	mFyra = FYRA;
	mTre = TRE;
	mTv� = TV�;
	mEtt = ETT;

	mMyFont = new Font("assets/font_fire.bmp");

	mUp = false; 
	mDown = false; 
	mLeft = false; 
	mRight = false; 
	mSpace = false; 


	//Bakgrundens position

	mBGX = 0.0f;
	mLifeX = 670;
	mLifeY = 5;
	mScoreX = 5;
	mScoreY = 5;

	//skapa rymdskepp

	//SetGameobject(new Rymdskepp());
	mGameobject = new Rymdskepp();
	mGameobject->SetGamescreen(this);
	counter = 0;
	gameover = false;
	points = 0;
}

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
Gamescreen::~Gamescreen() {
	// Frig�r bild.
	//SDL_FreeSurface(mFaceSurface);
	//SDL_FreeSurface(mBGSurface);
	printf("Gamescreen destroyed\n");

	delete mMyFont;
	// audiere.
	sMusic->stop();
}

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void Gamescreen::KeyDown(SDL_Keycode keyCode) {
	// S�tt hastighet f�r rymdskeppet.
	if (keyCode == SDLK_LEFT) {
		//mGameobject->SetSpeedX(-2.0);
		mLeft = true;
	}
	else if (keyCode == SDLK_RIGHT) {
		//mGameobject->SetSpeedX(2.0);
		mRight = true;
	}
	if (keyCode == SDLK_UP) {
		//mGameobject->SetSpeedY(-2.0);
		mUp = true;
	}
	else if (keyCode == SDLK_DOWN) {
		//mGameobject->SetSpeedY(2.0);
		mDown = true;
	}
	if (keyCode == SDLK_SPACE) {
		//GenerateProjectileSpaceship(mGameobject->GetPosX(), mGameobject->GetPosY());
		//mGameobject->Fire();
		mSpace = true;
	}
}

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void Gamescreen::KeyUp(SDL_Keycode keyCode) {
	if (keyCode == SDLK_LEFT) {
		mLeft = false;
		mGameobject->SetSpeedX(0.0);
	}
	else if (keyCode == SDLK_RIGHT) {
		mRight = false;
		mGameobject->SetSpeedX(0.0);
	}

	if (keyCode == SDLK_UP) {
		mUp = false;
		mGameobject->SetSpeedY(0.0);
	}
	else if (keyCode == SDLK_DOWN) {
		mDown = false;
		mGameobject->SetSpeedY(0.0);
	}
	if (keyCode == SDLK_SPACE) {
		mSpace = false;
	}
}

////////////////////////////////////////////////////////////////////////////////
// Anropas 100 g�nger per sekund. Utf�r all logik h�r. 
////////////////////////////////////////////////////////////////////////////////
void Gamescreen::Update() {

	mBGX = mBGX - 0.5f;
	if (mBGX < -800.0) mBGX += 800.0;
	//if (mBGX < -640.0) mBGX += 640.0;
	//if (mBGX < -1024.0) mBGX += 1024.0;

	if (counter < 1500 && counter%200 == 0){
		//randy = rand()%413;
		//randy = rand()%704;
		randy = rand()%693 + 40;
		GenerateEnemy(randy);
	}
	else if (counter >= 1500 && counter < 3000 && counter%100 == 0) {
		//randy = rand()%413;
		//randy = rand()%704;
		randy = rand()%693 + 40;
		GenerateWeaponEnemy(randy);
	}
	else if (counter >= 3000 && counter%50 == 0) {
		//randy = rand()%413;
		//randy = rand()%704;
		randy = rand()%693 + 40;
		if (counter%100 == 0)
			GenerateWeaponEnemy(randy);
		else
			GenerateEnemy(randy);
	}

	CheckOverlapSpaceship(mGameobject, enemies, enemybullets); 
	CheckOverlapHerobullets(herobullets, enemies);

	mGameobject->Update();
	/*for (std::list<ProjectileSpaceship*>::iterator it=herobullets.begin(); it != herobullets.end(); ++it) {
		(*it)->Update();
	}*/
	for (std::list<Gameobject*>::iterator it = herobullets.begin(); it != herobullets.end(); ++it) {
		(*it)->Update();
	}
	for (std::list<Gameobject*>::iterator it = enemybullets.begin(); it != enemybullets.end(); ++it) {
		(*it)->Update();
	}
	for (std::list<Enemy*>::iterator it=enemies.begin(); it != enemies.end(); ++it) {
		(*it)->Update();
	}
 	/*for (std::list<ProjectileSpaceship*>::iterator it=killedherobullets.begin(); it != killedherobullets.end(); ++it) {
		herobullets.remove(*it);
		//printf("Finally killed projectile!\n");
		delete *it;
	}*/
	for (std::list<Gameobject*>::iterator it=killedherobullets.begin(); it != killedherobullets.end(); ++it) {
			herobullets.remove(*it);	
			enemybullets.remove(*it);
		//printf("Finally killed projectile!\n");
		delete *it;
	}
	for (std::list<Enemy*>::iterator it=killedenemies.begin(); it != killedenemies.end(); ++it) {
		enemies.remove(*it);
		delete *it;
		//printf("Finally killed enemy!\n");
	}
	killedherobullets.clear();
	killedenemies.clear();
	if (mUp)
		mGameobject->SetSpeedY(-2.0);
	if (mDown)
		mGameobject->SetSpeedY(2.0);
	if (mLeft)
		mGameobject->SetSpeedX(-2.0);
	if (mRight)
		mGameobject->SetSpeedX(2.0);
	if (mSpace)
		mGameobject->Fire();
	if (gameover) {
		KillAll();
		delete mGameobject;
		printf("GAME OVER!!!\n");
		GameApp()->SetScreen(new Gameover(points));
	}
	counter = counter + 1;
}

////////////////////////////////////////////////////////////////////////////////
// Utf�r all utritning h�r.
////////////////////////////////////////////////////////////////////////////////
void Gamescreen::Draw(Graphics *g) {
	// Rensa sk�rmen.
	//g->Clear(RGB(255, 255, 255));
	g->DrawImage(mBGSurface, (int)mBGX, 0);
	g->DrawImage(mBGSurface, (int)(mBGX + 800.0), 0);
	//g->DrawImage(mBGSurface, (int)(mBGX + 640.0), 0);
	//g->DrawImage(mBGSurface, (int)(mBGX + 1024.0), 0);
	
	mGameobject->Draw(g);

	//Rymdskepp *rp = (Rymdskepp *)mGameobject;
	Rymdskepp *rp = dynamic_cast<Rymdskepp*>(mGameobject);

	life = rp->GetHealth();
	if (life == 100)
		g->DrawImage(mTio, mLifeX, mLifeY);
	else if (life == 90)
		g->DrawImage(mNio, mLifeX, mLifeY);
	else if (life == 80)
		g->DrawImage(m�tta, mLifeX, mLifeY);		
	else if (life == 70)
		g->DrawImage(mSju, mLifeX, mLifeY);
	else if (life == 60)
		g->DrawImage(mSex, mLifeX, mLifeY);
	else if (life == 50)
		g->DrawImage(mFem, mLifeX, mLifeY);
	else if (life == 40)
		g->DrawImage(mFyra, mLifeX, mLifeY);
	else if (life == 30)
		g->DrawImage(mTre, mLifeX, mLifeY);
	else if (life == 20)
		g->DrawImage(mTv�, mLifeX, mLifeY);
	else if (life == 10)
		g->DrawImage(mEtt, mLifeX, mLifeY);

	
	char tmp[64];
	sprintf(tmp, "SCORE: %d", points);
	mMyFont->WriteString(g, tmp, 10, 5);

	for (std::list<Gameobject*>::iterator it = herobullets.begin(); it != herobullets.end(); ++it) {
		(*it)->Draw(g);
	}
	for (std::list<Gameobject*>::iterator it = enemybullets.begin(); it != enemybullets.end(); ++it) {
		(*it)->Draw(g);
	}
	for (std::list<Enemy*>::iterator it=enemies.begin(); it != enemies.end(); ++it) {
		(*it)->Draw(g);
	}


}
///////////////////////////////
void Gamescreen::SetGameobject(Gameobject *gameobject) {
	if (gameobject) gameobject->SetGamescreen(this);
	if (mGameobject == 0) {
		mGameobject = gameobject;
	}
}
//////////////////
void Gamescreen::GenerateProjectileSpaceship(float x, float y) {
	ProjectileSpaceship *tempbullet = new ProjectileSpaceship(x, y);
	tempbullet->SetGamescreen(this);
	herobullets.push_back(tempbullet);
	// audiere.
	sShootSound->play();
	//
	//printf("Gave birth to projectile!\n");
}
///////////////////////
void Gamescreen::GenerateProjectileEnemy(float x, float y) {
	ProjectileEnemy *tempbullet = new ProjectileEnemy(x, y);
	tempbullet->SetGamescreen(this);
	enemybullets.push_back(tempbullet);
	// audiere.
	sShootSound->play();
	//
	//printf("Gave birth to projectile!\n");
}
/////////////////////////////
/*void Gamescreen::KillObject(ProjectileSpaceship *projectile) {
	auto result = std::find(killedherobullets.begin(), killedherobullets.end(), projectile);
	if (result == killedherobullets.end())
		killedherobullets.push_back(projectile);
	//printf("Killed projectile!\n");
}*/
void Gamescreen::KillObject(Gameobject *gameobject) {
	auto result = std::find(killedherobullets.begin(), killedherobullets.end(), gameobject);
	if (result == killedherobullets.end())
		killedherobullets.push_back(gameobject);


	//printf("Killed projectile!\n");
}
//////////////////////////////
void Gamescreen::KillObjectEnemy(Enemy *enemy) {
	auto result = std::find(killedenemies.begin(), killedenemies.end(), enemy);
	if (result == killedenemies.end()) {
		killedenemies.push_back(enemy);
	}
	//printf("Killed enemy!\n");
}
/////////////////////////////
void Gamescreen::KillSpaceship() {
	gameover = true;
	// audiere.
	sExplosionSound->play();
}
////////////////////////////
void Gamescreen::GenerateEnemy(float y) {
	Enemy *tempenemy = new Enemy(y);
	tempenemy->SetGamescreen(this);
	enemies.push_back(tempenemy);
	//printf("Gave birth to enemy!\n");
}
//////////////////////////////////
void Gamescreen::GenerateWeaponEnemy(float y) {
	WeaponEnemy *tempenemy = new WeaponEnemy(y);
	tempenemy->SetGamescreen(this);
	enemies.push_back(tempenemy);
	//printf("Gave birth to enemy!\n");
}
/////////////////////////////////
/*void Gamescreen::CheckOverlapSpaceship(Gameobject *gameobject, std::list<Enemy*> enemies) {
	for (std::list<Enemy*>::iterator it=enemies.begin(); it != enemies.end(); ++it) {
		if ((mGameobject->GetPosX()+ mGameobject->Getw()) < (*it)->GetPosX() || (mGameobject->GetPosX() > ((*it)->GetPosX() + (*it)->Getw())))
			printf("");
		else if ((mGameobject->GetPosY()+ mGameobject->Geth()) < (*it)->GetPosY() || (mGameobject->GetPosY() > ((*it)->GetPosY() + (*it)->Geth())))
			printf("");
		else {
			mGameobject->Overlap(*it);
			(*it)->Overlap(mGameobject);
		}
	}
}*/
void Gamescreen::CheckOverlapSpaceship(Gameobject *gameobject, std::list<Enemy*> enemies, std::list<Gameobject*> enemybullets) {
	for (std::list<Enemy*>::iterator it=enemies.begin(); it != enemies.end(); ++it) {
		if ((mGameobject->GetPosX()+ mGameobject->Getw()) < (*it)->GetPosX() || (mGameobject->GetPosX() > ((*it)->GetPosX() + (*it)->Getw())))
			printf("");
		else if ((mGameobject->GetPosY()+ mGameobject->Geth()) < (*it)->GetPosY() || (mGameobject->GetPosY() > ((*it)->GetPosY() + (*it)->Geth())))
			printf("");
		else {
			mGameobject->Overlap(*it);
			(*it)->Overlap(mGameobject);
		}
	}

	for (std::list<Gameobject*>::iterator it = enemybullets.begin(); it != enemybullets.end(); ++it) {
		if ((mGameobject->GetPosX() + mGameobject->Getw()) < (*it)->GetPosX() || (mGameobject->GetPosX() > ((*it)->GetPosX() + (*it)->Getw())))
			printf("");
		else if ((mGameobject->GetPosY() + mGameobject->Geth()) < (*it)->GetPosY() || (mGameobject->GetPosY() > ((*it)->GetPosY() + (*it)->Geth())))
			printf("");
		else {
			mGameobject->Overlap(*it);
			(*it)->Overlap(mGameobject);
		}
	}

}
//////////////////////////////////
/*void Gamescreen::CheckOverlapHerobullets(std::list<ProjectileSpaceship*> herobullets, std::list<Enemy*> enemies) {
	for (std::list<ProjectileSpaceship*>::iterator hbit=herobullets.begin(); hbit != herobullets.end(); ++hbit) {
		for (std::list<Enemy*>::iterator it=enemies.begin(); it != enemies.end(); ++it) {
			if (((*hbit)->GetPosX()+ (*hbit)->Getw()) < (*it)->GetPosX() || ((*hbit)->GetPosX() > ((*it)->GetPosX() + (*it)->Getw())))
				printf("");
			else if (((*hbit)->GetPosY()+ (*hbit)->Geth()) < (*it)->GetPosY() || ((*hbit)->GetPosY() > ((*it)->GetPosY() + (*it)->Geth())))
				printf("");
			else {
				(*hbit)->Overlap(*it);
				(*it)->Overlap(*hbit);
			}
		}
	}
}*/
void Gamescreen::CheckOverlapHerobullets(std::list<Gameobject*> herobullets, std::list<Enemy*> enemies) {
	for (std::list<Gameobject*>::iterator hbit = herobullets.begin(); hbit != herobullets.end(); ++hbit) {
		for (std::list<Enemy*>::iterator it=enemies.begin(); it != enemies.end(); ++it) {
			if (((*hbit)->GetPosX()+ (*hbit)->Getw()) < (*it)->GetPosX() || ((*hbit)->GetPosX() > ((*it)->GetPosX() + (*it)->Getw())))
				printf("");
			else if (((*hbit)->GetPosY()+ (*hbit)->Geth()) < (*it)->GetPosY() || ((*hbit)->GetPosY() > ((*it)->GetPosY() + (*it)->Geth())))
				printf("");
			else {
				(*hbit)->Overlap(*it);
				(*it)->Overlap(*hbit);
			}
		}
	}
}
///////////////////////////////
void Gamescreen::PointsToPlayer() {
	points = points + 10;
	printf("Points=%d\n", points);
}
////////////////////7
void Gamescreen::KillAll() {
	for (std::list<Gameobject*>::iterator it = herobullets.begin(); it != herobullets.end(); ++it) {
		delete *it;
	}
	for (std::list<Gameobject*>::iterator it = enemybullets.begin(); it != enemybullets.end(); ++it) {
		delete *it;
	}
	for (std::list<Enemy*>::iterator it=enemies.begin(); it != enemies.end(); ++it) {
		delete *it;
	}
}