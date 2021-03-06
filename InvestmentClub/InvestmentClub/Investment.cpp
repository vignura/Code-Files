// InvestmentClub.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Member.h"
#include "InvestmentClub.h"

int main()
{
	int iMemCount = 0;
	float fMthContrib = 0;
	float fRatePA = 0;
	char Name[64] = { 0 };

	printf("Investment Club Simulation\n");

#if 0
	printf("Enter no of members: ");
	scanf("%d", &iMemCount);

	printf("Enter monthly contribution: ");
	scanf("%f", &fMthContrib);

	printf("Enter club intrest rate (% per Annum): ");
	scanf("%f", &fRatePA);

#else

	iMemCount = 10;
	fMthContrib = 500;
	fRatePA = 12;

#endif

	// create a club
	InvestmentClub IC(fRatePA, fMthContrib);

	// add members
	for (int iCount = 0; iCount < iMemCount; iCount++)
	{
		sprintf_s(Name, sizeof(Name), "Member-%d", (iCount + 1));
		IC.addMember(Name);
	}

	// run simulation
	IC.Run(120);

	getchar();
	return 0;
}
