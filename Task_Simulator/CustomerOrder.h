// OOP345 Milestone- CustomerOrder and CustomerOrderManager
// File	CustomerOrder.h
// Date	2016/Mar.- Apr
// Author	EUNSUN KIM / OOP345-SAB/SAAL
////////////////////////////////////////////
#pragma once
#include <ciso646>  //for visual studio
#include <iostream>
#include <vector>
#include "Item.h"

class CustomerOrder 
{
protected: // <----------------------------------------//
	std::string CustomerName, ProductName;
	std::vector<std::string> ItemList;
	unsigned int NumberOfOrders;
	static size_t field_width;

public:
	CustomerOrder();
	CustomerOrder(const std::vector<std::string>& fields);	
	const std::string getCustomerName() const;
	const std::string getProductName() const;			
	void display(std::ostream& os) const;
	void gengraphviz(std::ostream& os) const;
};

class OrderManager : public std::vector<CustomerOrder> {
			
public:			
	void display(std::ostream& os);
	void gengraphviz(std::string filename);
	void parseOrderManager(const std::vector<std::vector<std::string>>& vOrders)
	{
		for (auto line : vOrders)
		{
			push_back(CustomerOrder(line));
		}
	}
};