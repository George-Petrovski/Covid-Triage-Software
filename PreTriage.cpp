/* Citation and Sources...
Final Project Milestone 5
Module: PreTriage
Filename: PreTriage.cpp
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
#include "CovidPatient.h"
#include "PreTriage.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

namespace sdds
{
	PreTriage::PreTriage(const char* dataFilename) : m_averCovidWait(15), m_averTriageWait(5), m_appMenu("General Hospital Pre-Triage Application\n1- Register\n2- Admit", 2), m_pMenu ("Select Type of Admittance:\n1- Covid Test\n2- Triage", 2)
	{
		m_dataFilename = new char[strLen(dataFilename) + 1];
		strCpy(m_dataFilename, dataFilename);
		load();
	}

	PreTriage::~PreTriage()
	{
		ofstream csvoutfile(m_dataFilename);
		csvoutfile << m_averCovidWait << "," << m_averTriageWait << endl;
		cout << "Saving Average Wait Times," << endl;
		cout << "   COVID Test: " << m_averCovidWait << endl;
		cout << "   Triage: " << m_averTriageWait << endl;
		if (m_lineupSize > 0)
		{
			cout << "Saving m_lineup..." << endl;
		}
		for (int i = 0; i < m_lineupSize; i++)
		{
			m_lineup[i]->csvWrite(csvoutfile);
			csvoutfile << endl;
			cout << i+1 << "- ";
			m_lineup[i]->csvWrite(cout);
			cout << endl;
			delete m_lineup[i];
		}
		delete[] m_dataFilename;
		cout << "done!" << endl;
	}

	void PreTriage::run(void)
	{
		int selection;
		do
		{
			m_appMenu >> selection;
			switch (selection)
			{
			case 1:
				reg();
				break;
			case 2:
				admit();
				break;
			default:
				break;
			}
		} while (selection != 0);
	}

	void PreTriage::reg()
	{
		if (m_lineupSize < maxNoOfPatients)
		{
			int selection;
			m_pMenu >> selection;
			switch (selection)
			{
			case 1:
				m_lineup[m_lineupSize] = new CovidPatient;
				break;
			case 2:
				m_lineup[m_lineupSize] = new TriagePatient;
				break;
			default:
				break;
			}	
			m_lineup[m_lineupSize]->setArrivalTime();
			cout << "Please enter patient information: " << endl;
			m_lineup[m_lineupSize]->read(cin);
			cout << "\n******************************************" << endl;
			m_lineup[m_lineupSize]->write(cout);
			cout << "Estimated Wait Time: " << getWaitTime(*m_lineup[m_lineupSize]) << endl;
			cout << "******************************************" << endl << endl;
			m_lineupSize += 1;
		}
		else
		{
			cout << "Line up full!" << endl;
		}
	}

	void PreTriage::admit()
	{
		char type;
		int index = -1;
		int selection;
		m_pMenu >> selection;
		switch (selection)
		{
		case 1:
			type = 'C';
			index = indexOfFirstInLine(type);
			
			break;
		case 2:
			type = 'T';
			index = indexOfFirstInLine(type);
			break;
		default:
			break;
		}
		if (index >= 0)
		{
			cout << "\n******************************************" << endl;
			cout << "Calling for ";
			m_lineup[index]->write(cout);
			cout << "******************************************" << endl << endl;
			setAverageWaitTime(*m_lineup[index]);
			removePatientFromLineup(index);
		}
	}

	const Time PreTriage::getWaitTime(const Patient& p) const
	{
		Time waitTime;
		int numFound = 0;
		for (int i = 0; i < m_lineupSize; i++)
		{
			if (m_lineup[i]->type() == p.type())
			{
				numFound++;
			}
		}
		if (p.type() == 'C')
		{
			waitTime = m_averCovidWait * (Time)numFound;
		}
		else if (p.type() == 'T')
		{
			waitTime = m_averTriageWait * (Time)numFound;
		}
		return Time();
	}

	void PreTriage::setAverageWaitTime(const Patient& p)
	{
		Time nowTime;
		nowTime.setToNow();
		if (p.type() == 'C')
		{
			m_averCovidWait = ((nowTime - (Time)p) + (m_averCovidWait * (Time)(p.number() - 1))) / (Time)p.number();
		}
		else if (p.type() == 'T')
		{
			m_averTriageWait = ((nowTime - (Time)p) + (m_averTriageWait * (Time)(p.number() - 1))) / (Time)p.number();;
		}
	}

	void PreTriage::removePatientFromLineup(int index)
	{
		removeDynamicElement(m_lineup, index, m_lineupSize);
	}

	int PreTriage::indexOfFirstInLine(char type) const
	{
		int matchFound = -1;
		for (int i = 0; i < m_lineupSize && matchFound == -1; i++)
		{
			if (m_lineup[i]->type() == type)
			{
				matchFound = i;
			}
		}
		return matchFound;
	}

	void PreTriage::load()
	{
		int numLoaded = 0;
		char type;
		cout << "Loading data..." << endl;
		ifstream csvfile(m_dataFilename);
		if (csvfile.peek() != -1)
		{
			csvfile >> m_averCovidWait;
			csvfile.ignore();
			csvfile >> m_averTriageWait;
			csvfile.ignore();
		}
		for (int i = 0; i < 100 && !csvfile.eof(); i++)
		{
			csvfile.get(type);
			if (csvfile.peek() != -1)
			{
				if (type == 'C')
				{
					m_lineup[i] = new CovidPatient;
				}
				else if (type == 'T') 
				{
					m_lineup[i] = new TriagePatient;
				}
				csvfile.ignore();
				m_lineup[i]->csvRead(csvfile);
				numLoaded += 1;
			}
		}
		if (!csvfile.eof())
		{
			cout << "Warning: number of records exceeded 100\n";
		}
		if (numLoaded == 0)
		{
			cout << "No data or bad data file!\n\n";
		}
		else if (numLoaded > 0)
		{
			cout << numLoaded << " Records imported...\n\n";
		}
		m_lineupSize = numLoaded;
	}
}