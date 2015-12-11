#include "PowerUp.h"
#include "GameApp.h"
#include "Graphics.h"
#include "Res.h"
#include "Gamescreen.h"
#include "GameApp.h"
#include "Graphics.h"
#include "Res.h"
#include "Rymdskepp.h"
#include "audiere.h"
#include <stdio.h>
#include <math.h>
#include <typeinfo>


PowerUp::PowerUp(float y, float xs)
{
	mX = 800;
	mY = y;
	mSpeedX = xs;
	mSpeedY = 0;
	mHealth = 30;
}


PowerUp::~PowerUp() {
}
void PowerUp::Update()
{
	mX += mSpeedX;
	if (mX < 0) {
		mGamescreen->KillObjectPowerUp(this);
		printf("H�r borde powerup d�das!");
	}
}

void PowerUp::Draw(Graphics *g) {
}

void PowerUp::Overlap(Gameobject *gameobject) {
}