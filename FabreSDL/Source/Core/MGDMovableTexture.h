#ifndef MGD_MovableTexture_h_
#define MGD_MovableTexture_h_

#include <SDL.h>

// The texture that will move around on the screen
class MGDMovableTexture {
public:
    // Initializes the variables
    MGDMovableTexture();

    // Initializes the variables and tries to load a texture from the path
    MGDMovableTexture(const char* path);

    // Deinitializes the variables
    ~MGDMovableTexture();

    // Takes key presses and adjusts the texture's velocity
    void handleEvent(SDL_Event& sdlEvent);

    // Moves the texture
    void move(double timeStep);

    // Shows the texture on the screen
    void render();

    // Sets the position of this texture (0,0 is the top left)
    void setPosX(double posX);
    void setPosY(double posY);

    // Gets the position of this texture (0,0 is the top left)
    double getPosX();
    double getPosY();

private:
    double _posX, _posY;
    double _velX, _velY;

    // The dimensions of the texture
    int _textureWidth = 20;
    int _textureHeight = 20;

    // Maximum axis velocity of the texture
    int _velocity = 200;

    // Scene textures
    class MGDTexture* _texture;

    const char* _path;
};

#endif // MGD_MovableTexture_h_
