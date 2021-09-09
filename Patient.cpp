/* Citation and Sources...
Final Project Milestone 5
Module: Patient
Filename: patient.cpp
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

#include "Patient.h"
#include "utils.h"
#include <string>
#include <iostream>
using namespace std;
namespace sdds
{
	Patient::Patient(int ticketNum, bool IOflag): m_ticket(ticketNum)
	{
		m_IOflag = IOflag;
	}

	Patient::~Patient()
	{
		delete[] m_name;
	}

	bool Patient::fileIO() const
	{
		return m_IOflag;
	}

	Patient& Patient::fileIO(bool IOflag)
	{
		m_IOflag = IOflag;
		return *this;
	}

	bool Patient::operator==(char x) const
	{
		return (this->type() == x);
	}

	bool Patient::operator==(const Patient& Ro) const
	{
		return (this->type() == Ro.type());
	}

	void Patient::setArrivalTime()
	{
		m_ticket.resetTime();
	}

	Patient::operator Time() const
	{
		return (Time)m_ticket;
	}

	int Patient::number() const
	{
		return m_ticket.number();
	}

	std::ostream& Patient::csvWrite(std::ostream& ostr) const
	{
		ostr << type() << "," << m_name << "," << m_ohipNumber << ",";
		m_ticket.csvWrite(ostr);
		return ostr;
	}

	std::istream& Patient::csvRead(std::istream& istr)
	{
		if (istr.peek() != -1)
		{
			delete[] m_name;
			m_name = getcstr(nullptr, istr, ',');
			istr >> m_ohipNumber;
			istr.ignore();
			m_ticket.csvRead(istr);
		};
		return istr;
	}

	std::ostream& Patient::write(std::ostream& ostr) const
	{
		m_ticket.write(ostr);
		ostr << endl;
		for (int i = 0; i < 25 && m_name[i] != '\0'; i++)
			ostr << m_name[i];
		ostr << ", OHIP: " << m_ohipNumber << "\n";
		return ostr;
	}

	std::istream& Patient::read(std::istream& istr)
	{
		delete[] m_name;
		m_name = getcstr("Name: ", istr);
		std::cout << "OHIP: ";
		m_ohipNumber = getInt(100000000, 999999999, "", "Invalid OHIP Number, ");
		return istr;
	}
}