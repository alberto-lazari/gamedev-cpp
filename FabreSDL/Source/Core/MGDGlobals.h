#ifndef MGD_Globals_h_
#define MGD_Globals_h_

#include <SDL_mixer.h>
#include <SDL_ttf.h>

// Screen dimension constants
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

// The window we'll be rendering to
extern struct SDL_Window* globalWindow;

// The window renderer
extern struct SDL_Renderer* globalRenderer;

// Globally used font
extern TTF_Font* globalFont;

// The music that will be played
extern Mix_Music* globalMusic;

#endif // MGD_Globals_h_
