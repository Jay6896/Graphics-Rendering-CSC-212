#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO); //Initialize SDL
	// SDL windows
	SDL_Window* window = SDL_CreateWindow("My window", 800, 600, SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE); // Creation and Specifications of an SDL window. Uses a pointer reference and has 4 params, 1st is window name, second is width, third is height and last is a flag (different settings for the window)
	/* flags included are in module 2.1 and include SDL_WINDOW_FULLSCREEN, SDL_WINDOW_BORDERLESS, SDL_WINDOW_RESIZABLE
		there can be multiple flags*/ 

	// SDL renderers
	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL); // Creation and Specifications of an SDL renderer. 2 params being a window and a character (usually NULL)
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // for setting colour, 5 params which are first is renderer, second is red colour (max 255), third is green colour (max 255), fourth is blue colour (max 255), last is opacity
	SDL_RenderClear(renderer);

	// NOTE: THE while(running) IS NECESSARY FOR ANY RENDERER TO CONTINUE RUNNING

	// Rendering one pixel at a single point
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderPoint(renderer, 400.0f, 300.0f);

	// Rendering MULTIPLE points, first value contains the x coord, second value is y coord
	SDL_FPoint point[] = {
		{400.0f, 300.0f}, // 400.0f is the x coord, 300.0 is the y coord
		{400.0f, 310.0f},
		{400.0f, 320.0f},
		{400.0f, 330.0f},
		{400.0f, 340.0f},
	};
	SDL_RenderPoints(renderer, point, 5); // renders multiple points, first arg is renderer name, second is the array holding the points, third is amount of points to be rendered
	
	/* Rendering individual lines
	// Line rendering first param is x1, second is y1, third is x2, fourth is y2
	//Line 1: L-R Diagonal
	SDL_RenderLine(renderer, 0.0f, 0.0f, 800.0f, 600.0f);
	//Line 2: R-L Diagonal
	SDL_RenderLine(renderer, 0.0f, 600.0f, 800.0f, 0.0f);
	//Line 3: Top to Bottom
	SDL_RenderLine(renderer, 400.0f, 0.0f, 400.0f, 600.0f);
	//Line 4: Bottom to Top
	SDL_RenderLine(renderer, 0.0f, 300.0f, 800.0f, 300.0f);
	*/

	// Rendering multiple lines
	SDL_FPoint lines[]{
		{200.0f, 200.0f},
		{400.0f, 200.0f},
		{400.0f, 400.0f},
		{200.0f, 400.0f},
		{200.0f, 200.0f}
	};

	/* NOTE, FOR A TRIANGLE, WE MUST SET THE LAST POINT AS THE ORIGINAL POINT, AND THE COUNT TO 4
	SDL_FPoint lines[]{
		{400.0f, 200.0f},
		{600.0f, 400.0f},
		{200.0f, 400.0f},
		{400.0f, 200.0f}
	};
	*/


	// Renders lines based off the points
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // colour of the renderer
	SDL_RenderLines(renderer, lines, 5); // the last param is the count value, it must be above the total amount of lines you want to see i.e 5 = 4 lines
	SDL_RenderPresent(renderer);

	SDL_Event event;
	bool running = true;



	// Renders shapes based off coord range as an outline
	SDL_FRect rect = { 400.0f, 300.0f, 200.0f, 100.0f };
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderRect(renderer, &rect);

	// Renders shapes based off coord range as outline WITH a colour fill
	SDL_FRect rect2 = { 600.0f, 500.0f, 400.0f, 300.0f };
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &rect2); // what fills the outline

	// Animation of rects, it renders a new rectangle over every second
	// Points needed for the actual movement in the animation
	float rectx = 0.0f; // x coord
	float recty = 250.0f; // y coord
	float rectx2 = 800.0f;
	float recty2 = 250.0f;

	float speed = 900.0f; 

	Uint64 lastTime = SDL_GetTicks();

	// Event system for animation
	/*For Rendering Moving Rects*/
	while (running)
	{
		Uint64 currentTime = SDL_GetTicks(); // This function calculates the number of milliseconds that have passed since SDL was initialized

		float deltaTime = (currentTime - lastTime) / 1000.0f; // The difference between the last time and the last time divided by 1000 (to convert to seconds)

		lastTime = currentTime; // used to update the time over the next running seconds

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				running = false;
			}
		}

		const bool* keys = SDL_GetKeyboardState(NULL);
		if(keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D])
		{
			rectx += speed * deltaTime; // adds points in the x direction and re renders the rect
		}
		if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A])
		{
			rectx -= speed * deltaTime;
		}
		if (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W])
		{
			recty -= speed * deltaTime;
		}
		if (keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S])
		{
			recty += speed * deltaTime;
		}

		if (rectx >= 800)
		{
			rectx = 0; // makes the rect loop back to its original position
		}

		if (recty >= 600)
		{
			recty = 0;
		}

		SDL_FRect rect = { rectx, recty, 100, 100 }; // the structure of the rectangle. Consists of the coordinates and the width and height of the rectangle
		SDL_FRect rect2 = { rectx2, recty2, 100, 100 };
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // colour of the renderer
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // colour of the rect
		SDL_RenderFillRect(renderer, &rect);
		SDL_RenderPresent(renderer);
	}



	// Shape rendering
	SDL_FRect square = { 10.0f, 20.0f, 30.0f, 40.0f };
	SDL_RenderFillRect(renderer, &square);

	SDL_RenderPresent(renderer); // What actually renders the renderer. Is used to present the renderer

	// Event system 
	//SDL_Event event;
	//bool running = true;

	//while(running)
	//{
	//	while(SDL_PollEvent(&event)) // checks for event changes
	//	{
	//		if (event.type == SDL_EVENT_QUIT) // runs when the close button is pressed in the window, closes the window
	//		{
	//			running = false;
	//		}

	//		if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) // runs when the escape button is pressed in the window, closes the window
	//		{
	//			running = false;
	//		}
	//	}
	//}
	
	//SDL_Delay(3000); // For how long the window would be displayed, in milliseconds

	SDL_DestroyWindow(window); // To destroy the window
	SDL_DestroyRenderer(renderer); // To destroy the renderer

	SDL_Quit(); // To quit SDL

	return 0; // Necessary to return something
}