#include <iostream>
#include <SDL.h>

#define WIDTH 1280
#define HEIGHT 720

bool running, fullscreen;

SDL_Renderer* renderer;
SDL_Window* window;

int frameCount, timerFps, lastFrame, fps;

void update() {
    if (fullscreen) {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    } else {
        SDL_SetWindowFullscreen(window, 0);
    }
};

void input() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            running = false;
        }
    }

    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    if (keystates[SDL_SCANCODE_ESCAPE]) {
        running = false;
    }
    if (keystates[SDL_SCANCODE_F11]) {
        fullscreen = !fullscreen;
    }
}

void draw() {
    SDL_SetRenderDrawColor(renderer, 40, 43, 200, 255);
    SDL_Rect rect;
    rect.x = rect.y= 0;
    rect.w = WIDTH;
    rect.h = HEIGHT;
    SDL_RenderFillRect(renderer, &rect);

    frameCount++;
    timerFps = SDL_GetTicks() - lastFrame;
    if (timerFps < (1000/60)) {
        SDL_Delay((1000/60) - timerFps);
    }

    SDL_RenderPresent(renderer);
}

int main(int argc, char* args[]) {
    running = true;
    fullscreen = false;
    static int lastTime = 0;

    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        std::cout << "Failed at SDL_Init()" << std::endl;
    }

    if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) < 0) {
        std::cout << "Failed at SDL_CreateWindowAndRenderer()" << std::endl;
    }

    SDL_SetWindowTitle(window, "SPIC Poc with physcis");
    SDL_ShowCursor(0);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

    while (running) {
        lastFrame = SDL_GetTicks();
        if (lastFrame >= (lastTime + 1000)) {
            lastTime = lastFrame;
            fps = frameCount;
            frameCount = 0;
        }

        std::cout << fps << std::endl;

        update();
        input();
        draw();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
