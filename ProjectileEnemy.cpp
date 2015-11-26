#include "ProjectileEnemy.h"
#include "GameApp.h"
#include "Graphics.h"
#include "Gamescreen.h"
#include "Res.h"
#include <stdio.h>
#include <math.h>


////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
ProjectileEnemy::ProjectileEnemy(float x, float y) {
	// L�s in en bild av ett ansikte.
	//mFaceSurface = SDL_LoadBMP("assets/face.bmp");
	//SDL_SetColorKey(mFaceSurface, SDL_TRUE, RGB(255, 0, 255));
	mBigbullet = BIGBULLET_SURFACE;

	//mBGSurface = SDL_LoadBMP("assets/background.bmp");


	// Ansiktets position och hastighet.
	mX = x + 60;
	mY = y + 30;
	mSpeedX = -3.0;
	mSpeedY = 0;

	w = mBigbullet->w;
	h = mBigbullet->h;
	//printf("bredd = %d\n", w);

	//mBGX = 0.0f;


}

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
ProjectileEnemy::~ProjectileEnemy() {
	// Frig�r bild.
	//SDL_FreeSurface(mFaceSurface);
	//SDL_FreeSurface(mBGSurface);
	//printf("Herobullet destroyed\n");
}

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Anropas 100 g�nger per sekund. Utf�r all logik h�r. 
////////////////////////////////////////////////////////////////////////////////
void ProjectileEnemy::Update() {
	// Flytta ansiktet.
	mX += mSpeedX;
	mY += mSpeedY;
	/*if(mX>640) {
	mGamescreen->KillObject(this);
	}*/
	if (mY<40.0)
		mY = 40.0;
	if (mX<0) {
		mGamescreen->KillObject(this);
	}

	//mBGX = mBGX - 5.5f;
	//if (mBGX < -640.0) mBGX += 640.0;
}

////////////////////////////////////////////////////////////////////////////////
// Utf�r all utritning h�r.
////////////////////////////////////////////////////////////////////////////////
void ProjectileEnemy::Draw(Graphics *g) {
	// Rensa sk�rmen.
	//g->Clear(RGB(255, 255, 255));
	//g->DrawImage(mBGSurface, (int)mBGX, 0);
	//g->DrawImage(mBGSurface, (int)(mBGX + 640.0), 0);
	// Rita ut ansikte.
	g->DrawImage(mBigbullet, mX, mY);


}
////////////////////////////////7
void ProjectileEnemy::SetSpeed(float SpeedX, float SpeedY){
	mSpeedX = SpeedX;
	mSpeedY = SpeedY;
}
////////////////////////////////////
void ProjectileEnemy::Overlap(Gameobject *gameobject) {
	mGamescreen->KillObject(this);
	//printf("Projektil d�dad pga kollision!\n");
}