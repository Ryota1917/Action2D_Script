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
	// �T�|�[�g����t�H���g�T�C�Y
	std::vector<int> sizes = { 12,18,24,30 };

	// �T�C�Y���Ƃ�TTF_OpenFont
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
	// color�����
	SDL_Color sdlColor;
	sdlColor.r = static_cast<Uint8>(color.x * 255);
	sdlColor.g = static_cast<Uint8>(color.y * 255);
	sdlColor.b = static_cast<Uint8>(color.z * 255);
	sdlColor.a = 255;

	auto fontIter = mFontDataMap.find(pointSize);
	if (fontIter == mFontDataMap.end()) {
		SDL_Log("�w�肵���t�H���g�T�C�Y�͑Ή����Ă��܂���D");
		return nullptr;
	}

	// �t�H���g�f�[�^����Surface�����
	SDL_Surface_Unique surface = SDL_Surface_Unique(TTF_RenderUTF8_Solid(mFontDataMap[pointSize], text.c_str(), sdlColor));
	if (!surface) {
		SDL_Log("�t�H���g����T�[�t�F�X�̍쐬�Ɏ��s���܂����D");
		return nullptr;
	}

	// Surface����Texure�����
	auto texture = SDL_CreateTextureFromSurface(mRenderer, surface.get());
	if (!texture) {

		SDL_Log("�T�[�t�F�X����e�N�X�`���̍쐬�Ɏ��s���܂����D");
		return nullptr;
	}

	return SDL_Texture_Unique(texture);
}

SDL_Texture_Unique Font::LoadSDLTextureWrapped(const std::string& text, int pointSize, const Vector3& color, int wrapLength)
{
	// color�����
	SDL_Color sdlColor;
	sdlColor.r = static_cast<Uint8>(color.x * 255);
	sdlColor.g = static_cast<Uint8>(color.y * 255);
	sdlColor.b = static_cast<Uint8>(color.z * 255);
	sdlColor.a = 255;

	auto fontIter = mFontDataMap.find(pointSize);
	if (fontIter == mFontDataMap.end()) {
		SDL_Log("�w�肵���t�H���g�T�C�Y�͑Ή����Ă��܂���D");
		return nullptr;
	}

	// �t�H���g�f�[�^����Surface�����
	SDL_Surface_Unique surface = SDL_Surface_Unique(TTF_RenderUTF8_Solid_Wrapped(mFontDataMap[pointSize], text.c_str(), sdlColor, wrapLength));
	if (!surface) {
		SDL_Log("�t�H���g����T�[�t�F�X�̍쐬�Ɏ��s���܂����D");
		return nullptr;
	}

	// Surface����Texure�����
	auto texture = SDL_CreateTextureFromSurface(mRenderer, surface.get());
	if (!texture) {

		SDL_Log("�T�[�t�F�X����e�N�X�`���̍쐬�Ɏ��s���܂����D");
		return nullptr;
	}

	return SDL_Texture_Unique(texture);
}

