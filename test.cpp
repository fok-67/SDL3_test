#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <cmath> // sin, cos

class App {
public:
	App() = default;

	~App() {
	    SDL_DestroyWindow(m_window);
	    SDL_Quit();
	}

	bool init() {
	    if (!SDL_Init(SDL_INIT_VIDEO)) {
	        SDL_Log("Errore Init: %s", SDL_GetError());
	        return false;
	    }
	
	    if (!SDL_CreateWindowAndRenderer("SDL3 C++17 Test", 800, 600, 0, &m_window, &m_renderer)) {
	        SDL_Log("Errore Creazione Finestra: %s", SDL_GetError());
	        return false;
	    }
	    return true;
	}

	SDL_Renderer* renderer() const { return m_renderer; }

private:
	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;
};

// --- Funzioni di Callback richieste da SDL3 ---

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
	auto app{ new App };
	if (!app->init()) {
		delete app;
		return SDL_APP_FAILURE;
	}
	*appstate = app;
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
	if ((event->type == SDL_EVENT_QUIT) ||
	    (event->type == SDL_EVENT_KEY_DOWN) && (event->key.key == SDLK_ESCAPE)) {
	    return SDL_APP_SUCCESS;
	}
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
	auto* app{ static_cast<App*>(appstate) };
	
	const float time{ SDL_GetTicks() / 1000.0f };
	
	uint8_t r{ static_cast<uint8_t>(127 + 127 * std::sin(time)) };
	SDL_SetRenderDrawColor(app->renderer(), 25, r, 25, 255);
	SDL_RenderClear(app->renderer());
	
	SDL_FRect rect{
	    400.0f + std::cos(time) * 200.0f - 50.0f,
	    300.0f + std::sin(time) * 200.0f - 50.0f,
	    100.0f, 100.0f
	};
	
	SDL_SetRenderDrawColor(app->renderer(), 255, 255, 255, 255);
	SDL_RenderFillRect(app->renderer(), &rect);
	
	SDL_RenderPresent(app->renderer());
	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
	if (appstate)
	    delete static_cast<App*>(appstate);
}

