/* Citation and Sources...
Final Project Milestone 5
Module: Menu
Filename: Menu.cpp
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
#include "Menu.h"
#include "utils.h"
#include <iostream>

using namespace std;
namespace sdds
{
	void Menu::display()const
	{
		cout << m_text;
		cout << endl << "0- Exit" << endl;
	}

	Menu::Menu(const char* MenuContent, int NoOfSelections)
	{
		m_text = new char[strLen(MenuContent) + 1];
		strCpy(m_text, MenuContent);
		m_noOfSel = NoOfSelections;
	}

	Menu::Menu(const Menu& data)
	{
		m_noOfSel = data.m_noOfSel;
		*this = data.m_text;
	}

	Menu::~Menu()
	{
		delete[] m_text;
	}

	int& Menu::operator>>(int& Selection)
	{
		display();
		Selection = getInt(0, m_noOfSel, "> ", "Invalid option ");
		return Selection;
	}

	Menu& Menu::operator=(const char* data)
	{
		m_text = new char[strLen(data) + 1];
		strCpy(m_text, data);
		return *this;
	}
}