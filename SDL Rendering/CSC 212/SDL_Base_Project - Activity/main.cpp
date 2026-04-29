#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("SDL3 Test", 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    SDL_Surface* surface = IMG_Load("/Users/Jamil/Documents/Graphics-Rendering-COS-212/SDL Rendering/CSC 212/SDL_Base_Project - Activity/white_square.png"); // SECOND IMAGE
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface); // creates a texture params are name of renderer and name of surface

    SDL_DestroySurface(surface);  // destroys the surface

    SDL_FRect imgrect = { 325, 45, 140, 140 }; // the shape of the rect, params are x,y,width and height
    SDL_FRect imgrect2 = { 325, 345, 140, 140 };
    SDL_FRect imgrect3 = { 165, 195, 140, 140 };
    SDL_FRect imgrect4 = { 486, 190, 140, 140 };


    SDL_Event event;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) running = false;
        }

        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, texture, NULL, &imgrect); // clears, params are the name of the renderer, name of texture, takes a shape rect where the input would be displayed. It can be null, outputs the image inside the shape rect. It can be null
        SDL_RenderTexture(renderer, texture, NULL, &imgrect2); // SECOND RENDERER
        SDL_RenderTexture(renderer, texture, NULL, &imgrect3);
        SDL_RenderTexture(renderer, texture, NULL, &imgrect4);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}