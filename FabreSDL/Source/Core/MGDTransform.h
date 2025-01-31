#ifndef MGD_Transform_h_
#define MGD_Transform_h_

#include <SDL_rect.h>

struct MGDTransform {
    SDL_FPoint Position{};
    SDL_FPoint Rotation{};
    SDL_FPoint Scale{1.f, 1.f};
};

#endif // MGD_Transform_h_
