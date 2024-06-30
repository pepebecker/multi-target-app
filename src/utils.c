#include "game.h"

double screenToNormalized(double x, double range) {
  return (2 * x / range) - 1.0;
}

double normalizedToScreen(double x, double range) {
  return (x + 1) * range / 2;
}

void calculateReflection(double vx, double vy, double x, double y, double *reflected_vx, double *reflected_vy) {
    double normal_magnitude = sqrt(x * x + y * y);
    double nx = x / normal_magnitude;
    double ny = y / normal_magnitude;

    double dot_product = vx * nx + vy * ny;
    
    *reflected_vx = vx - 2 * dot_product * nx;
    *reflected_vy = vy - 2 * dot_product * ny;
}
