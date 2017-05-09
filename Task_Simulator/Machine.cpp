// OOP345 Milestone - Machine
// File	Machine.cpp
// Date	2016/Apr.
// Author	EUNSUN KIM / OOP345-SAB/SAAL
////////////////////////////////////////////
#include <iostream>
#include <queue>
#include <vector>   
#include <algorithm>
#include "Task.h"
#include "Item.h"            //ItemManager for sorting out installer/remover capability
#include "CustomerOrder.h"
#include "Job.h"
#include "Machine.h"

using namespace std;

Machine::Machine(Task& tt, ItemManager& im): Task(tt),bInstaller(false),bRemover(false),bSource(false)
{ 
	m_Name = tt.getName();
	Classify(im);	
}

void Machine::push(Job&& j) { m_qInputQ.push(move(j)); }

void Machine::print(std::ostream& os) 
{ 
	os << "Machine " << m_Name << "\n";
	if (bInstaller)	os << "instraller\n";
	if (bRemover)	os << "remover\n";
	if (isSink())	os << "sink\n";
}

void Machine::Classify(ItemManager& im) 
{
	for (auto it = im.begin(); it != im.end(); it++)
	{
		if (m_Name == it->getInstaller())   //Item class
		{
			bInstaller = true;
		}
		else if (m_Name == it->getRemover())     //Item class
		{
			bRemover = true;
		}
	}
	if (bInstaller && bRemover)
		throw m_Name + " is both an installer and a remover. Fix item data and resubmit.";
}

void Machine::Run(ItemManager& im, std::vector<Machine>& machineList)
{
	cout << "Machine::Run: " << m_Name << "\n";

	if (m_qInputQ.empty())
		return;                     //nothing to do

	m_Job = move(m_qInputQ.front());
	m_qInputQ.pop();

	cout << "\n";
	std::cout << "*****************************************************\n";
	cout << "Job = "; 
	m_Job.print(cout);
	std::cout << "*****************************************************\n";

	if (isSink())
	{
		m_Job.completed();
		cout << "'" << m_Job.getProductName() << "'" << " completed for customer  '" << m_Job.getCustomerName() << "\n";

		///////////////////////////////
		//if job is complete, get PruductName and CustomerName from CustomerOrder class
		//if (m_Job.isComplete())
		//{  //all done with job
		//	cout << "'" << m_Job.getProductName() << "'"
		//		<< " completed for customer  '" << m_Job.getCustomerName() << "\n";
		//}
		//else {
		//	throw std::string("job at sink node ") + m_Name + " but job is not complete";
		//}
	} // end isSink()
	else
	{
		bool bJobDone = true;

		if (isInstallRequired())
		{
			bJobDone = false;

			if (installItem(im))
			{
				bJobDone = true;
			}
		}

		if (isRemoveRequired())
		{
			bJobDone = false;

			if (removeItem(im))
			{
				bJobDone = true;
			}
		}

		bool bPassed = false;

		if (bJobDone)
		{
			if (inspector())
			{
				// passed
				m_qPassedJob.push(move(m_Job));
				bPassed = true;
			}
			else
			{
				if (flip_a_coin())  // <-------------------  flip_a_coin()
				{
					// passed
					m_qPassedJob.push(move(m_Job));
					bPassed = true;
				}
			}
		}

		if (!bPassed)
		{
			m_qFailedJob.push(move(m_Job));
		}

		auto route = [&machineList](Job& job, string des)
		{
			for (auto m = machineList.begin(); m < machineList.end(); m++)
			{
				if (m->getName() == des)
				{
					m->push(move(job));
					cout << "route\n";
				}
			}
		};
		string passed = getPassed();	// getNextInstaller
		string failed = getFailed();	// getNextRemover

		route((bPassed) ? m_qPassedJob.back() : m_qFailedJob.back(), (isRemoveRequired()) ? failed : passed);
	}
	return;
}


void Machine::setAsSource(bool bThisIsSource)
{
	bSource = bThisIsSource;
}
bool Machine::isSource()
{
	return bSource;
}

bool Machine::isSink()
{
	std::string sPassed = this->getPassed();
	std::string sFailed = this->getFailed();

	if ((sPassed.empty())
		&& (sFailed.empty()))
	{
		return true;
	}
	return false;
}

bool Machine::isInstallRequired()
{
	return bInstaller;
}

bool Machine::isRemoveRequired()
{
	return bRemover;
}

bool Machine::installItem(ItemManager& itemManager)
{
	bool bSucceeded = false;

	std::vector<std::string>& vOrderedItems = m_Job.getItemsOrdered();
	std::cout << vOrderedItems.size() << " items ordered\n";

	for (std::vector<std::string>::iterator itrItem = vOrderedItems.begin(); itrItem != vOrderedItems.end(); itrItem++)
	{
		std::string	sItemName = (*itrItem);
		Item*		pItem = itemManager.find((*itrItem));

		if (pItem == nullptr)
		{
			std::cout << "no item found -> " << sItemName << std::endl;
		}
		else if (pItem->getInstaller() == m_Name)  //remover field eg CPU
		{
			m_Job.Install(itrItem - vOrderedItems.begin());
			bSucceeded = true;
		}
		else
		{
			std::cout << "item -> " << sItemName << " <- needs installer " << pItem->getInstaller() << "\n";
		}
	}

	return bSucceeded;
}

bool Machine::removeItem(ItemManager& itemManager)
{
	bool bSucceeded = false;

	std::vector<std::string>& vOrderedItems = m_Job.getItemsOrdered();
	std::cout << vOrderedItems.size() << " items ordered\n";

	for (std::vector<std::string>::iterator itrItem = vOrderedItems.begin(); itrItem != vOrderedItems.end(); itrItem++)
	{
		std::string	sItemName = (*itrItem);
		Item*		pItem = itemManager.find((*itrItem));

		if (pItem == nullptr)
		{
			std::cout << "no item found -> " << sItemName << std::endl;
		}
		else if (pItem->getRemover() == m_Name)  //remover field eg CPU
		{
			m_Job.Remove(itrItem - vOrderedItems.begin());
			bSucceeded = true;
		}
		else
		{
			std::cout << "item -> " << sItemName << " <- needs remover " << pItem->getRemover() << "\n";
		}
	}
	return bSucceeded;
}

bool Machine::inspector()
{
	std::string strRemoverName = getFailed();
	return (strRemoverName.empty());
}

bool Machine::flip_a_coin()
{
	return (rand() % 2);
}

bool Machine::isJobCompleted()
{
	if (m_qInputQ.empty())
	{
		if (m_Job.isComplete())
		{
			return true;
		}
	}
	return false;
}