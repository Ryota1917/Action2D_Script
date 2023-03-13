#pragma once
#include<SDL.h>
#include<memory>
/// <summary>
/// SDLのクラスに関して，スマートポインタでリソースを正常に削除されるためのラッパー
/// </summary>
struct SDL_Delete {
	void operator() (SDL_Texture* texture) {
		if (texture) {
			SDL_DestroyTexture(texture);
		}
	}

	void operator()(SDL_Surface* surface) {
		if (surface) {
			SDL_FreeSurface(surface);
		}
	}

	void operator()(SDL_Renderer* renderer) {
		if (renderer) {
			SDL_DestroyRenderer(renderer);
		}
	}

	void operator()(SDL_Window* window) {
		if (window) {
			SDL_DestroyWindow(window);
		}
	}
};

using SDL_Texture_Unique = std::unique_ptr<SDL_Texture, SDL_Delete>;
using SDL_Surface_Unique = std::unique_ptr<SDL_Surface, SDL_Delete>;
using SDL_Renderer_Unique = std::unique_ptr<SDL_Renderer, SDL_Delete>;
using SDL_Window_Unique = std::unique_ptr<SDL_Window, SDL_Delete>;