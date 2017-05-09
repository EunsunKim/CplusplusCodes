// OOP345 Milestone  - Item and ItemManager
// File	Item.h
// Date	2016/Mar-Apr
// Author	EUNSUN KIM / OOP345-SAB/SAAL
////////////////////////////////////////////
#pragma once
#include <ciso646>   //for visual studio
#include <iostream>
#include <vector>
#include "CustomerOrder.h"

class Item
{        
protected: // <----------------------------------------//
	std::string itemName, InstallerTask, Remover, SequentialCode, Description;
	static size_t field_width;  
	unsigned int NumberOfOrders;
	//std::vector<std::string> ItemList;
public:
	Item();
	Item(const std::vector<std::string>& fields);
	const std::string& getItemName() const;	
	const std::string& getInstaller() const;      
	
	const std::string& getRemover()const ;         //getDestination
	unsigned int getSequentialCode() const;	
	void display(std::ostream& os);
	void gengraphviz(std::ostream& os);
};

class ItemManager : public std::vector<Item> {

public:	
	Item* find(const std::string& csName);
	void display(std::ofstream& os);
	void gengraphviz(std::string filename);
	void parseItem(std::vector<std::vector<std::string>>& vItems)
	{
		for (auto line : vItems)
		{
			push_back(Item(line));
		}
	}
};
