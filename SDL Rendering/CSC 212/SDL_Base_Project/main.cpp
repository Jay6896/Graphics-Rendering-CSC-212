#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("SDL3 Test", 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    SDL_Surface* surface = IMG_Load("/Users/Jamil/Documents/SDL_Base_Project2/SDL_Base_Project/FiverrPFPLarger.png"); // Loads the image
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface); // creates a texture params are name of renderer and name of surface
    SDL_Surface* surface2 = IMG_Load("/Users/Jamil/Documents/SDL_Base_Project2/SDL_Base_Project/hair.gif"); // SECOND IMAGE
    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, surface2); // creates a texture params are name of renderer and name of surface

    SDL_DestroySurface(surface);  // destroys the surface

    SDL_FRect imgrect = { 200, 100, 200, 200 }; // the shape of the rect, params are x,y,width and height
    SDL_FRect imgrect2 = { 400, 100, 200, 200 };

    SDL_Event event;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) running = false;
        }

        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, texture, NULL, &imgrect); // clears, params are the name of the renderer, name of texture, takes a shape rect where the input would be displayed. It can be null, outputs the image inside the shape rect. It can be null
        SDL_RenderTexture(renderer, texture2, NULL, &imgrect2); // SECOND RENDERER
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}