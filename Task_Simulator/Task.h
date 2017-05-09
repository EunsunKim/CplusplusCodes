// OOP345 Milestone - Task and TaskManager
// File	Task.h
// Date	2016/Mar.22 - Apr
// Author	EUNSUN KIM / OOP345-SAB/SAAL
////////////////////////////////////////////
#pragma once
#include <ciso646>   //for visual studio
#include <iostream>
#include <vector>
#include<sstream>
#include "Item.h"

class Task
{
protected: // <----------------------------------------//
	std::string TaskName, Slots;
	std::string nextTask[2];
	const Task* pNextTask[2];  //destination
	static size_t field_width;			

public:
	enum Quality
	{
		Installer,
		Failed
	};

	Task();
	Task(std::vector<std::string>& fields);	
	const std::string& getName() const;	
	const std::string& getPassed() const;
	const std::string& getFailed() const;
	bool validate(const Task& t);
	const Task* getNextTask(Quality quality) const;

	void display(std::ostream& os) const;		
	void gengraphviz(std::ostream& os) const;	
};

class TaskManager : public std::vector<Task> {	
public:		
	void display(std::ofstream& os) const;
	void gengraphviz(std::string filename) ;	

	void parseTask(const std::vector<std::vector<std::string>>& vTasks)
	{	
		for (auto line : vTasks)
		{
			push_back(Task(line));
		}
	}
};
