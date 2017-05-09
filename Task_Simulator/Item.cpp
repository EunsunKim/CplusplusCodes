// OOP345 Milestone - Item and ItemManager
// File	Item.cpp
// Date	2016/Mar. - Apr.
// Author	EUNSUN KIM / OOP345-SAB/SAAL
////////////////////////////////////////////
#include <ciso646>      //for visual studio
#include <iostream>     // std::cout
#include <fstream>
#include <exception>
#include <cctype>       //isalnum
#include <sstream>      // getline from string stream
#include <iomanip>
#include <vector>       // std::vector
#include <algorithm>    // std::find
#include "Item.h"

using namespace std;
size_t Item::field_width =1;

Item::Item() :itemName(""), InstallerTask(""), Remover(""), SequentialCode("1"), Description("no detailed description") {}

Item::Item(const vector<string>& fields)		
	{	// validate functions for all Item's member from here	
		auto isTaskName = [](string& s) -> bool
		{			
			if ((isalpha((int)s[0]) != 0) || (s[0] == '_'))
			{
				for (size_t i = 0; i < s.size(); ++i)
				{
					if ((isalnum(s[i]) == 0) && (s[i] != ' ') && (s[i] != '_'))
					{ return false;	}
				} return true;
			}return false;
		};

		auto isNumber = [](string& s) -> bool
		{
			stringstream ss(s);
			int i;
			if (ss >> i)
				return true;
			else
				return false;
		};
		auto error = [](string errorType, string expented, string found)
		{
			throw errorType + " expented " + expented + " found " + found;
		};
		
		// put Item's each data string members  to each field after validate
		// Item data - ensure all install and remove task references exist		
		switch (fields.size())
		{
		case 5:
			if (not fields[4].empty())
				Description = fields[4];	
		case 4:
			if (not fields[3].empty() )
				SequentialCode = fields[3];	
			else
				error(string("lookng for 'SequentialCode' "), string("number "), fields[3]);
		case 3:
			if (not fields[2].empty() )
				Remover = fields[2];
			else
				error(string("lookng for 'Remover' "), string("task name "), fields[2]);
		case 2:
			if (not fields[1].empty() )
				InstallerTask = fields[1];
			else
				error(string("lookng for 'InstallerTask' "), string("task name "), fields[1]);
		case 1:					
			if (not fields[0].empty() )
				itemName = fields[0];
			else
				error(string("lookng for 'ItemName' "), string("task name "), fields[0]);
			break;
		default:
			error(string("fields count not correct "), string("1,2,3,4, or 5 fields "), to_string(fields.size()) + std::string("fields"));
		}
	}
const std::string& Item::getItemName() const  
{
	return itemName;
}

const string& Item::getInstaller() const //for void Machine::Classify(ItemManager& im) 
{ 	return InstallerTask; }

const string& Item::getRemover() const  //for void Machine::Classify(ItemManager& im) 
{	return Remover; }

unsigned int Item::getSequentialCode() const
{	return stoi(SequentialCode); }

void Item::display(ostream& os)
{
	size_t FieldWidth = field_width + 2;
	string quote(R"(")");

	os << "Item Name    : " << left << setw(17) << quote + itemName + quote;
	os << "-->  SequentialCode : " << quote << fixed << right 
	   << setw(5) << setfill('0') << SequentialCode << quote << std::endl;
	
	os << fixed <<setfill(' ') <<  setw(15) << "--> " << fixed << left <<  setw(19)  << string("From ") + InstallerTask <<  std::string("To ") + Remover << std::endl;
	
	os << fixed << right << setfill(' ') <<setw(15) ;
	if (!Description.empty())
		os << "--> " << fixed << left << Description << endl;
	else
		os << std::endl;
}
// beginning gengraphviz
//ItemName, InstallerTask, Remover, SequentialCode, Description
void Item::gengraphviz(ostream& os)
{
	string quote(R"(")");
	string str_itemname = quote + "ItemName\\n" + itemName + quote;	
	string str_installertask = quote + "InstallerTask\\n" + InstallerTask + quote;	
	string str_remover = quote + "Remover\\n" + Remover + quote;
	string str_sequentialcode = quote + SequentialCode + quote;
	string str_description = quote + "Description\\n" + Description + quote ;

	if (not Description.empty())
	{
		os << " " << str_itemname << "[shape=box][color=blue]\n";
		os << " " << str_description << "[shape=box][color=blue]\n";
		os << " " << str_itemname << "->" << str_installertask << "[color=blue]\n";
		os << " " << str_installertask << "->" << str_remover << "[color=red]\n";		
		os << " " << str_remover << "->" << str_installertask << "[color=green]\n";
		os << " " << str_itemname << "->" << str_description << "[color=blue]\n";
	}
	else
	{
		os << " " << str_itemname << "[shape=box][color=blue]\n";
		os << " " << str_itemname << "->" << str_installertask << "[color=blue]\n";
		os << " " << str_installertask << "->" << str_remover << "[color=red]\n";
		os << " " << str_remover << "->" << str_installertask << "[color=green]\n";
	}
}  //gengraphviz


/*  find ItemName through the Item object with getItemName(), if ItemName not found return nullptr */

Item* ItemManager::find(const std::string& csName)
{
	for (auto& item : *this)
	{
		if (item.getItemName() == csName)
		{
			return &item;
		}
	} return nullptr;
}

void ItemManager::display(std::ofstream& os)
{
	for (auto&i : *this)   
		i.display(cout);    
} 

void ItemManager::gengraphviz(std::string filename)
{
	ofstream of(filename.c_str(), ios::out);
	if (of.is_open())
	{
		of << "digraph item {\n";
		of << R"(node[style="filled", fillcolor="white"])";
		of << "\n";

		for (auto t : *this)
		{
			t.gengraphviz(of);
		}

		of << R"foo(label = " )foo";
		of << filename;
		of << R"foo( \n< Eunsun Kim >OOP345 Milestone\n2016\nItem Relation Diagram drawn by Graphviz";
            fondsize=30;)foo";
		of << "}\n";
	}
}
