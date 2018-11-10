// DrawFun.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGLScene.h"
#include "DrawFun.h"

void DrawLine(Point P1, Point P2, float fLineWidth)
{
	glLineWidth(fLineWidth);

	glBegin(GL_LINES);

		glVertex3f(P1.x, P1.y, P1.z);
		glVertex3f(P2.x, P2.y, P2.z);

	glEnd();
	glLineWidth(1.0);
}

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

void DrawDisc(float fCX, float fCY, float fRadius, int iSegments)
{
	int iSegmentNo = 0;
	float ftempX = 0;

	// initialize @ zero degree
	float fX = fRadius;
	float fY = 0;

	float fThetaRad = (float) ((2 * PI ) / iSegments);
	float fSinTheta = (float) sin(fThetaRad);
	float fCosTheta = (float) cos(fThetaRad);

	glBegin(GL_POLYGON);

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
	gluDeleteQuadric(pSphere);
}

void DrawTriangle(float fBase, float fHeight)
{
	glBegin(GL_TRIANGLES);
		glVertex3f(-(fBase /2), 0.0f, 0.0f);
		glVertex3f((fBase /2), 0.0f, 0.0f);
		glVertex3f(0.0f, fHeight, 0.0f);
	glEnd();
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
	//TRACE0(Msg);

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

void DrawClock(int iSecHandMode)
{
	static float fTheta = 0;
	static int iIsOffSetSet = false; 
	static float fHourHndOffset = 0;
	static float fMinOHndffset = 0;
	static float fSecHndOffset = 0;
	static int iSyncCount = 0;
	
	if(!iIsOffSetSet)
	{
		SYSTEMTIME Curtime = {0};
		GetLocalTime(&Curtime);
		
		//Curtime.wHour = 6;
		//Curtime.wMinute = 30;
		//Curtime.wSecond = 0;

		fHourHndOffset = ( ((Curtime.wHour % 12) * -30.0f) + ((Curtime.wMinute * -30.0f) / 60.0f) ); 
		fMinOHndffset = ((Curtime.wMinute * -6.0f));
		fSecHndOffset = (Curtime.wSecond * -6.0f);

		iIsOffSetSet = true;
	}

	// draw base disc
	glColor3f(0.4f, 0.4f, 0.4f);
	DrawDisc(0, 0, 1.0, 100);

	// draw outline
	glLineWidth(2.5);
	glColor3f(1.0f, 1.0f, 1.0f);
	DrawCircle(0, 0, 1, 100);
	glLineWidth(1.0);

	// draw hour and minute markings
	DrawClockMarking();
	
	// draw hour hand
	glPushMatrix();
		glColor3f(0.9, 0.0, 0.0f);
		glRotatef((fTheta / 3600.0f) + fHourHndOffset, 0, 0, 1);
		DrawTriangle(0.1, 0.60);
	glPopMatrix();

	// draw minute hand
	glPushMatrix();
		glColor3f(0.7, 0.2, 0.2f);
		glRotatef((fTheta / 60.0f) + fMinOHndffset, 0, 0, 1);
		DrawTriangle(0.075, 0.9);
	glPopMatrix();

	// draw second hand
	glPushMatrix();
		glColor3f(1.0, 1.0, 1.0f);
		glRotatef(fTheta + fSecHndOffset, 0, 0, 1);
		DrawTriangle(0.05, 0.95);
	glPopMatrix();

	if(iSecHandMode == SEC_HAND_CONTINUOUS)
	{
		if(iSyncCount >= 64)
		{
			iSyncCount = 0;
			fTheta = 0;
			iIsOffSetSet = false;
		}
		else
		{
			iSyncCount++;
		}

		fTheta -= (3.0f / 32.0f);
	}
	else
	{
		iIsOffSetSet = false;
	}
}

void DrawClockMarking()
{
	Point p1, p2;
	float fLineLen = 0.1;
	float fRadius = 1.0;
	int iIndex = 0;
	

	for(iIndex = 0; iIndex < 12; iIndex++)
	{
		p1.SetPoint((fRadius * cos(2 * PI * iIndex / 12)), (fRadius * sin(2 * PI * iIndex / 12)), 0);
		p2.SetPoint(((fRadius - fLineLen) * cos(2 * PI * iIndex / 12)), ((fRadius - fLineLen) * sin(2 * PI * iIndex / 12)), 0);

		DrawLine(p1, p2, 2.0);
	}
	
	fLineLen = 0.04;
	fRadius = 0.97;
	for(iIndex = 0; iIndex < 60; iIndex++)
	{
		p1.SetPoint((fRadius * cos(2 * PI * iIndex / 60)), (fRadius * sin(2 * PI * iIndex / 60)), 0);
		p2.SetPoint(((fRadius - fLineLen) * cos(2 * PI * iIndex / 60)), ((fRadius - fLineLen) * sin(2 * PI * iIndex / 60)), 0);

		DrawLine(p1, p2, 1.0);
	}
}
