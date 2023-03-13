#pragma once
#include<string>
#include<SDL_ttf.h>
#include<vector>
#include<unordered_map>
#include"../Util/Math.h"
#include"../SDL_Wrapper/SDL_Wrapper.h"

class Font {
public:
	Font(class Game* game, SDL_Renderer* renderer);
	~Font();

	bool Load(const std::string& fileName);
	void UnLoad();

	SDL_Texture_Unique LoadSDLTexture(const std::string& text, int pointSize = 30, const Vector3& color = Color::White);
	SDL_Texture_Unique LoadSDLTextureWrapped(const std::string& text, int pointSize = 30, const Vector3& color = Color::White, int wrapLength = 0);

private:
	class Game* mGame;
	std::unordered_map<int, TTF_Font*> mFontDataMap;
	SDL_Renderer* mRenderer; // TODO: ‚±‚±‚ÉƒŒƒ“ƒ_ƒ‰[‚ğ“ü‚ê‚Ä‚¢‚¢‚Ì‚©ŒŸ“¢
};