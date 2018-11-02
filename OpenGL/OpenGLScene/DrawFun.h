#ifndef _DRAW_FUN_H_
#define _DRAW_FUN_H_

#define PI		3.1415926535897932384626433832795	// 4 * atan(1 (rad)) 
#define SUN_RADIUS_OFFSET	10

//#define NORMALIZE_RGB(R,G,B)		(R/255.0f),(G/255.0f),(B/255.0f)

// colors
#define RGB_WHITE					(255 / 255.0f), (255 / 255.0f), (255 / 255.0f)
#define RGB_DARK_GREY				(169 / 255.0f), (169 / 255.0f), (169 / 255.0f)
#define RGB_REDDISH_BROWN			(29 / 255.0f), (17 / 255.0f), (17 / 255.0f)
#define RGB_SKY_BLUE				(0 / 255.0f), (183/ 255.0f), (239 / 255.0f)
#define RGB_RUST					(183 / 255.0f), (65/ 255.0f), (14 / 255.0f)
#define RGB_BROWN					(165 / 255.0f), (42/ 255.0f), (42 / 255.0f)
#define RGB_PALE_BLUE				(30 / 255.0f), (144/ 255.0f), (255 / 255.0f)
#define RGB_AZURE_BLUE				(0 / 255.0f), (127/ 255.0f), (255 / 255.0f)
#define RGB_MAROON					(128 / 255.0f), (0 / 255.0f), (0 / 255.0f)
#define RGB_LIGHT_ORANGE			(255 / 255.0f), (160 / 255.0f), (122 / 255.0f)

#if 0
	// planet scalling factors with respect to sun
	#define SF_MERCURY				(1.0f / 80.0f)
	#define SF_VENUS				(1.0f / 50.0f)
	#define SF_EARTH				(1.0f / 50.0f)
	#define SF_MARS					(1.0f / 55.0f)
	#define SF_JUPITER				(1.0f / 10.0f)
	#define SF_SATURN				(1.0f / 12.0f)
	#define SF_URANUS				(1.0f / 30.0f)
	#define SF_NEPTUNE				(1.0f / 35.0f)
	#define SF_PLUTO				(1.0f / 90.0f)
	#define SF_MOON					(1.0f / 90.0f)

#else
	// planet scalling factors with respect to sun
	#define SF_DEFAULT				(1.0f / 5.0f)
	#define SF_MERCURY				SF_DEFAULT
	#define SF_VENUS				SF_DEFAULT
	#define SF_EARTH				SF_DEFAULT
	#define SF_MARS					SF_DEFAULT
	#define SF_JUPITER				SF_DEFAULT
	#define SF_SATURN				SF_DEFAULT
	#define SF_URANUS				SF_DEFAULT
	#define SF_NEPTUNE				SF_DEFAULT
	#define SF_PLUTO				SF_DEFAULT
	#define SF_MOON					(SF_DEFAULT / 3)
#endif

void DrawCircle(float fCX, float fCY, float fRadius, int iSegments);
void DrawConcCircles(float fCX, float fCY, float finRadius, float fInc, int iNofCircles);
void DrawArc(float fCX, float fCY, float fRadius, float fStartAngleDeg, float fArcAngleDeg, int iSegments);
void DrawCube(float fCX, float fCY, float fCZ, float fSide);
void DrawColoredCube(float fCX, float fCY, float fCZ, float fSide);
void DrawSphere(double dRadius, int iSlices, int iStacks);
void DrawSolarSystem();

#endif // _DRAW_FUN_H_
