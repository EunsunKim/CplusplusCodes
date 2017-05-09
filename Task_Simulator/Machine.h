// OOP345 Milestone - Machine
// File	Machine.h
// Date	2016/Apr.
// Author	EUNSUN KIM / OOP345-SAB/SAAL
////////////////////////////////////////////
#pragma once
#include <queue>
#include <vector>
#include "Item.h"
#include "CustomerOrder.h"
#include "Task.h"
#include "Job.h"

class Machine :public Task
{	
//  Task t;
	bool bInstaller;
	bool bRemover;
	bool bSource;

	std::queue<Job>	m_qInputQ;
	std::queue<Job>	m_qPassedJob;
	std::queue<Job>	m_qFailedJob;
	std::string		m_Name;
	Job	m_Job;	
	
public:	
	Machine(Task& tt, ItemManager& im);
	void push(Job&& j);	
	bool empty() { return m_qInputQ.empty(); }
	void print(std::ostream& os);
	void Classify(ItemManager& im);
	void Run(ItemManager& im, std::vector<Machine>& machineList);
	
	void setAsSource(bool bThisIsSource);
	bool isJobCompleted();
	bool isSource();
	bool isSink();
	bool isInstallRequired();
	bool isRemoveRequired();
	bool installItem(ItemManager& itemManager);
	bool removeItem(ItemManager& itemManager);
	bool inspector();
	bool flip_a_coin();
};