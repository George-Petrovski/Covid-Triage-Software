/* Citation and Sources...
Final Project Milestone 5
Module: Patient
Filename: patient.h
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

#ifndef SDDS_PATIENT_H_
#define SDDS_PATIENT_H_
#include "IOAble.h"
#include "Ticket.h"

namespace sdds
{
	class Patient :public IOAble
	{
		char* m_name = nullptr;
		int m_ohipNumber = 0;
		Ticket m_ticket;
		bool m_IOflag;
	public:
		Patient(int ticketNum = 0, bool IOflag = false);
		Patient(Patient&) = delete;
		~Patient();
		virtual char type()const = 0;
		bool fileIO() const;
		Patient& fileIO(bool IOflag);
		bool operator==(char x)const;
		bool operator==(const Patient& Ro)const;
		void setArrivalTime();
		operator Time()const;
		int number()const;
		std::ostream& csvWrite(std::ostream& ostr)const;
		std::istream& csvRead(std::istream& istr);
		std::ostream& write(std::ostream& ostr)const;
		std::istream& read(std::istream& istr);
	};
}

#endif // !SDDS_PATIENT_H_
