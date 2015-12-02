#include "ProjectileSpaceship.h"
#include "GameApp.h"
#include "Graphics.h"
#include "Gamescreen.h"
#include "Res.h"
#include <stdio.h>
#include <math.h>


////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
ProjectileSpaceship::ProjectileSpaceship(float x, float y, float sy = 0) {
	// L�s in en bild av ett ansikte.
	//mFaceSurface = SDL_LoadBMP("assets/face.bmp");
	//SDL_SetColorKey(mFaceSurface, SDL_TRUE, RGB(255, 0, 255));
	mBigbullet = SPACESHIP_BULLET;

	//mBGSurface = SDL_LoadBMP("assets/background.bmp");


	// Ansiktets position och hastighet.
	mX = x + 64;
	mY = y + 22;
	mSpeedX = 3.0;
	mSpeedY = sy;

	w = mBigbullet->w;
	h = mBigbullet->h;
	//printf("bredd = %d\n", w);

	//mBGX = 0.0f;


}

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
ProjectileSpaceship::~ProjectileSpaceship() {
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
void ProjectileSpaceship::Update() {
	// Flytta ansiktet.
	mX += mSpeedX;
	mY += mSpeedY;
	if (mY<40.0)
		mY = 40.0;
	if(mX>800) {
		mGamescreen->KillObject(this);
	}
	/*if(mX>1024) {
		mGamescreen->KillObject(this);
	}*/

}

////////////////////////////////////////////////////////////////////////////////
// Utf�r all utritning h�r.
////////////////////////////////////////////////////////////////////////////////
void ProjectileSpaceship::Draw(Graphics *g) {
	// Rensa sk�rmen.
	//g->Clear(RGB(255, 255, 255));
	//g->DrawImage(mBGSurface, (int)mBGX, 0);
	//g->DrawImage(mBGSurface, (int)(mBGX + 640.0), 0);
	// Rita ut ansikte.
	g->DrawImage(mBigbullet, mX, mY);


}
////////////////////////////////7
void ProjectileSpaceship::SetSpeed(float SpeedX, float SpeedY){
	mSpeedX = SpeedX;
	mSpeedY = SpeedY;
}
////////////////////////////////////
void ProjectileSpaceship::Overlap(Gameobject *gameobject) {
	mGamescreen->KillObject(this);
	//printf("Projektil d�dad pga kollision!\n");
}