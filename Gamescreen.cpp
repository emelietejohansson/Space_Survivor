#include "Gamescreen.h"
#include "BlinkScreen.h"
#include "GameApp.h"
#include "Graphics.h"
#include "Rymdskepp.h"
#include "Res.h"
#include "ProjectileSpaceship.h"
#include <stdio.h>
#include <math.h>


////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
Gamescreen::Gamescreen() {

	mGameobject = 0;	

	// L�s in en bild av ett ansikte.
	//mFaceSurface = SDL_LoadBMP("assets/face.bmp");
	//SDL_SetColorKey(mFaceSurface, SDL_TRUE, RGB(255, 0, 255));

	//L�s in bakgrundsbild

	//mBGSurface = SDL_LoadBMP("assets/background.bmp");
	mBGSurface = BG_SURFACE;


	// Ansiktets position och hastighet.
	//mFaceX = 100;
	//mFaceY = 100;
	//mFaceSpeedX = 0;
	//mFaceSpeedY = 0;

	//Bakgrundens position

	mBGX = 0.0f;

	//skapa rymdskepp

	//SetGameobject(new Rymdskepp());
	mGameobject = new Rymdskepp();
	mGameobject->SetGamescreen(this);
}

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
Gamescreen::~Gamescreen() {
	// Frig�r bild.
	//SDL_FreeSurface(mFaceSurface);
	//SDL_FreeSurface(mBGSurface);
	printf("Gamescreen destroyed\n");
}

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void Gamescreen::KeyDown(SDL_Keycode keyCode) {
	// S�tt hastighet f�r ansiktet.
	if (keyCode == SDLK_LEFT) {
		//mFaceSpeedX = -1;
		mGameobject->SetSpeed(-2.0, 0.0);
	}
	else if (keyCode == SDLK_RIGHT) {
		//mFaceSpeedX = 1;
		mGameobject->SetSpeed(2.0, 0.0);
	}
	else if (keyCode == SDLK_UP) {
		//mFaceSpeedY = -1;
		//mGameobject->SetSpeed(0.0, -2.0);
		mUp = true;
	}
	else if (keyCode == SDLK_DOWN) {
		mDown = true;
		//mFaceSpeedY = 1;
		//mGameobject->SetSpeed(0.0, 2.0);
	}
	else if (keyCode == SDLK_SPACE) {
		mSpace = true;
		//mGameobject->Fire();
	}
	else if (keyCode == SDLK_ESCAPE) {
		GameApp()->SetScreen(new BlinkScreen());
	}
}

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void Gamescreen::KeyUp(SDL_Keycode keyCode) {
	if (keyCode == SDLK_LEFT || keyCode == SDLK_RIGHT) {
		//mFaceSpeedX = 0;
		mGameobject->SetSpeed(0.0, 0.0);
	}
	else if (keyCode == SDLK_UP) {
		//mFaceSpeedY = 0;
		mUp = false;
		mGameobject->SetSpeed(0.0, 0.0);
	}
	else if (keyCode == SDLK_DOWN) {
		//mFaceSpeedY = 0;
		mDown = false;
		mGameobject->SetSpeed(0.0, 0.0);
	}
	else if (keyCode == SDLK_SPACE) {
		mSpace = false;
	}
}

////////////////////////////////////////////////////////////////////////////////
// Anropas 100 g�nger per sekund. Utf�r all logik h�r. 
////////////////////////////////////////////////////////////////////////////////
void Gamescreen::Update() {
	// Flytta ansiktet.
	//mFaceX += mFaceSpeedX;
	//mFaceY += mFaceSpeedY;

	mBGX = mBGX - 1.0f;
	if (mBGX < -640.0) mBGX += 640.0;

	mGameobject->Update();
	for (std::list<ProjectileSpaceship*>::iterator it=herobullets.begin(); it != herobullets.end(); ++it) {
		(*it)->Update();
	}
	for (std::list<ProjectileSpaceship*>::iterator it=killedherobullets.begin(); it != killedherobullets.end(); ++it) {
		herobullets.remove(*it);
		delete *it;

		//(*it)->Update();
		//herobullets.remove(projectile);
	/*delete ProjectileSpaceship;*/
	//delete projectile;
	printf("Finally killed projectile!\n");
	}
	if (mSpace)
		mGameobject->Fire();

	if (mUp)		
		mGameobject->SetSpeed(0.0, -2.0);

	if (mDown)
		mGameobject->SetSpeed(0.0, 2.0);
	killedherobullets.clear();
}

////////////////////////////////////////////////////////////////////////////////
// Utf�r all utritning h�r.
////////////////////////////////////////////////////////////////////////////////
void Gamescreen::Draw(Graphics *g) {
	// Rensa sk�rmen.
	//g->Clear(RGB(255, 255, 255));
	g->DrawImage(mBGSurface, (int)mBGX, 0);
	g->DrawImage(mBGSurface, (int)(mBGX + 640.0), 0);
	// Rita ut ansikte.
	//g->DrawImage(mFaceSurface, mFaceX, mFaceY);
	mGameobject->Draw(g);
	/*for (std::list<int>::iterator it=mylist.begin(); it != mylist.end(); ++it)
    std::cout << ' ' << *it;
	std::list<ProjectileSpaceship*> herobullets;
	*/
	for (std::list<ProjectileSpaceship*>::iterator it=herobullets.begin(); it != herobullets.end(); ++it) {
		(*it)->Draw(g);
	}


}
///////////////////////////////
void Gamescreen::SetGameobject(Gameobject *gameobject) {
	if (gameobject) gameobject->SetGamescreen(this);
	if (mGameobject == 0) {
		mGameobject = gameobject;
	}
/*	else {
		mNewScreen = screen;
	}*/
}
//////////////////
void Gamescreen::GenerateProjectileSpaceship(float x, float y) {
	ProjectileSpaceship *tempbullet = new ProjectileSpaceship(x, y);
	tempbullet->SetGamescreen(this);
	herobullets.push_back(tempbullet);
	printf("Gave birth to projectile!\n");
}
/////////////////////////////
void Gamescreen::KillObject(ProjectileSpaceship *projectile) {
	//herobullets.remove(projectile);
	/*delete ProjectileSpaceship;*/
	//delete projectile;
	killedherobullets.push_back(projectile);
	printf("Killed projectile!\n");
}