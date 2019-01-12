#ifndef _INVSETMENT_CLUB_H_
#define _INVSETMENT_CLUB_H_

#include "Member.h"

#define ENABLE_DEBUG			
#define MAX_CLUB_MEMBERS		20

// error codes
#define ERROR_BASE						-400
#define E_FAILED_TO_ADD_MEMBER			(ERROR_BASE + 1)
#define E_CLUB_IS_FULL					(ERROR_BASE + 2)
#define E_INVALID_TERM_MONTHS			(ERROR_BASE + 3)
#define E_IVALID_CLUB_RATE				(ERROR_BASE + 4)
#define E_IVALID_MEM_CONTRIB			(ERROR_BASE + 5)
#define E_CLUB_IS_EMPTY					(ERROR_BASE + 6)

class InvestmentClub
{
	Member m_Member[MAX_CLUB_MEMBERS];
	char m_strError[STRING_BUFFER_SIZE];
	int m_iCurMonth;
	int m_iMemCount;
	float m_fRatePA;
	float m_fMemContribtion;
	float m_fLoanContribution;
	float m_fNetContribution;

	int m_ierror;

	void clearMembers();
	void printMembers();
	char* getStrError(int ierror);

public:
	InvestmentClub();
	InvestmentClub(float fRatePA, float fMemContribtion);

	void startClub(float fRatePA, float fMemContribtion);
	void addMember(char *Name);
	
	void Run();
	void Run(int iMonths);
	void RunMembers();
	
	int getError();
	void clearError();
};

#endif // _INVSETMENT_CLUB_H_