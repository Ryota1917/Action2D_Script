#include "Font.h"
#include"../SDL_Wrapper/SDL_Wrapper.h"

Font::Font(Game* game, SDL_Renderer* renderer):
	mGame(game), mRenderer(renderer)
{
}

Font::~Font()
{
}

bool Font::Load(const std::string& fileName)
{
	// サポートするフォントサイズ
	std::vector<int> sizes = { 12,18,24,30 };

	// サイズごとにTTF_OpenFont
	for (auto& size : sizes) {
		TTF_Font* font = TTF_OpenFont(fileName.c_str(), size);

		if (!font) {
			SDL_Log("Failed to load font %s in size %d", fileName.c_str(), size);
			return false;
		}

		mFontDataMap.emplace(size, font);
	}

	return true;
}

void Font::UnLoad()
{
	for (auto& font : mFontDataMap) {
		TTF_CloseFont(font.second);
	}
}

SDL_Texture_Unique Font::LoadSDLTexture(const std::string& text, int pointSize, const Vector3& color)
{
	// colorを作る
	SDL_Color sdlColor;
	sdlColor.r = static_cast<Uint8>(color.x * 255);
	sdlColor.g = static_cast<Uint8>(color.y * 255);
	sdlColor.b = static_cast<Uint8>(color.z * 255);
	sdlColor.a = 255;

	auto fontIter = mFontDataMap.find(pointSize);
	if (fontIter == mFontDataMap.end()) {
		SDL_Log("指定したフォントサイズは対応していません．");
		return nullptr;
	}

	// フォントデータからSurfaceを作る
	SDL_Surface_Unique surface = SDL_Surface_Unique(TTF_RenderUTF8_Solid(mFontDataMap[pointSize], text.c_str(), sdlColor));
	if (!surface) {
		SDL_Log("フォントからサーフェスの作成に失敗しました．");
		return nullptr;
	}

	// SurfaceからTexureを作る
	auto texture = SDL_CreateTextureFromSurface(mRenderer, surface.get());
	if (!texture) {

		SDL_Log("サーフェスからテクスチャの作成に失敗しました．");
		return nullptr;
	}

	return SDL_Texture_Unique(texture);
}

SDL_Texture_Unique Font::LoadSDLTextureWrapped(const std::string& text, int pointSize, const Vector3& color, int wrapLength)
{
	// colorを作る
	SDL_Color sdlColor;
	sdlColor.r = static_cast<Uint8>(color.x * 255);
	sdlColor.g = static_cast<Uint8>(color.y * 255);
	sdlColor.b = static_cast<Uint8>(color.z * 255);
	sdlColor.a = 255;

	auto fontIter = mFontDataMap.find(pointSize);
	if (fontIter == mFontDataMap.end()) {
		SDL_Log("指定したフォントサイズは対応していません．");
		return nullptr;
	}

	// フォントデータからSurfaceを作る
	SDL_Surface_Unique surface = SDL_Surface_Unique(TTF_RenderUTF8_Solid_Wrapped(mFontDataMap[pointSize], text.c_str(), sdlColor, wrapLength));
	if (!surface) {
		SDL_Log("フォントからサーフェスの作成に失敗しました．");
		return nullptr;
	}

	// SurfaceからTexureを作る
	auto texture = SDL_CreateTextureFromSurface(mRenderer, surface.get());
	if (!texture) {

		SDL_Log("サーフェスからテクスチャの作成に失敗しました．");
		return nullptr;
	}

	return SDL_Texture_Unique(texture);
}

