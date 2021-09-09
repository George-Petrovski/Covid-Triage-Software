/* Citation and Sources...
Final Project Milestone 5
Module: CovidPatient
Filename: CovidPatient.cpp
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

#include "CovidPatient.h"

namespace sdds {
int nextCovidTicket = 1;
   CovidPatient::CovidPatient() : Patient(nextCovidTicket)
   {
	   nextCovidTicket++;
   }
   char CovidPatient::type()const
   {
	   return 'C';
   }
   std::istream& CovidPatient::csvRead(std::istream& istr)
   {
	   Patient::csvRead(istr);
	   nextCovidTicket = Patient::number() + 1;
	   istr.ignore(1);
	   return istr;
   }
   std::ostream& CovidPatient::write(std::ostream& ostr) const
   {
	   if (Patient::fileIO())
	   {
		   csvWrite(ostr);
	   }
	   else
	   {
		   ostr << "COVID TEST\n";
		   Patient::write(ostr);
	   }
	   return ostr;
   }
   std::istream& CovidPatient::read(std::istream& istr)
   {
	   if (Patient::fileIO())
	   {
		   csvRead(istr);
	   }
	   else
	   {
		   Patient::read(istr);
	   }
	   return istr;
   }
}