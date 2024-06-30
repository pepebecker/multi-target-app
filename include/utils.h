#ifndef __UTILS_H__
#define __UTILS_H__

double screenToNormalized(double x, double range);
double normalizedToScreen(double x, double range);
void calculateReflection(double vx, double vy, double x, double y, double *reflected_vx, double *reflected_vy);

#endif
