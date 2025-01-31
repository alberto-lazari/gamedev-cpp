// All the SDL includes we need
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <cstdio> // Some utilities for the log
#include <memory> // Needed for the smart pointers

#include "Core/MGDMovableTexture.h"
#include "Core/MGDTexture.h"
#include "Core/MGDTimer.h"

#include "Core/MGDMain.hpp" // Used just to hide some extra code

int Main() {
    // Game loop flag
    bool isQuittingGame = false;

    // TEXTURES LOADING, with different type of allocation:
    // The texture that will be moving around on the screen
    MGDMovableTexture dotMovableTexture("Assets/dot.bmp");
    // Other fixed textures
    MGDTexture* backgroundTexture = new MGDTexture("Assets/MissingTexture.bmp");
    std::unique_ptr<MGDTexture> smileTexture(new MGDTexture("Assets/smile.png"));
    std::unique_ptr<MGDTexture> doraemonSpriteSheet(new MGDTexture("Assets/DoraemonSpritesheet.png"));
    MGDTexture* textTexture = new MGDTexture();
    SDL_Color textColor{0x5c, 0x80, 0x01, 0xff}; // a kind of green
    textTexture->loadFromRenderedText("Rendered Text!", textColor);

    // Keeps track of time between steps
    MGDTimer stepTimer;

    // I will add a rotation to the smile
    double smileAngle = 0.0;

    // I will alternate the images in the spreadsheet, so I have to mantain a counter of which image I am using
    constexpr unsigned int spritesNum = 6U;
    constexpr unsigned int spritesheetRowSize = 4U;
    unsigned int spritesheetCurrentColumn = 0U;
    unsigned int spritesheetCurrentRow = 0U;
    unsigned int spriteCurrentIndex = 0U;
    unsigned int nextSpriteCountdown = 0U; // in milliseconds
    constexpr int maxCount = 30000;        // this value is used to restore to 0 the milliseconds count (useful for the movement on the x axis)

    // SDL Event handler
    SDL_Event sdlEvent;

    // ****************** GAME LOOP ************************
    // While application is running
    while (!isQuittingGame) {
        // Handle events on queue
        while (SDL_PollEvent(&sdlEvent) != 0) {
            // User requests quit
            if (sdlEvent.type == SDL_QUIT) {
                isQuittingGame = true;
            }
            // Handle input for the texture
            dotMovableTexture.handleEvent(sdlEvent);
        }

        // User input depends on nothing, so it goes first.
        // Objects being updated depend on the user input, so they go second.
        // Physics depend on the new updated objects, so it goes third.
        // Rendering depends on the latest physics state and object updates, so it goes fourth.
        // UI depends on the scene to already be rendered, so it goes fifth.

        // SETTING THE TIME
        // Get the delta time in milliseconds
        Uint32 deltaTime = stepTimer.getTicks();
        // Calculate the delta time in seconds
        double deltaTimeF = deltaTime * 0.001;
        // Move for time step
        dotMovableTexture.move(deltaTimeF);

        // Restart step timer
        stepTimer.start();

        // Clear screen
        SDL_SetRenderDrawColor(globalRenderer, 0xca, 0xcc, 0x90, 0xFF); // a kind of yellow
        SDL_RenderClear(globalRenderer);

        // TEXTURE RENDERING:
        // Rendering the background
        {
            // The rectDest is a rect which defines the position and the size of the texture
            SDL_Rect rectDest = {180, 280, 320, 200};
            backgroundTexture->renderCopyEx(&rectDest);
            // Alternative Rendering (without scale)
            // backgroundTexture->render(0, 0, NULL, 45, NULL,SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
        }

        // Rendering the smile, using the renderCopyEx function:
        {
            SDL_Rect rectDestination = {0, 0, 180, 150};                                               // this is the rectangle where the smile will be rendered
            SDL_Rect rectClip = {500, 200, smileTexture->getWidth() - 800, smileTexture->getHeight()}; // this is the rectangle that will cut the
            // original loaded texture
            smileTexture->renderCopyEx(&rectDestination, &rectClip, smileAngle);
            smileAngle += 90 * deltaTimeF; // it will rotate by 90 degrees per second
        }

        // Rendering the Doraemon animation, by taking all the frames from the spritesheet texture
        {
            SDL_Rect rectClip = {240 * (int)spritesheetCurrentColumn, 310 * (int)spritesheetCurrentRow, 250, 300};
            doraemonSpriteSheet->render(400, -25, &rectClip);
        }
        // Rendering another Doraemon animation, but moving it to the left and the right
        {
            SDL_Rect rectClip = {240 * (int)spritesheetCurrentColumn, 310 * (int)spritesheetCurrentRow, 250, 300};
            // If the countdown is over the half of its maximum, the sprite will be flipped and the position reduced
            int xInitialPosition = 150;
            SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE;
            int xPosition = xInitialPosition + (nextSpriteCountdown / 50);
            if (nextSpriteCountdown > maxCount / 2) {
                xPosition = xInitialPosition + (maxCount - nextSpriteCountdown) / 50;
                flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
            }
            SDL_Rect rectDest = {xPosition, 160, 100, 125};
            doraemonSpriteSheet->renderCopyEx(&rectDest, &rectClip, 0, NULL, flip);
            // Alternate render version (without sprite scale):
            // doraemonSpriteSheet->render(xPosition, -25, &rectClip, 0, NULL, flip);
        }
        // Sprite calculation to get the right spritesheet row and column:
        nextSpriteCountdown = (nextSpriteCountdown + (deltaTime * 10)) % maxCount; // every 0.1 seconds (1/10) it will change sprite
        spriteCurrentIndex = ((nextSpriteCountdown / 1000)) % spritesNum;
        spritesheetCurrentColumn = spriteCurrentIndex % spritesheetRowSize;
        spritesheetCurrentRow = spriteCurrentIndex / spritesheetRowSize;
        // A log of the indexes of the spritesheet:
        printf("Next Sprite Count: %d, DeltaTime: %d, Current Sprite Index: %d\n", nextSpriteCountdown, deltaTime, spriteCurrentIndex);

        // Rendering the movable dot:
        dotMovableTexture.render();

        // Rendering the text at the center of the screen:
        textTexture->render((SCREEN_WIDTH / 2) - (textTexture->getWidth() / 2), 0);

        // Update screen
        SDL_RenderPresent(globalRenderer);
    }

    // ****************** END GAME LOOP ************************

    // Free resources and close SDL
    delete backgroundTexture;
    delete textTexture;


    return 0;
}
