// OOP345 Milestone
// Edit Date	2016/Apr
// EUNSUN KIM / OOP345-SAB/SAAL
////////////////////////////////////////////
#pragma once
#include <ciso646>
#include <iostream>
#include <string>
#include <vector>
#include "CustomerOrder.h"

class Job : public CustomerOrder
{
private:	
	std::vector<bool> installed; //true if CustomerOrder.getItemsOrderd[i] is installed
	bool m_bDone;
	
public:
	Job();
	Job(CustomerOrder& oo);
	void completed();
	bool isComplete();
	void Install(int i) { installed[i] = true; }
	void Remove(int i) { installed[i] = false; }
	bool isInstalled(int i) { return installed[i]; }
	std::vector<std::string>& getItemsOrdered(); // <--------get CustomerOrder's ItemList(vector) --------//	
	void print(std::ostream& os);
};
