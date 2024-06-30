#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
#include "SDL2/SDL_video.h"
#include <SDL2/SDL2_gfxPrimitives.h>

#include "color.h"
#include "game.h"

SDL_Window* window;
SDL_Renderer* renderer;
Color color = {0, 0, 0, 0};

void (*onClickCallback)(int x, int y) = NULL;

void println(const char* message) {
  printf("%s\n", message);
}

void initialize_random() {
    srand((unsigned int)time(NULL));
}

double getRandom() {
    return (double)rand() / (double)RAND_MAX;
}

void init() {
  initialize_random();
  SDL_Init(SDL_INIT_VIDEO);
  SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "0" );
}

void createWindow(const char* title, int32_t width, int32_t height) {
  window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void runGameLoop(void (*gameLoop)(float), void (*onComplete)()) {
  Uint64 NOW = SDL_GetPerformanceCounter();
  Uint64 LAST = 0;
  SDL_Event event;
  while (1) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        onComplete();
        return;
      }
      if (event.type == SDL_MOUSEBUTTONDOWN) {
        onClickCallback(event.button.x, event.button.y);
      }
    }

    LAST = NOW;
    NOW = SDL_GetPerformanceCounter();

    double deltaTime = (double)((NOW - LAST)*1000 / (double)SDL_GetPerformanceFrequency());

    gameLoop(deltaTime);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000 / 60);
  }
  onComplete();
}

void setDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  color = (Color){r, g, b, a};
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void clearScreen() {
  SDL_RenderClear(renderer);
}

void drawRect(int32_t x, int32_t y, int32_t width, int32_t height) {
  SDL_Rect rect = { x, y, width, height };
  SDL_RenderDrawRect(renderer, &rect);
}

void fillRect(int32_t x, int32_t y, int32_t width, int32_t height) {
  SDL_Rect rect = { x, y, width, height };
  SDL_RenderFillRect(renderer, &rect);
}

void drawCircle(int32_t x, int32_t y, int32_t r) {
  aaellipseRGBA(renderer, x, y-1, r-1, r-2, color.r, color.g, color.b, color.a);
  aacircleRGBA(renderer, x, y-1, r-2, color.r, color.g, color.b, color.a);
}

void fillCircle(int32_t x, int32_t y, int32_t r) {
  drawCircle(x, y, r);
  filledCircleColor(renderer, x, y-1, r-2, convert_color_to_uint32(color));
}

void destroyWindow() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

void quit() {
  SDL_Quit();
  exit(0);
}

void setOnClick(void (*onClick)(int x, int y)) {
  onClickCallback = onClick;
}

int main(int argc, char **argv) {
  start();
  return 0;
}
