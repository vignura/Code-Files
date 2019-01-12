#include "pch.h"
#include "InvestmentClub.h"

// constructors
InvestmentClub::InvestmentClub()
{
	clearMembers();
} 

InvestmentClub::InvestmentClub(float fRatePA, float fMemContribtion)
{
	clearMembers();
	startClub(fRatePA, fMemContribtion);
} 

void InvestmentClub::startClub(float fRatePA, float fMemContribtion)
{
	if(fRatePA > 0)
	{
		m_fRatePA = fRatePA;
	}
	else
	{
		m_ierror = E_IVALID_CLUB_RATE;
		m_fRatePA = 0;
	}

	if(fMemContribtion > 0)
	{
		m_fMemContribtion = fMemContribtion;
	}
	else
	{
		m_ierror = E_IVALID_MEM_CONTRIB;
		fMemContribtion = 0;
	}
}

void InvestmentClub::addMember(char *Name)
{
	if(m_iMemCount >= MAX_CLUB_MEMBERS)
	{
		m_ierror = E_CLUB_IS_FULL;
	}
	else
	{
		m_Member[m_iMemCount].clearError();
		m_Member[m_iMemCount].setName(Name);
		
		if(m_Member[m_iMemCount].getError() != 0)
		{
			m_ierror = E_FAILED_TO_ADD_MEMBER;	
		}
		else
		{
			m_iMemCount++;
		}
	}
}

void InvestmentClub::Run(int iMonths)
{
	if(iMonths < 0)
	{
		m_ierror = E_INVALID_TERM_MONTHS;
	}
	else
	{
		for(int iCurMonth = 0; iCurMonth < iMonths; iCurMonth++)
		{
			Run();
		}
	}
}


void InvestmentClub::Run()
{
	int iMemtoLoan = 0;
	m_iCurMonth++;

	if(m_iMemCount > 0)
	{
		// calculate the net contribution
		m_fNetContribution = (m_fMemContribtion * m_iMemCount);

		// run members
		RunMembers();
	
		// reset the loan contribution
		m_fLoanContribution = 0;
		for(int iMemCount = 0; iMemCount < m_iMemCount; iMemCount++)
		{
			m_fLoanContribution += m_Member[iMemCount].getCurInstallment();
		}

		m_fNetContribution += m_fLoanContribution;
		
		iMemtoLoan = (m_iCurMonth -1) % m_iMemCount;
		m_Member[iMemtoLoan].setLoan(m_fNetContribution, m_fRatePA, m_iMemCount);
	}
	else
	{
		m_ierror = E_CLUB_IS_EMPTY;
	}

	#ifdef ENABLE_DEBUG
		printMembers();
	#endif
}

void InvestmentClub::RunMembers()
{
	for(int iMemCount = 0; iMemCount < m_iMemCount; iMemCount++)
	{
		m_Member[iMemCount].Run();
	}	
}

int InvestmentClub::getError()
{
	return m_ierror;
}

void InvestmentClub::clearError()
{
	m_ierror = 0;
}

char* InvestmentClub::getStrError(int ierror)
{
	switch(ierror)
	{
		case E_FAILED_TO_ADD_MEMBER:
			
			sprintf_s(m_strError, STRING_BUFFER_SIZE, "[%d]: unable to add a new member", ierror);
		break;

		case E_CLUB_IS_FULL:
			
			sprintf_s(m_strError, STRING_BUFFER_SIZE, "[%d]: club is full", ierror);
		break;

		case E_INVALID_TERM_MONTHS:
			
			sprintf_s(m_strError, STRING_BUFFER_SIZE, "[%d]: Invalid term in months", ierror);
		break;

		case E_IVALID_CLUB_RATE:
			
			sprintf_s(m_strError, STRING_BUFFER_SIZE, "[%d]: Invaid club intrest rate", ierror);
		break;

		case E_IVALID_MEM_CONTRIB:
			
			sprintf_s(m_strError, STRING_BUFFER_SIZE, "[%d]: Invalid club membership contribution", ierror);
		break;

		case E_CLUB_IS_EMPTY:
			
			sprintf_s(m_strError, STRING_BUFFER_SIZE, "[%d]: The club is empty", ierror);
		break;

		default:
			sprintf_s(m_strError, STRING_BUFFER_SIZE, "[%d]: Unknown Error", ierror);
	}

	return m_strError;
}

// helper functions
void InvestmentClub::clearMembers()
{
	m_iMemCount = 0;
	m_fRatePA = 0;
	m_iCurMonth = 0;
	m_fMemContribtion = 0;
	m_fNetContribution = 0;
	m_fLoanContribution = 0;
	m_ierror = 0;
	memset(m_strError, 0, sizeof(m_strError));
}


void InvestmentClub::printMembers()
{
	printf("\r\n%d,%d,%.2f,", 
					m_iCurMonth,
					m_iMemCount,
					m_fRatePA);

	printf("\t%2.2f,%2.2f,%2.2f",
					m_fMemContribtion, 
					m_fLoanContribution, 
					m_fNetContribution);


	if(m_ierror != 0)
	{
		printf("\n%s", getStrError(m_ierror));
	}
}