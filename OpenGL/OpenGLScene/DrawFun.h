#ifndef _DRAW_FUN_H_
#define _DRAW_FUN_H_

#define PI		3.1415926535897932384626433832795	// 4 * atan(1 (rad)) 


void DrawCircle(float fCX, float fCY, float fRadius, int iSegments);
void DrawConcCircles(float fCX, float fCY, float finRadius, float fInc, int iNofCircles);
void DrawArc(float fCX, float fCY, float fRadius, float fStartAngleDeg, float fArcAngleDeg, int iSegments);
void DrawCube(float fCX, float fCY, float fCZ, float fSide);
void DrawColoredCube(float fCX, float fCY, float fCZ, float fSide);
void DrawSphere(double dRadius, int iSlices, int iStacks);
void DrawSolarSystem();

#endif // _DRAW_FUN_H_
