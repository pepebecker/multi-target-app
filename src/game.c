#include "game.h"
#include "utils.h"

#define COUNT(x) (sizeof(x) / sizeof(x[0]))

#define WINDOW_WIDTH 640.0f
#define WINDOW_HEIGHT 640.0f

#define WINDOW_CENTER_X (WINDOW_WIDTH / 2)
#define WINDOW_CENTER_Y (WINDOW_HEIGHT / 2)

typedef struct {
    double x, y;
    double w, h;
    double dx, dy;
} Player;

uint8_t playerCount = 0;
Player players[1000];

void addPlayer(Player *player) {
  players[playerCount++] = *player;
}

void updatePlayer(Player *player, float delta) {
  player->x += delta * player->dx;
  player->y += delta * player->dy;

  float px2 = player->x * player->x;
  float py2 = player->y * player->y;
  float dist = sqrt(px2 + py2);

  if (dist >= 0.9) {
    player->x -= delta * player->dx;
    player->y -= delta * player->dy;

    double rx = player->x + ((getRandom() - 0.5) * 0.1);
    double ry = player->y + ((getRandom() - 0.5) * 0.1);
    calculateReflection(player->dx, player->dy, rx, ry, &player->dx, &player->dy);
  }
}

void update(float delta) {
  for (int i = 0; i < COUNT(players); i++) {
    updatePlayer(&players[i], delta);
  }
}

void renderPlayer(Player *player) {
  float screenX = normalizedToScreen(player->x, WINDOW_WIDTH);
  float screenY = normalizedToScreen(player->y, WINDOW_HEIGHT);
  fillCircle(screenX, screenY, player->w / 2);
}

void render() {
  setDrawColor(0, 0, 0, 255);
  clearScreen();

  setDrawColor(255, 255, 0, 255);
  fillCircle(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH / 2);

  setDrawColor(255, 0, 0, 255);
  for (int i = 0; i < COUNT(players); i++) {
    renderPlayer(&players[i]);
  }
}

void gameLoop(float delta) {
  update(delta);
  render();
}

void onClick(int x, int y) {
  float nx = screenToNormalized(x, WINDOW_WIDTH);
  float ny = screenToNormalized(y, WINDOW_HEIGHT);
  float dist = sqrt(nx * nx + ny * ny);
  if (dist > 0.9) return;

  double dx = (getRandom() - 0.5) * 2;
  double dy = (getRandom() - 0.5) * 2;

  double mag = sqrt(dx * dx + dy * dy);
  dx /= mag;
  dy /= mag;

  addPlayer(&(Player){
    .x = nx,
    .y = ny,
    .w = 64,
    .h = 64,
    .dx = dx * 0.0007f,
    .dy = dy * 0.0007f,
  });
}

void onQuit() {
  destroyWindow();
}

void start() {
  init();
  createWindow("Pepe's Game", WINDOW_WIDTH, WINDOW_HEIGHT);
  setOnClick(onClick);
  onClick(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
  onClick(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
  onClick(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
  runGameLoop(gameLoop, onQuit);
}
