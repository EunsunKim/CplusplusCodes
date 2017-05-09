// OOP345 Milestone - Task 
// File	Task.cpp
// Date	2016/Mar.22 - Apr
// Author	EUNSUN KIM / OOP345-SAB/SAAL
////////////////////////////////////////////
#include <ciso646>   //for visual studio
#include <string>
#include <exception>
#include <sstream>  // getline from string stream
#include <cctype>   //isalnum
#include <iomanip> 
#include <fstream>  
#include <algorithm>
#include "Task.h"

using namespace std;
size_t Task::field_width=1;

Task::Task() :TaskName(""), Slots("1") 
{
	for (auto& e : nextTask) e.clear();
	for (auto& e : pNextTask) e = nullptr;
};
Task::Task(vector<string>& fields) 
	{ // validate functions for Taskname, Slots, Installer, and Failed 
		for (auto& e : nextTask) e.clear();
		for (auto& e : pNextTask) e = nullptr;

		auto isTaskName = [](string& s) -> bool
		{	
			if ((isalpha((int)s[0]) != 0) || (s[0] == '_'))
			{
				for (size_t i = 0; i < s.size(); i++)
				{
					if ((isalnum(s[i]) == 0) && (s[i] != ' ') && (s[i] != '_'))
					{
						//cout << "error s[" << i << "] :" << s[i] << endl;  //error check
						return false;
					}
				}
				return true;
			}
			return false;
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

		auto error = [](string errorType, string expected, string found)
		{
			throw errorType + " expected " + expected + " found " + found;
		}; //error message

		 // put Task's each data string members  to each field after validate
		switch (fields.size()) 
		{
		case 4:
			if (not fields[3].empty() and isTaskName(fields[3]))   			
				//Failed = fields[3];
				nextTask[Failed] = fields[3];
			else
				error(string("empty "), string("task name "), fields[3]);
		case 3:
			if (not fields[2].empty() and isTaskName(fields[2]))
				nextTask[Installer] = fields[2];
			else
				error(std::string("lookng for 'Installer' "), string("task name "), fields[2]);
		case 2:
			if (not fields[1].empty() and isNumber(fields[1]))
				Slots = fields[1];
			else
				error(std::string("lookng for 'Slots' "), string("number "), fields[1]);
		case 1:
			if (not (fields[0].empty()) and isTaskName(fields[0]))
				TaskName = fields[0];
			else
				error(string("*** to be validated ***"), string("task name "), fields[0]);		
		break;	
		default:
			error(string("fields count not correct "), string("1,2,3, or 4 fields "), to_string(fields.size()) + std::string("fields"));
			//continue;  //if loop exist
		}				
	}

const string& Task::getName() const { return TaskName; }
const std::string& Task::getPassed() const { return nextTask[Installer]; }
const std::string& Task::getFailed() const { return nextTask[Failed];}

/*
validate a next task in the current object by comparing the Task referenced
in its parameter to the next tasks stored upon instantiation.
If one of these tasks has the same name as that referenced,
this function sets the corresponding pointer to the address of the referenced task.
*/
bool Task::validate(const Task& t)
{
	if (!pNextTask[Installer] && !nextTask[Installer].compare(t.TaskName))
		pNextTask[Installer] = &t;

	if (!pNextTask[Failed] && !nextTask[Failed].compare(t.TaskName))
		pNextTask[Failed] = &t;

	return (nextTask[Installer].empty() || pNextTask[Installer]) &&
		(nextTask[Failed].empty() || pNextTask[Failed]);
}

/*
 returns the address of the next task depending on the parameter received.
 if the addressed of that next task has not been determined (by validate()) 
 reports can show error ..
*/
const Task* Task::getNextTask(Quality q) const
{
	if (!pNextTask[q])
		throw std::string("*** Validate  [") + nextTask[q] + std::string("] @ [") + TaskName + std::string("] ***");

	return pNextTask[q];
}

void Task::display(std::ostream& os) const
{
	size_t FieldWidth = field_width + 2;
	string quote(R"(")");

	if (not TaskName.empty())
		os << "Task Name    : " << left << std::setw(18) << quote + TaskName + quote;
	if (not Slots.empty())
		os << "-->  Slots : " << quote << Slots << quote << std::endl;
	else
		os << std::endl;
	if (not nextTask[Installer].empty())
		os << "    Passed --> " << quote + nextTask[Installer] + quote << std::endl;
	if (not nextTask[Failed].empty())
		os << "    Failed --> " << left << std::setw(18) << quote + nextTask[Failed] + quote << "to be validated " << std::endl;

} // end Task display


// beginning gengraphviz for Task
void Task::gengraphviz(std::ostream& os) const     
{
	string quote(R"(")");
	string str_taskname = quote + TaskName + quote;  //fixed 04/03/2016
	string str_slots = quote + Slots + quote;
	string str_installer = quote + nextTask[Installer] + quote;
	string str_failed = quote + nextTask[Failed] + quote;
		
	if (not nextTask[Installer].empty() and nextTask[Failed].empty())
		os << " " << str_taskname << "->" << str_installer << "[color=green]\n";
	
	if (not nextTask[Failed].empty())
	{
		os << " " << str_taskname << "->" << str_installer << "[color=green]\n";
		os << " " << str_taskname << "->" << str_failed << "[color=red]\n";
	}	
}  //gengraphviz

void TaskManager::display(std::ofstream& os) const
{
	for (auto Task : *this)  
		Task.display(cout);
} // end TaskManager display

void TaskManager::gengraphviz(std::string filename)
{
	ofstream of(filename, ios::out);
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
		of << R"foo( \n< Eunsun Kim >OOP345 Milestone\n2016\nTask Relation Diagram drawn by Graphviz";
            fondsize=30;)foo";
		of << "}\n";
	}
} //end TaskManager gengraphviz for label and description

 