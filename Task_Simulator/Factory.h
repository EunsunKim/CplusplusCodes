// OOP345 Milestone - Factory
// File	Factory.h
// Date	2016/Apr.
// Author	EUNSUN KIM / OOP345-SAB/SAAL
////////////////////////////////////////////
#pragma once
#include <ciso646>      // for Visual Studio 2015
#include <iostream>
#include <vector>       // at
#include <queue>
#include <cstring>
#include "Task.h"
#include "Item.h"
#include "CustomerOrder.h"
#include "Job.h"
#include "Machine.h"

class Factory
{
	ItemManager  im;
	OrderManager om;
	TaskManager  tm;
	std::vector<Job> jobList;
	std::vector<Machine> machineList;	

public:
	Factory(TaskManager&& TM, ItemManager&& IM, OrderManager&& OM);
	void gengraphviz(std::string filename);
};

//int IntegrityCheck(ItemManager& im, OrderManager& om, TaskManager& tm);
