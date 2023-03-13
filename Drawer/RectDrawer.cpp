#include "RectDrawer.h"
#include "../Actors/Actor.h"

RectDrawer::RectDrawer(const Vector2& size, Actor* owner, int order):
	Drawer(owner, order), mRectSize(size), mR(255), mG(255), mB(255), mA(255)
{
}

void RectDrawer::Draw(SDL_Renderer* renderer)
{
	SDL_Rect r;
	r.w = static_cast<int>(mRectSize.x * mOwner->GetScale().x);
	r.h = static_cast<int>(mRectSize.y * mOwner->GetScale().y);
	r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2);
	r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2);
	SDL_SetRenderDrawColor(renderer, mR, mG, mB, mA);
	SDL_RenderFillRect(renderer, &r);
}

void RectDrawer::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	mR = r;
	mG = g;
	mB = b;
	mA = a;
}
