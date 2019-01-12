#ifndef _MEMBER_H_
#define _MEMBER_H_

//#define ENABLE_DEBUG					
#define STRING_BUFFER_SIZE		512

#define MEMBER_ERROR_BASE							-200
#define E_INVALID_NAME							(MEMBER_ERROR_BASE + 1)
#define E_INVALID_PRINCIPAL						(MEMBER_ERROR_BASE + 2)
#define E_INVALID_RATE							(MEMBER_ERROR_BASE + 3)
#define E_INVALID_TERM							(MEMBER_ERROR_BASE + 4)
#define E_INVALID_MONTH_OF_TERM					(MEMBER_ERROR_BASE + 5)
#define E_TERM_OVERRUN							(MEMBER_ERROR_BASE + 6)

class Member
{
	char m_Name[32];
	char m_strError[512];

	int m_iCurMonth;
	float m_fInterest;
	float m_fCurInstallment;
	
	float m_fPriciple;
	float m_fRatePA;
	int m_iTermMonths;

	float m_fPrincipleRepayed;
	float m_fInterestRepayed;
	float m_fInstallment;

	int m_ierror;

	float calcIntrest(float fPrincipal, float fRatePA);
	void clearMembers();
	void printMembers();
	char* getStrError(int ierror);

public:
	Member();
	Member(char *Name);
	Member(char *Name, float fPrincipal, float fRatePA, int iTermMonths);

	void Run();
	void Run(int iMonths);

	void setName(char *Name);
	void setLoan(float fPrincipal, float fRatePA, int iTermMonths);

	float getCurInstallment();
	float getInstallment(int iMonthofTerm);
	float getInterest();
	float getPrincipleRepayed();
	float getInterestRepayed();

	int getError();
	void clearError();
};


#endif // _MEMBER_H_