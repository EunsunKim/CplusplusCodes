// OOP345 Milestone - CustomerOrder and CustomerOrderManager
// File	CustomerOrder.cpp
// Date	2016/Mar.- Apr
// Author	EUNSUN KIM / OOP345-SAB/SAAL
////////////////////////////////////////////
#include <ciso646>  //for visual studio
#include <string>
#include <exception>
#include <fstream>
#include <sstream>   // getline from string stream
#include <cctype>    //isalnum
#include <iomanip> 
#include <algorithm>
#include "CustomerOrder.h"
#include "Item.h"

using namespace std;
size_t CustomerOrder::field_width;

CustomerOrder::CustomerOrder():CustomerName(""), ProductName(""), ItemList('\0'), NumberOfOrders(0) {}

CustomerOrder::CustomerOrder(const vector<string>& fields) 
	: CustomerName(""), ProductName(""), ItemList('\0'), NumberOfOrders(0)
{
	// validate CustomerName, ProductName, and ItemList 
	//  are alphabet or number for string 
	auto isTaskName = [](string& s) -> bool
	{
		if ((isalpha((int)s[0]) != 0) || (s[0] == '_'))
		{
			for (size_t i = 0; i < s.size(); ++i)
			{
				if ((isalnum(s[i]) == 0) && (s[i] != ' ') && (s[i] != '_'))
				{
					return false;
				}
			}
			return true;
		}
		return false;
	};

	auto isNumber = [](std::string& s) -> bool
	{
		std::stringstream ss(s);
		int i;
		if (ss >> i)
			return true;
		else
			return false;
	};

	auto error = [](string errorType, string expected, string found)
	{
		throw errorType + " expected " + expected + " found " + found;
	};
	
	if (fields.size() < 3)   //assume the fields sizes are at least 3
		cerr << "fields need at least 3\n";
	else
	{
		if (!fields[0].empty() )
			CustomerName = fields[0];
		else
			error(string("lookng for 'CustomerName' "), string("task name "), fields[0]);

		if (!fields[1].empty() )
			ProductName = fields[1];
		else
			error(string("lookng for 'ProductName' "), string("task name "), fields[1]);		

		// -------->  iterator for loop below  <-----------
			
		for (vector<string>::const_iterator itrField = fields.begin() + 2; itrField != fields.end(); itrField++)
		{
			if (!itrField->empty()) 
				ItemList.push_back((*itrField));
			NumberOfOrders++;
		}		
	}
}

const std::string CustomerOrder::getCustomerName() const  { return CustomerName; }
const std::string CustomerOrder::getProductName() const   {	return ProductName; }

// display for CustomerOrder class's elements, CustomerName, ProductName, and ItemLists
void CustomerOrder::display(std::ostream& os) const  
{    
	size_t FieldWidth = field_width + 2;
	std::string quote(R"(")");
	
	os << "CustomerName    : " << left << std::setw(17) << CustomerName << endl;
	os << std::setw(19) <<  "     ordered " << quote + ProductName + quote << endl;
	
	for (vector<string>::const_iterator itrItem = ItemList.begin(); itrItem != ItemList.end(); itrItem++)  //don't forget 'const'
	{
		os << fixed << right << std::setw(15) << "--> ";
		os << fixed << left << *itrItem << "\n";		
	}
}

// beginning gengraphviz for CustomerOrder
// std::vector<std::string> ItemList

void CustomerOrder::gengraphviz(ostream& os) const
{  //CustomerName, ProductName, ItemList  
	string quote(R"(")");
	string str_customername = quote + CustomerName + quote;
	string str_productname = quote + ProductName + quote;
	
	if (not CustomerName.empty())
	{
		os << " " << str_customername << "[shape=box][color=green]\n";
	}

	if (not ProductName.empty())
	{
		os << " " << str_customername << "->" << str_productname << "[color=green]\n";
		if (not ItemList.empty())
		{
			//NumberOfOrders = (unsigned int)(ItemList.size());
			int i = NumberOfOrders;    
			
			for (vector<string>::const_iterator it = ItemList.begin(); it != ItemList.end(); it++)
			{
				//os << " " << str_customername << "->" << "\"" << "ITEM\\n" <<*it << "\"" <<"[color=blue]\n";
				os << " " << str_productname << "->" << "\"" << "ITEM - " << i << "\\n" << *it << "\"" << "[color=blue]\n";
				i--;
			}
		}
	}	
}  //gengraphviz


// beginning the OrderManager
// OrderManager contains (composition) a list of all instances of that CustomerOrder's data type
// std::vector<CustomerOrder> OrderList;

void OrderManager::display(std::ostream& os)
{
	for (auto&o : *this)  // <----------------------------------------//
		o.display(cout);
}

void OrderManager::gengraphviz(string filename)
{
	ofstream of(filename.c_str(), ios::out);
	if (of.is_open())
	{
		of << "digraph task {\n";
		of << R"(node[style="filled", fillcolor="white"])";
		of << "\n";

		for (auto t : *this)
		{
			t.gengraphviz(of);
		}
		of << R"foo(label = " )foo";
		of << filename;
		of << R"foo(\n< Eunsun Kim >OOP345 Milestone\n2016\nCustomerOrder Relation Diagram drawn by Graphviz";
            fondsize=30;)foo";
		of << "}\n";
	}
}
