#include "pch.h"
#include "Member.h"

Member::Member()
{
	clearMembers();
	setName(NULL);
}

Member::Member(char *Name)
{
	clearMembers();
	setName(Name);
}

Member::Member(char *Name, float fPrincipal, float fRatePA, int iTermMonths)
{
	clearMembers();
	setName(Name);
	setLoan(fPrincipal, fRatePA, iTermMonths);
}

void Member::Run(int iMonths)
{
	if(iMonths < 0)
	{
		m_ierror = E_INVALID_TERM;
	}
	else
	{
		for(int iCurMonth = 0; iCurMonth < iMonths; iCurMonth++)
		{
			Run();
		}
	}
}

void Member::Run()
{
	float fInstallment = 0;

	if(m_iCurMonth < m_iTermMonths)
	{		
		// increment the month
		m_iCurMonth++;

		// calculate currrent intrest and installment
		m_fInterest = calcIntrest((m_fPriciple - m_fPrincipleRepayed), m_fRatePA); 
		m_fCurInstallment = m_fInstallment + m_fInterest;

		m_fPrincipleRepayed += m_fInstallment;
		m_fInterestRepayed  += m_fInterest;
	}
	else
	{
		m_ierror = E_TERM_OVERRUN;
	}

	#ifdef ENABLE_DEBUG
		printMembers();
	#endif
}

float Member::getPrincipleRepayed()
{
	return m_fPrincipleRepayed;
}

float Member::getInterestRepayed()
{
	return m_fInterestRepayed;
}

float Member::getCurInstallment()
{
	return m_fCurInstallment;
}

float Member::getInterest()
{
	return m_fInterest;
}

// not to be used in run
float Member::getInstallment(int iMonthofTerm)
{
	float Installment = 0;
	float fInterest = 0;

	if((iMonthofTerm < 0) || (iMonthofTerm > m_iTermMonths))
	{
		m_ierror = E_INVALID_MONTH_OF_TERM;
	}
	else
	{
		fInterest = calcIntrest((m_fPriciple - m_fPrincipleRepayed), m_fRatePA);
		Installment = m_fInstallment + fInterest;
	}

	return Installment;
}

void Member::setLoan(float fPrincipal, float fRatePA, int iTermMonths)
{
	clearMembers();
	
	// set the principal
	if(fPrincipal > 0)
	{
		m_fPriciple = fPrincipal; 	
	}
	else
	{	
		m_fPriciple = 0;
		m_ierror = E_INVALID_PRINCIPAL;
	}

	// set the rate
	if(fRatePA > 0)
	{
		m_fRatePA = fRatePA;	
	}
	else
	{	
		m_fRatePA = 0;
		m_ierror = E_INVALID_RATE;
	}


	// set the term
	if(iTermMonths > 0)
	{
		m_iTermMonths = iTermMonths;	
	}
	else
	{	
		m_iTermMonths = 0;
		m_ierror = E_INVALID_TERM;
	}

	// calculate the installment
	m_fInstallment = ((float)m_fPriciple / (float)m_iTermMonths);
	m_fPrincipleRepayed = 0;
	m_fInterestRepayed = 0;
}

int Member::getError()
{
	return m_ierror;
}

void Member::clearError()
{
	m_ierror = 0;
}

// helper functions
float Member::calcIntrest(float fPrincipal, float fRatePA)
{
	// (12 * 100) ie converting rate pa to rate pm
	return (fPrincipal * (fRatePA / 1200));
}


void Member::clearMembers()
{

 	memset(m_Name, 0, sizeof(m_Name));
 	memset(m_strError, 0, sizeof(m_strError));

	m_iCurMonth = 0;
	m_fInterest = 0;
	m_fCurInstallment = 0;

	m_fPriciple = 0;
	m_fRatePA = 0;
	m_iTermMonths = 0;

	m_fPrincipleRepayed = 0;
	m_fInterestRepayed = 0;
	m_fInstallment = 0;	

	m_ierror = 0;
}

void Member::setName(char *Name)
{
	if(Name != NULL)
	{
		strcpy_s(m_Name, sizeof(m_Name), Name);
	}
	else
	{
		strcpy_s(m_Name, sizeof(m_Name), "Name Not Given");
		m_ierror = E_INVALID_NAME;
	}
}

void Member::printMembers()
{
	printf("\r\n%d,\t%.2f,%.2f,%d,", 
			m_iCurMonth,
			m_fPriciple,
			m_fRatePA,
			m_iTermMonths);

	printf("\t%.2f,%.2f,%.2f,", 
			m_fPrincipleRepayed,
			m_fInterestRepayed,
			m_fInstallment);

	printf("\t%.2f,%.2f", 
			m_fCurInstallment,
			m_fInterest);

	if(m_ierror != 0)
	{
		printf("\n%s", getStrError(m_ierror));
	}
}


char* Member::getStrError(int ierror)
{
	switch(ierror)
	{
		case E_INVALID_NAME:
			
			sprintf_s(m_strError, STRING_BUFFER_SIZE, "[%d]: Invalid Name", ierror);
		break;

		case E_INVALID_PRINCIPAL:
			
			sprintf_s(m_strError, STRING_BUFFER_SIZE, "[%d]: Invalid principle amount", ierror);
		break;

		case E_INVALID_RATE:
			
			sprintf_s(m_strError, STRING_BUFFER_SIZE, "[%d]: Invalid Intreat Rate per Annum", ierror);
		break;

		case E_INVALID_TERM:
			
			sprintf_s(m_strError, STRING_BUFFER_SIZE, "[%d]: Invalid Term in months", ierror);
		break;

		case E_INVALID_MONTH_OF_TERM:
			
			sprintf_s(m_strError, STRING_BUFFER_SIZE, "[%d]: Invalid Month of the term", ierror);
		break;

		case E_TERM_OVERRUN:
			
			sprintf_s(m_strError, STRING_BUFFER_SIZE, "[%d]: Term overrun", ierror);
		break;		

		default:
			sprintf_s(m_strError, STRING_BUFFER_SIZE, "[%d]: Unknown Error", ierror);
	}

	return m_strError;
}