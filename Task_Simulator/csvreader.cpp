// OOP345 Milestone 1 - CSVreader
// csvreader.cpp
// Date	2016/Mar.23 - Apr.
// EUNSUN KIM / OOP345-SAB/SAAL
////////////////////////////////////////////
#include <ciso646>  // for Visual Studio 2015
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>
#include <sstream>  // getline from string stream
#include <cctype>
#include <memory>
#include "csvreader.h"
#include "Task.h"
#include "Item.h"
#include "CustomerOrder.h"

// trim white space, tab, and carriage return
std::string& trim(std::string& s)
{
	/*
	while (not s.empty() and s[0] == ' ')
		s.erase(0, 1);
	while (not s.empty() and s[s.size() - 1] == '\r')  // added 04/02/2016
		s.erase(s.size() - 1, 1);
	while (not s.empty() and s[s.size() - 1] == '\n')  // added 04/02/2016
		s.erase(s.size() - 1, 1);
	while (not s.empty() and s[s.size() - 1] == ' ')
		s.erase(s.size() - 1, 1);
	*/
	auto cr = s.find_first_not_of(" \t\r\n");  //fixed because much easier than privious one
	s.erase(0, cr);
	cr = s.find_last_not_of(" \t\r\n");
	if (cr != std::string::npos)
		s.erase(cr + 1);
	return s;
}

//************************************************************************************************//
// beginning csvReader here

void csvReader(std::string fileName, char delimeter, std::vector< std::vector<std::string> >& data)
{	
	std::ifstream is(fileName.c_str(), std::ios::in);
	if (is.is_open())
	{
		std::string line;
		while (std::getline(is, line))       // read each line  // if read line is duplicate line ??
		{                                    
			//is >> std::ws;	// trim function fixed so this line dosen't need		
			std::stringstream ss(line);
			std::string field;
			std::string fieldTrimOff;
			std::vector<std::string> fields;

			unsigned int uiTotalLetter = 0;  // <-- --------      added 04/01/2016
			
			while (getline(ss, field, delimeter))
			{
				if (field.length() > 0 and not field.empty())
				{
					fieldTrimOff = trim(field);
					uiTotalLetter += fieldTrimOff.size();        // added 04/01/2016 don't forget this methode					
					fields.push_back(fieldTrimOff);					
				}
			}
			if (not fields.empty() and (uiTotalLetter != 0))       //if empty fields,TaskList.dat 12 line will skip
				data.push_back(fields);                  //add a vector of the field data into the "data" vector					
		}
		is.close();
	} else
		throw std::string("cannot open file") + fileName;
} // end csvReader
