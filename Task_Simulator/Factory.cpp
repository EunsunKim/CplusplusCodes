// OOP345 Milestone - Factory
// File	Factory.cpp
// Date	2016/Apr.
// Author	EUNSUN KIM / OOP345-SAB/SAAL
////////////////////////////////////////////
#include <ciso646>      // for Visual Studio 2015
#include <iostream>
#include <vector> 
#include <cstring>
#include <utility>      // std::move
#include <exception>
#include <fstream>
#include "Task.h"
#include "Item.h"
#include "CustomerOrder.h"
#include "Job.h"
#include "Machine.h"
#include "Factory.h"

using namespace std;

Factory::Factory(TaskManager&& TM, ItemManager&& IM, OrderManager&& OM )
		: tm(move(TM)), im(move(IM)), om(move(OM))
	{
		//////////////////////////////////////////////
		//step1 - load machine, one machine per task//
		//////////////////////////////////////////////

		for (size_t m = 0; m < tm.size(); m++)
		{
			machineList.push_back(Machine(tm.at(m), im));			
		}  //std::vector::at   reference at(size_type n);


		// Way #1
		//for (vector<Machine>::iterator itrMachine = machineList.begin(); itrMachine != machineList.end(); ++itrMachine)
		//{
		//	bool bIsSource = true;

		//	for (vector<Machine>::iterator itrMachineToFind = machineList.begin(); itrMachineToFind != machineList.end(); ++itrMachineToFind)
		//	{
		//		if (itrMachine == itrMachineToFind)
		//		{
		//			continue;
		//		}

		//		if ((itrMachineToFind->getNextTask(Machine::Installer) == &(*itrMachine))
		//			|| (itrMachineToFind->getNextTask(Machine::Failed) == &(*itrMachine)))
		//		{
		//			bIsSource = false;
		//			break;
		//		}
		//	}

		//	itrMachine->setAsSource(bIsSource);
		//}

		// Way #2
		for (size_t iIndex = 0; iIndex < machineList.size(); ++iIndex)
		{
			bool bIsSource = true;

			for (size_t jIndex = 0; jIndex < machineList.size(); ++jIndex)
			{
				if (iIndex == jIndex)
				{
					continue;
				}

				string sPassed = machineList[jIndex].getPassed();
				string sFailed = machineList[jIndex].getFailed();

				if ((sPassed == machineList[iIndex].getName())
					|| (sFailed == machineList[iIndex].getName()))
				{
					bIsSource = false;
					break;
				}
			}

			machineList[iIndex].setAsSource(bIsSource);
		}


		
		///////////////////////////////
		//step2 - find source machine//
		///////////////////////////////
		//Find the source node for the machine network
		enum { SOURCE_NOT_FOUND = -1 };
		int sourceMachine = SOURCE_NOT_FOUND;
		
		for (size_t m = 0; m < machineList.size(); m++)
		{
			if (machineList.at(m).isSource() and not machineList.at(m).isSink())			
			{
				if (sourceMachine == -1) //found 1st source
				{  //keep checking to see if there are duplicate sources
					sourceMachine = m;
				}
				else
				{ throw("cannot build factory: multiple source nodes, fix data and resubmit");}
			}
		}
		if (sourceMachine == SOURCE_NOT_FOUND)
		throw string("cannot build factory: NO source node, fix data and resubmit");

		cout << "Source machine =  " << sourceMachine << "\n";		
		tm.at (sourceMachine).display(cout);
		cout << "\n";
		// end step2 - find source machine

		//////////////////////////////////////////////////////////////
		// step3 - load jobs into source machine, one job per order //
		//////////////////////////////////////////////////////////////

		for (size_t j = 0; j < om.size(); j++)
		{
			machineList.at(sourceMachine).push(move(Job(om.at(j))));			
		}

		///////////////////////
		// step4 - Time loop //
		///////////////////////
		while (true)
		{
			// look for incomplete jobs
			bool notFinished = false;
			for (size_t m = 0; m < machineList.size(); m++)
			{
				if (machineList[m].isSink())
				{
					if (!machineList[m].isJobCompleted())
					{
						notFinished = true;
						break;
					}
				}
				else
				{
					if (!machineList[m].isJobCompleted())
					{
						notFinished = true;
						break;
					}
				}
			}

			if (not notFinished)
				break; //all done. Simulation over

		//////////////////////////
		// step5 - Machine loop //
		//////////////////////////
			for (size_t m = 0; m < machineList.size(); m++)
			{				
				machineList[m].Run(im, machineList);
			}
			//break;///for test
		} //end while loop  Factory finish		
}

void Factory::gengraphviz(std::string filename)
{
	std::ofstream os(filename.c_str(), std::ios::out);
	if (os.is_open())
	{
		os << "digraph m3 {\n";
		os << R"(node[style="filled", fillcolor="grey"])";
		os << R"(edge[color=blue];)";
		os << "\n";
		std::string quote(R"(")");
		os << "\n";

		//subgraph timeLoop here

		os << "subgraph timeLoop {\n";
		os << R"(node[style="filled", fillcolor="grey"])";
		os << "\n";

		std::string str_create_factory = quote + "Create Factory" + quote;
		std::string str_find_source = quote + "Find Source" + quote;
		os << " " << str_create_factory << "->" << str_find_source << "\n";
		os << "\n";
		os << " " << str_find_source << "[shape=box]\n";
		std::string str_load_input = quote + "Load jobs into source node input Q" + quote;
		os << " " << str_find_source << "->" << str_load_input << "\n";
		os << "\n";
		os << " " << str_load_input << "[shape=box]\n";
		std::string str_time_loop = quote + "Time Loop" + quote;
		os << " " << str_load_input << "->" << str_time_loop << "\n";
		os << "\n";
		os << " " << str_time_loop << "[shape=box]\n";
		std::string str_incomplete_job = quote + "Incomplete jobs?" + quote;
		os << " " << str_time_loop << ":e->" << str_incomplete_job << "\n";
		os << "\n";
		os << " " << str_incomplete_job << "[shape=diamond]\n";
		os << "\n";
		std::string str_end_time_loop = quote + "End Time Loop" + quote;
		os << " " << str_end_time_loop << "->" << str_time_loop << "[color=blue]\n";
		os << "\n";
		os << " " << str_end_time_loop << "[shape=box][fillcolor=grey]\n";
		os << "}\n";  // end subgraph timeLoop
		os << "\n";
		os << "\n";
		//start subgraph machineLoop here
		os << "subgraph machineLoop {\n";
		os << R"(node[style="filled", fillcolor="green"])";
		os << "\n";

		std::string str_machine_loop = quote + "Machine Loop" + quote;
		os << " " << str_machine_loop << "[shape=box]\n";
		os << "\n";
		std::string str_qempty = quote + "Input Q empty?" + quote;
		os << " " << str_machine_loop << "->" << str_qempty << "\n";
		os << "\n";
		os << " " << str_qempty << "[shape=diamond]\n";
		std::string str_remove_job = quote + "Remove job from input Q" + quote;
		os << " " << str_qempty << "->" << str_remove_job << "\n";
		os << "\n";
		std::string str_end_machine_loop = quote + "End Machine Loop" + quote;
		os << " " << str_end_machine_loop << "[shape=diamond][fillcolor=green]\n";
		os << " " << str_qempty << ":e->" << str_end_machine_loop << "\n";
		os << "\n";
		os << " " << str_remove_job << "[shape=box]\n";
		std::string str_sink = quote + "Sink?" + quote;
		os << " " << str_remove_job << "->" << str_sink << "\n";
		os << "\n";
		os << " " << str_sink << "[shape=diamond]\n";
		std::string str_mark = quote + "Mark job complete" + quote + "\n" + quote + "Ready to ship" + quote;
		os << " " << str_sink << "->" << str_mark << "\n";
		os << "\n";
		std::string str_q_install_item = quote + "Install item?" + quote;
		os << " " << str_sink << "->" << str_q_install_item << "[color=red]\n";
		os << "\n";
		os << " " << str_q_install_item << "[shape=diamond]\n";
		os << " " << str_mark << "[shape=box]\n";
		os << "\n";
		os << " " << str_mark << "->" << str_end_machine_loop << "[color=blue]\n";
		os << "\n";
		std::string str_install_item = quote + "Install item" + quote;
		std::string str_q_remove_item = quote + "Remove item?" + quote;
		std::string str_remove_item = quote + "Remove item" + quote;
		os << "\n";
		os << " " << str_q_install_item << ":w->" << str_install_item << "[color=blue]\n";
		os << " " << str_q_install_item << ":e->" << str_q_remove_item << "[color=red]\n";
		os << " " << str_q_remove_item << ":w->" << str_remove_item << "[color=blue]\n";
		os << "\n";
		os << " " << str_install_item << "[shape=diamond]\n";
		os << " " << str_remove_item << "[shape=box]\n";
		os << "\n";
		std::string str_inspector = quote + "Inspector" + quote;
		os << " " << str_install_item << "->" << str_inspector << "[color=blue]\n";
		os << "\n";
		os << " " << str_inspector << "[shape=box]\n";
		std::string str_move_passed = quote + "Move job to passed machine input Q" + quote;
		os << "\n";
		os << " " << str_q_remove_item << ":e->" << str_move_passed << "[color=red]\n";
		os << "\n";
		os << " " << str_q_remove_item << "[shape=diamond]\n";
		os << " " << str_move_passed << "[shape=box]\n";
		os << " " << str_remove_item << "->" << str_inspector << "[color=blue]\n";
		os << "\n";
		std::string str_passed = quote + "Only Passed?" + quote;
		std::string str_coin = quote + "Flip a coin" + quote;
		os << "\n";
		os << " " << str_inspector << "->" << str_passed << "[color=blue]\n";
		os << "\n";
		os << " " << str_passed << "[shape=diamond]\n";
		os << " " << str_coin << "[shape=diamond]\n";
		os << " " << str_passed << ":e->" << str_move_passed << "[color=blue]\n";
		os << " " << str_passed << ":w->" << str_coin << "[color=red]\n";
		os << "\n";
		os << " " << str_move_passed << "->" << str_end_machine_loop << "[color=blue]\n";
		os << "\n";
		std::string str_move_failed = quote + "Move job to failed machine input Q" + quote;
		os << "\n";
		os << " " << str_move_failed << "[shape=box]\n";
		os << " " << str_coin << ":e->" << str_move_passed << "[color=blue]\n";
		os << " " << str_coin << ":w->" << str_move_failed << "[color=red]\n";
		os << "\n";
		os << " " << str_move_failed << "->" << str_end_machine_loop << "[color=blue]\n";
		os << " " << str_end_machine_loop << "->" << str_machine_loop << "[color=blue]\n";
		os << "}\n";  // end subgraph machine
		os << "\n";
		os << "\n";
		//node and edges outside of subgraph
		os << R"(node[style="filled", fillcolor="yellow"])";
		os << "\n";

		std::string str_start = quote + "START" + quote;
		os << " " << str_start << "[shape=hexagon][fillcolor=yellow]\n";
		os << "\n";

		//std::string str_create_factory = quote + "Create Factory" + quote;
		os << " " << str_start << "->" << str_create_factory << "\n";
		os << " " << str_create_factory << "[shape=box]\n";
		os << "\n";
		std::string str_done = quote + "ALL DONE" + quote;
		os << " " << str_done << "[shape=polygon,sides=6][fillcolor=yellow]\n";
		os << " " << str_incomplete_job << ":e->" << str_done << "[color=red]\n";
		os << "\n";
		// edges from time loop subgraph to machine loop subgraph
		os << " " << str_incomplete_job << ":s->" << str_machine_loop << "[color=blue]\n";
		os << "\n";
		// edges from machine loop subgraph to time loop subgraph
		os << " " << str_end_machine_loop << ":s->" << str_end_time_loop << "[color=blue]\n";
		os << "\n";
				
		os << R"foo(label = " )foo";
		os << filename;
		os << R"foo(\n< Eunsun Kim >OOP345 Milestone3\nMINIMAL VIABLE SKELETON FACTORY drawn by Graphviz\n2016";
		fondsize=30;)foo";
		os << "}\n";
	}
}
/*
int IntegrityCheck(ItemManager& im, OrderManager& om, TaskManager& tm)
{
	int errorCount = 0;
	//for each item, check task installer + remover exist
	for (auto item = im.begin(); item < im.end(); item++)
	{
		if (tm.Find (item->getInstaller()) == nullptr)
		{
			errorCount++;
			cerr << "Item <" << item->getItemsOrdered() << "> needs installer <" << item->getInstaller() << ">";
		}
	}
}
*/