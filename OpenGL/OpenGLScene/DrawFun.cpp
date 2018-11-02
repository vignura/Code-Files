// DrawFun.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGLScene.h"
#include "DrawFun.h"


void DrawCircle(float fCX, float fCY, float fRadius, int iSegments)
{
	int iSegmentNo = 0;
	float ftempX = 0;

	// initialize @ zero degree
	float fX = fRadius;
	float fY = 0;

	float fThetaRad = (float) ((2 * PI ) / iSegments);
	float fSinTheta = (float) sin(fThetaRad);
	float fCosTheta = (float) cos(fThetaRad);

	glBegin(GL_LINE_LOOP);

		for(iSegmentNo = 0; iSegmentNo < iSegments; iSegmentNo++)
		{
			glVertex2f((fCX + fX), (fCY + fY));	 

			// apply rotation 
			ftempX = fX;
			fX = (ftempX * fCosTheta) - (fY * fSinTheta);
			fY = (ftempX * fSinTheta) + (fY * fCosTheta);
		}

	glEnd();
}

void DrawConcCircles(float fCX, float fCY, float finRadius, float fInc, int iNofCircles)
{
	int iCount = 0;
	float fRadius = finRadius;
	int iSegments = 100;

	for(iCount = 0; iCount < iNofCircles; iCount++)
	{
		DrawCircle(fCX, fCY, fRadius, iSegments);
		
		// increment the radius
		fRadius += fInc;

		// adjust the segment count
		//iSegments = (int) (iSegments * fRadius * (fRadius / (fRadius - fInc)));
	}
}

void DrawArc(float fCX, float fCY, float fRadius, float fStartAngleDeg, float fArcAngleDeg, int iSegments)
{
	int iSegmentNo = 0;
	float ftempX = 0;

	// initialize @ zero degree
	float fX = (float) (fRadius * cos(fStartAngleDeg * PI / 180));
	float fY = (float) (fRadius * sin(fStartAngleDeg * PI / 180));

	float fThetaRad = (float) (((fArcAngleDeg * PI) / 180) / iSegments);
	float fSinTheta = (float) sin(fThetaRad);
	float fCosTheta = (float) cos(fThetaRad);

	glBegin(GL_LINE_STRIP);

		for(iSegmentNo = 0; iSegmentNo < iSegments; iSegmentNo++)
		{
			glVertex2f((fCX + fX), (fCY + fY));	 

			// apply rotation 
			ftempX = fX;
			fX = (ftempX * fCosTheta) - (fY * fSinTheta);
			fY = (ftempX * fSinTheta) + (fY * fCosTheta);
		}

	glEnd();
}


void DrawCube(float fCX, float fCY, float fCZ, float fSide)
{
	float fHalfSide = fSide / 2;
	glBegin(GL_QUADS);
		
		// Top Side
		glVertex3f((fCX + fHalfSide), (fCY + fHalfSide), (fCZ + fHalfSide));
		glVertex3f((fCX + fHalfSide), (fCY + fHalfSide), (fCZ - fHalfSide));
		glVertex3f((fCX - fHalfSide), (fCY + fHalfSide), (fCZ - fHalfSide));
		glVertex3f((fCX - fHalfSide), (fCY + fHalfSide), (fCZ + fHalfSide));

		// Bottom Side
		glVertex3f((fCX - fHalfSide), (fCY - fHalfSide), (fCZ - fHalfSide));
		glVertex3f((fCX + fHalfSide), (fCY - fHalfSide), (fCZ - fHalfSide));
		glVertex3f((fCX + fHalfSide), (fCY - fHalfSide), (fCZ + fHalfSide));
		glVertex3f((fCX - fHalfSide), (fCY - fHalfSide), (fCZ + fHalfSide));
		
		// Front Side
		glVertex3f((fCX + fHalfSide), (fCY + fHalfSide), (fCZ + fHalfSide));
		glVertex3f((fCX - fHalfSide), (fCY + fHalfSide), (fCZ + fHalfSide));
		glVertex3f((fCX - fHalfSide), (fCY - fHalfSide), (fCZ + fHalfSide));
		glVertex3f((fCX + fHalfSide), (fCY - fHalfSide), (fCZ + fHalfSide));
		
		// Back Side
		glVertex3f((fCX - fHalfSide), (fCY - fHalfSide), (fCZ - fHalfSide));
		glVertex3f((fCX - fHalfSide), (fCY + fHalfSide), (fCZ - fHalfSide));
		glVertex3f((fCX + fHalfSide), (fCY + fHalfSide), (fCZ - fHalfSide));
		glVertex3f((fCX + fHalfSide), (fCY - fHalfSide), (fCZ - fHalfSide));
		
		// Left Side
		glVertex3f((fCX - fHalfSide), (fCY - fHalfSide), (fCZ - fHalfSide));
		glVertex3f((fCX - fHalfSide), (fCY - fHalfSide), (fCZ + fHalfSide));
		glVertex3f((fCX - fHalfSide), (fCY + fHalfSide), (fCZ + fHalfSide));
		glVertex3f((fCX - fHalfSide), (fCY + fHalfSide), (fCZ - fHalfSide));

		// Right Side
		glVertex3f((fCX + fHalfSide), (fCY + fHalfSide), (fCZ + fHalfSide));
		glVertex3f((fCX + fHalfSide), (fCY - fHalfSide), (fCZ + fHalfSide));
		glVertex3f((fCX + fHalfSide), (fCY - fHalfSide), (fCZ - fHalfSide));
		glVertex3f((fCX + fHalfSide), (fCY + fHalfSide), (fCZ - fHalfSide));

	glEnd();
}

void DrawColoredCube(float fCX, float fCY, float fCZ, float fSide)
{
	float fHalfSide = fSide / 2;
	glBegin(GL_QUADS);
		
		// Top Side
		glColor3f(1.0, 0, 0);
		glVertex3f((fCX + fHalfSide), (fCY + fHalfSide), (fCZ + fHalfSide));
		glVertex3f((fCX + fHalfSide), (fCY + fHalfSide), (fCZ - fHalfSide));
		glVertex3f((fCX - fHalfSide), (fCY + fHalfSide), (fCZ - fHalfSide));
		glVertex3f((fCX - fHalfSide), (fCY + fHalfSide), (fCZ + fHalfSide));

		// Bottom Side
		glColor3f(0, 1.0, 0);
		glVertex3f((fCX - fHalfSide), (fCY - fHalfSide), (fCZ - fHalfSide));
		glVertex3f((fCX + fHalfSide), (fCY - fHalfSide), (fCZ - fHalfSide));
		glVertex3f((fCX + fHalfSide), (fCY - fHalfSide), (fCZ + fHalfSide));
		glVertex3f((fCX - fHalfSide), (fCY - fHalfSide), (fCZ + fHalfSide));
		
		// Front Side
		glColor3f(0, 0, 1.0);
		glVertex3f((fCX + fHalfSide), (fCY + fHalfSide), (fCZ + fHalfSide));
		glVertex3f((fCX - fHalfSide), (fCY + fHalfSide), (fCZ + fHalfSide));
		glVertex3f((fCX - fHalfSide), (fCY - fHalfSide), (fCZ + fHalfSide));
		glVertex3f((fCX + fHalfSide), (fCY - fHalfSide), (fCZ + fHalfSide));
		
		// Back Side
		glColor3f(0, 1.0, 1.0);
		glVertex3f((fCX - fHalfSide), (fCY - fHalfSide), (fCZ - fHalfSide));
		glVertex3f((fCX - fHalfSide), (fCY + fHalfSide), (fCZ - fHalfSide));
		glVertex3f((fCX + fHalfSide), (fCY + fHalfSide), (fCZ - fHalfSide));
		glVertex3f((fCX + fHalfSide), (fCY - fHalfSide), (fCZ - fHalfSide));
		
		// Left Side
		glColor3f(1.0, 1.0, 0);
		glVertex3f((fCX - fHalfSide), (fCY - fHalfSide), (fCZ - fHalfSide));
		glVertex3f((fCX - fHalfSide), (fCY - fHalfSide), (fCZ + fHalfSide));
		glVertex3f((fCX - fHalfSide), (fCY + fHalfSide), (fCZ + fHalfSide));
		glVertex3f((fCX - fHalfSide), (fCY + fHalfSide), (fCZ - fHalfSide));

		// Right Side
		glColor3f(1.0, 0, 1.0);
		glVertex3f((fCX + fHalfSide), (fCY + fHalfSide), (fCZ + fHalfSide));
		glVertex3f((fCX + fHalfSide), (fCY - fHalfSide), (fCZ + fHalfSide));
		glVertex3f((fCX + fHalfSide), (fCY - fHalfSide), (fCZ - fHalfSide));
		glVertex3f((fCX + fHalfSide), (fCY + fHalfSide), (fCZ - fHalfSide));

	glEnd();
}


void DrawSphere(double dRadius, int iSlices, int iStacks)
{
	GLUquadric *pSphere = gluNewQuadric();
	gluSphere(pSphere, dRadius, iSlices, iStacks);
}


void DrawSolarSystem()
{
	float fInc = 0.25;
	float fStartRadius = 0.5;
	float fRadius = 0.5;
	float fSunRadius = 0.25;
	static float fTheta = 0;
	static float fSunRadiusOffset = -SUN_RADIUS_OFFSET;
	static int iSign = 1;
	float foffset = (2 * PI / 5);
	CString Msg = "";
	
	// sun
	glColor3f((253 / 255.0f), (184/ 255.0f), (19 / 255.0f));
	DrawSphere(fSunRadius, 30 + fSunRadiusOffset, 30 + fSunRadiusOffset);
	
	
	if(fSunRadiusOffset > SUN_RADIUS_OFFSET)
	{
		fSunRadiusOffset = SUN_RADIUS_OFFSET;
		iSign *= -1;
	}
	else if(fSunRadiusOffset < -SUN_RADIUS_OFFSET)
	{
		fSunRadiusOffset = -SUN_RADIUS_OFFSET;
		iSign *= -1;
	}
	else
	{
		fSunRadiusOffset += ((float)iSign * 0.1);
	}
	
	Msg.Format("fSunRadiusOffset: %f\tiSign: %d\n", fSunRadiusOffset, iSign);
	TRACE0(Msg);

	glColor3f(0.8f, 0.8f, 0.8f);
	DrawConcCircles(0, 0, fStartRadius, fInc, 9);
	
	// draw planets
	// mercury
	glPushMatrix();
		glTranslatef(fRadius * cos(fTheta + foffset), fRadius * sin(fTheta + foffset), 0);
		glColor3f(RGB_DARK_GREY);
		//glColor3f((169 / 255.0f), (169/ 255.0f), (169 / 255.0f));
		DrawSphere((SF_MERCURY * fSunRadius), 50, 50); 
		fRadius += fInc;
		foffset += foffset;
	glPopMatrix();

	// venus
	glPushMatrix();
		glTranslatef(fRadius * cos(fTheta + foffset), fRadius * sin(fTheta + foffset), 0);
		glColor3f(RGB_REDDISH_BROWN);
		DrawSphere((SF_VENUS * fSunRadius), 50, 50); 
		fRadius += fInc;
		foffset += foffset;
	glPopMatrix();
	
	// earth
	glPushMatrix();
		glTranslatef(fRadius * cos(fTheta + foffset), fRadius * sin(fTheta + foffset), 0);
		glColor3f(RGB_SKY_BLUE);
		DrawSphere((SF_EARTH * fSunRadius), 50, 50); 
		fRadius += fInc;
		foffset += foffset;
		
		// draw moon
		glTranslatef(0, ((SF_MOON * fSunRadius) * 10) * cos(fTheta + foffset), ((SF_MOON * fSunRadius) * 10) * sin(fTheta + foffset));
		glColor3f((255 / 255.0f), (255/ 255.0f), (255 / 255.0f));
		DrawSphere((SF_MOON * fSunRadius), 50, 50);

	glPopMatrix();

	// mars
	glPushMatrix();
		glTranslatef(fRadius * cos(fTheta + foffset), fRadius * sin(fTheta + foffset), 0);
		glColor3f(RGB_RUST);
		DrawSphere((SF_MARS * fSunRadius), 50, 50); 
		fRadius += fInc;
		foffset += foffset;
	glPopMatrix();

	// jupiter
	glPushMatrix();
		glTranslatef(fRadius * cos(fTheta + foffset), fRadius * sin(fTheta + foffset), 0);
		glColor3f(RGB_LIGHT_ORANGE);
		DrawSphere((SF_JUPITER * fSunRadius), 50, 50); 
		fRadius += fInc;
		foffset += foffset;
		
		glPushMatrix();
			// draw moon
			glTranslatef(0, ((SF_MOON * fSunRadius) * 10) * cos(fTheta + foffset), ((SF_MOON * fSunRadius) * 10) * sin(fTheta + foffset));
			glColor3f((255 / 255.0f), (255/ 255.0f), (255 / 255.0f));
			DrawSphere((SF_MOON * fSunRadius), 50, 50);
		glPopMatrix();


		glPushMatrix();
			// draw moon
			glTranslatef(0, ((SF_MOON * fSunRadius) * 14) * cos(fTheta + foffset), ((SF_MOON * fSunRadius) * 14) * sin(fTheta + foffset - 10));
			glColor3f((255 / 255.0f), (255/ 255.0f), (255 / 255.0f));
			DrawSphere((SF_MOON * fSunRadius), 50, 50);
		glPopMatrix();

	glPopMatrix();

	// satrun
	glPushMatrix();
		glTranslatef(fRadius * cos(fTheta + foffset), fRadius * sin(fTheta + foffset), 0);
		glColor3f(RGB_BROWN);
		DrawSphere((SF_SATURN * fSunRadius), 50, 50); 
		fRadius += fInc;
		foffset += foffset;

		// draw saturn rings
		glColor3f(RGB_WHITE);
		DrawConcCircles(0, 0, (SF_SATURN * fSunRadius * 1.5), (SF_SATURN * fSunRadius / 50), 20);

		// draw moon
		glTranslatef(0, ((SF_MOON * fSunRadius) * 10) * cos(fTheta + foffset), ((SF_MOON * fSunRadius) * 10) * sin(fTheta + foffset));
		glColor3f((255 / 255.0f), (255/ 255.0f), (255 / 255.0f));
		DrawSphere((SF_MOON * fSunRadius), 50, 50);

	glPopMatrix();



	// uranus
	glPushMatrix();
		glTranslatef(fRadius * cos(fTheta + foffset), fRadius * sin(fTheta + foffset), 0);
		glColor3f(RGB_PALE_BLUE);
		DrawSphere((SF_URANUS * fSunRadius), 50, 50); 
		fRadius += fInc;
		foffset += foffset;

		// draw moon
		glTranslatef(0, ((SF_MOON * fSunRadius) * 10) * cos(fTheta + foffset), ((SF_MOON * fSunRadius) * 10) * sin(fTheta + foffset));
		glColor3f((255 / 255.0f), (255/ 255.0f), (255 / 255.0f));
		DrawSphere((SF_MOON * fSunRadius), 50, 50);

	glPopMatrix();
	
	// neptune
	glPushMatrix();
		glTranslatef(fRadius * cos(fTheta + foffset), fRadius * sin(fTheta + foffset), 0);
		glColor3f(RGB_AZURE_BLUE);
		DrawSphere((SF_NEPTUNE * fSunRadius), 50, 50); 
		fRadius += fInc;
		foffset += foffset;
		
		// draw moon
		glTranslatef(0, ((SF_MOON * fSunRadius) * 10) * cos(fTheta + foffset), ((SF_MOON * fSunRadius) * 10) * sin(fTheta + foffset));
		glColor3f((255 / 255.0f), (255/ 255.0f), (255 / 255.0f));
		DrawSphere((SF_MOON * fSunRadius), 50, 50);

	glPopMatrix();
	
	// pluto
	glPushMatrix();
		glTranslatef(fRadius * cos(fTheta + foffset), fRadius * sin(fTheta + foffset), 0);
		glColor3f(RGB_MAROON);
		DrawSphere((SF_PLUTO * fSunRadius), 50, 50); 
		fRadius += fInc;
		foffset += foffset;
	glPopMatrix();

	fTheta -= 0.01;
}
