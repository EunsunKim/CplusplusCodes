// OOP345 Milestone 
// Edit Date	2016/Apr
// EUNSUN KIM / OOP345-SAB/SAAL
////////////////////////////////////////////
#include <ciso646>
#include <iostream>
#include <string>
#include <iomanip>
#include <cassert>
#include <vector>
#include <exception>
#include "Job.h"
#include "Task.h"
#include "Item.h"
#include "CustomerOrder.h"

using namespace std;

Job::Job() : m_bDone(false)
{
	
}
Job::Job(CustomerOrder& oo) :	CustomerOrder(oo), //base class constructor
								m_bDone(false)
{//ItemList
	for (size_t i = 0; i < getItemsOrdered().size(); i++)
		installed.push_back(false);
}

void Job::completed()
{
	m_bDone = true;
}

bool Job::isComplete()
{
/*	for (auto e : installed)
		if (not e)
			return false;  
	return true;*/
	if (getItemsOrdered().empty())
	{
		return true;
	}

	return m_bDone;
}

std::vector<std::string>& Job::getItemsOrdered()
{
	return ItemList;  // <----------------------------------------//
}

void Job::print(std::ostream& os)
{	
	os << "ID: " << CustomerName << " - " << ProductName << "\n";
}
