/* Citation and Sources...
Final Project Milestone 5
Module: Time
Filename: time.cpp
Version 1.0
Author	George Petrovski
Revision History
-----------------------------------------------------------
Date            Reason
2021/08/02      First Submission
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/

#define _CRT_SECURE_NO_WARNINGS
#include "Time.h"
#include "utils.h"
using namespace std;
namespace sdds {
	Time& Time::setToNow()
	{
		m_min = getTime();
		return *this;
	}

	Time::Time(unsigned int min)
	{
		m_min = min;
	}

	std::ostream& Time::write(std::ostream& ostr)const
	{
		unsigned int hours = 0, min = 0;
		hours = m_min / 60;
		min = m_min % 60;
		ostr.fill('0');
		ostr.width(2);
		ostr << hours;
		ostr << ":";
		ostr.fill('0');
		ostr.width(2);
		ostr << min;
		return ostr;
	}

	std::istream& Time::read(std::istream& istr)
	{
		int hours = 0, min = 0;
		char colonCheck = '0';
		istr >> hours >> colonCheck >> min;

		if (colonCheck != ':' || hours < 0 || min < 0)
		{
			istr.setstate(ios::failbit);
		}

		m_min = hours * 60 + min;
		return istr;
	}

	Time& Time::operator-=(const Time& D)
	{
		int multiplyFactor = 1;
		if (D.m_min > m_min)
		{
			if (D.m_min % 1440 == 0)
			{
				multiplyFactor = D.m_min / 1440;
			}
			else
			{
				multiplyFactor += D.m_min / 1440;
			}
			m_min += (1440*multiplyFactor - D.m_min);
		}
		else
		{
			m_min -= D.m_min;
		}
		return *this;
	}

	Time Time::operator-(const Time& D)const
	{
		int multiplyFactor = 1;
		int timeReturned = 0;
		if (D.m_min > m_min)
		{
			if (D.m_min % 1440 == 0)
			{
				multiplyFactor = D.m_min / 1440;
			}
			else
			{
				multiplyFactor += D.m_min / 1440;
			}
			timeReturned = m_min + (1440 * multiplyFactor - D.m_min);
		}
		else
		{
			timeReturned = m_min - D.m_min;
		}
		return timeReturned;
	}

	Time& Time::operator+=(const Time& D)
	{
		m_min += D.m_min;
		return *this;
	}

	Time Time::operator+(const Time& D)const
	{
		return m_min + D.m_min;
	}

	Time& Time::operator=(unsigned int val)
	{
		m_min = val;
		return *this;
	}

	Time& Time::operator *= (unsigned int val)
	{
		m_min *= val;
		return *this;
	}

	Time& Time::operator /= (unsigned int val)
	{
		m_min /= val;
		return *this;
	}

	Time Time::operator *(unsigned int val)const
	{
		return m_min * val;
	}

	Time Time::operator /(unsigned int val)const
	{
		
		return m_min / val;;
	}
	Time::operator unsigned int()const
	{
		return m_min;
	}

	Time::operator int()const
	{
		return (int)m_min;
	}

	std::ostream& operator<<(std::ostream& ostr, const Time& T)
	{
		return T.write(ostr);
	}
	std::istream& operator>>(std::istream& istr, Time& T)
	{
		return T.read(istr);
	}
}