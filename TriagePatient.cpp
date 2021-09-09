/* Citation and Sources...
Final Project Milestone 5
Module: TriagePatient
Filename: TriagePatient.cpp
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

#include "TriagePatient.h"
#include "utils.h"
namespace sdds {
   int nextTriageTicket = 1;

   TriagePatient::TriagePatient() : Patient(nextTriageTicket)
   {
	   nextTriageTicket++;
	   m_symptoms = nullptr;
   }

   TriagePatient::~TriagePatient()
   {
	   delete[] m_symptoms;
   }

   char TriagePatient::type() const
   {
	   return 'T';
   }

   std::ostream& TriagePatient::csvWrite(std::ostream& ostr) const
   {
	   Patient::csvWrite(ostr);
	   ostr << "," << m_symptoms;
	   return ostr;
   }

   std::istream& TriagePatient::csvRead(std::istream& istr)
   {
	   if (istr.peek() != -1)
	   {
		   delete[] m_symptoms;
		   Patient::csvRead(istr);
		   istr.ignore(1);
		   m_symptoms = getcstr(nullptr, istr, '\n');
		   nextTriageTicket = Patient::number() + 1;
	   }
	   return istr;
   }

   std::ostream& TriagePatient::write(std::ostream& ostr) const
   {
	   if (Patient::fileIO())
	   {
		   csvWrite(ostr);
	   }
	   else
	   {
		   ostr << "TRIAGE\n";
		   Patient::write(ostr);
		   ostr << "Symptoms: " << m_symptoms << "\n";
	   }
	   return ostr;
   }

   std::istream& TriagePatient::read(std::istream& istr)
   {
	   if (Patient::fileIO())
	   {
		   csvRead(istr);
	   }
	   else
	   {
		   delete[] m_symptoms;
		   Patient::read(istr);
		   m_symptoms = getcstr("Symptoms: ", istr, '\n');
	   }
	   return istr;
   }

}