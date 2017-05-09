// OOP345 Milestone 
// Date	2016/Mar.23 - Apr.
// EUNSUN KIM / OOP345-SAB/SAAL
////////////////////////////////////////////

#include <ciso646>    // for Visual Studio 2015
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>
#include <sstream>    // getline from string stream
#include <cctype>
#include <memory>
#include "csvreader.h"
#include "Task.h"
#include "Item.h"
#include "CustomerOrder.h"
#include "Job.h"
#include "Factory.h"
#include "Machine.h"

void LoadCsvreaderTest(const std::string, char);

int main(int argc, char** argv)
{
	//if command arguments are less than 3, then error 
	if (argc < 3)
	{
		std::cerr << "*** invalid number of arguments ***\n"
			<< "usage " << argv[0] << " tast_filename, delimetor\n";
		return 1;
	}

	//if user wants to implement 3 data files at once  (ex) milestone filename1.dat filename2.dat filename3.dat '|'
	if (argc > 3)
	{
		std::cout << "Command Line Arguments\n----------------------\n";
		std::cout << "Task File Specified           = " << argv[1] << "\n";
		std::cout << "Item File Specified           = " << argv[2] << "\n";
		std::cout << "Customer Order File Specified = " << argv[3] << "\n";
		std::cout << "File Record Field Delimiter   = " << argv[4][0] << "\n";
				
		char delimeter = argv[4][0];    //delimiter character a command line parameter
		
		std::string filetask = argv[1];
		//LoadCsvreaderTest(filetask, delimeter);	
		std::vector< std::vector<std::string> > csvTask;
		csvReader(filetask, delimeter, csvTask);
		
		// end of command line processing
		
	try
	{
		std::cout << "*****************************************************\n";
		std::cout << "           1. List of Available Tasks\n";
		
		// Task print using a range - based for loop to walk the vector list
		std::cout << "Task print using a range - based for loop to walk the\n"
			      << "vector list.\n";
		std::cout << "*****************************************************\n";
		
			for (auto line : csvTask)
			{
				Task t(line);
				t.display(std::cout);				
			}		

			std::cout << "\n*****************************************************\n";
			std::cout << "           Task print using a graphviz\n";
			std::cout << "*****************************************************\n";

			for (auto line : csvTask)
			{
				Task t(line);				
				t.gengraphviz(std::cout) ;				
			}		
			TaskManager tm;
			tm.parseTask(csvTask);
			tm.gengraphviz(filetask + std::string(".gv"));			
					
		std::cout << "*****************************************************\n";
		std::cout << "          2. List of Available Items\n";

		// Load, Accept and Display the Items
		std::cout << "Item print using a range - based for loop to walk the\n"
			<< "vector list.\n";
		std::cout << "*****************************************************\n";
		std::string fileitem = argv[2];		
		LoadCsvreaderTest(fileitem, delimeter);
		std::vector< std::vector<std::string> > csvItem;
		csvReader(fileitem, delimeter, csvItem);		

		for (auto line : csvItem)
			{
				Item i(line);
				i.display(std::cout);
			}
			std::cout << "\n*****************************************************\n";
			std::cout << "           Item print using a graphviz\n";
			std::cout << "*****************************************************\n";

			for (auto line : csvItem)
			{
				Item i(line);
				i.gengraphviz(std::cout);
			}	

			ItemManager im;
			im.parseItem(csvItem);
			im.gengraphviz(fileitem + std::string(".gv"));
		
		std::cout << "*****************************************************\n";
		std::cout << "           3. List of Customer Order\n";
		
		// Load, Accept and Display the CustomerOrders
		std::cout << "CustomerOrder print using a range - based for loop to\n"
			<< "walk the vector list.\n";
		std::cout << "*****************************************************\n";
		std::string fileorder = argv[3];
		LoadCsvreaderTest(fileorder, delimeter);
		std::vector< std::vector<std::string> > csvOrders;
		csvReader(fileorder, delimeter, csvOrders);
		
		for (auto line : csvOrders)
			{
				CustomerOrder coder(line);
				coder.display(std::cout);
			}
			std::cout << "\n*****************************************************\n";
			std::cout << "        CustomerOrder print using a graphviz\n";
			std::cout << "*****************************************************\n";

			for (auto line : csvOrders)
			{
				CustomerOrder coder(line);
				coder.gengraphviz(std::cout);
			}
			OrderManager om;
			om.parseOrderManager(csvOrders);
			om.gengraphviz(fileorder + std::string(".gv"));

			//****************************************************************
			
	//	std::string fileorder = argv[3];
	//	LoadCsvreaderTest(fileorder, delimeter);
	//	std::vector< std::vector<std::string> > csvOrders;
	//	csvReader(fileorder, delimeter, csvOrders);
	//	std::string fileitem = argv[2];
	//	LoadCsvreaderTest(fileitem, delimeter);
	//	std::vector< std::vector<std::string> > csvItem;
	//	csvReader(fileitem, delimeter, csvItem);
	//	TaskManager tm;
	//	tm.parseTask(csvTask);
	//	ItemManager im;
	//	im.parseItem(csvItem);
	//	OrderManager om;
	//	om.parseOrderManager(csvOrders);  // this blocks is for test

			std::cout << "*****************************************************\n";
			Factory f(move(tm), move(im), move(om));
			f.gengraphviz(std::string("m3") + std::string(".gv"));
		}
		catch (std::string& e) { std::cerr << "if failed: " << e << "\n"; }
		catch (std::exception& e) { std::cerr << "**if failed: " << e.what() << "\n"; }
	}
	
	//if user wants each data file to implement individually (ex) milestone filename.dat '|'
	else  
	{
		std::string filename(argv[1]);
		char delimeter = argv[2][0];                   //delimiter character a command line parameter
		std::cout << "*****************************************************\n";
		std::cout << "            [ File from the CSVreader ]\n";
		std::cout << "*****************************************************\n";
	
		LoadCsvreaderTest(filename, delimeter);
		std::vector< std::vector<std::string> > Datas;
		csvReader(filename, delimeter, Datas);
		ItemManager  im;
		OrderManager om;
		TaskManager tm;

		//****************************************************************
		//if "Task*.dat" is filename, this condition is implementated.
		// Load, Accept and Display the Tasks
		if (argv[1][0] == 'T' || argv[1][0] == 'F')  // (argv[1][0] == 'T' or 'F')
		{			
			std::cout << "*****************************************************\n";
			std::cout << "            List of Available Tasks\n";
			// end of command line processing

			// Task print using a range - based for loop to walk the vector list

			std::cout << "Task print using a range - based for loop to walk the\n"
				<< "vector list.\n";
			std::cout << "*****************************************************\n";
			try
			{
				for (auto line : Datas)
				{
					Task t(line);
					t.display(std::cout);
				}

				std::cout << "\n*****************************************************\n";
				//	std::cout << "           Task print using a graphviz\n";
				//	std::cout << "*****************************************************\n";

				for (auto line : Datas)
				{
					Task task(line);
					task.gengraphviz(std::cout);					
				}

				tm.parseTask(Datas);			
				tm.gengraphviz(filename + std::string(".gv"));				
			}
			catch (std::string& e) { std::cerr << "if failed: " << e << "\n"; }
			catch (std::exception& e) { std::cerr << "**if failed: " << e.what() << "\n"; }
		}

		//****************************************************************
		//if "Item*.dat" is filename, this condition is implementated.
		// Load, Accept and Display the Items
		if (argv[1][0] == 'I')
		{
			std::cout << "*****************************************************\n";
			std::cout << "            List of Available Items\n";

			// end of command line processing

			// Load, Accept and Display the Items

			std::cout << "Item print using a range - based for loop to walk the\n"
				<< "vector list.\n";
			std::cout << "*****************************************************\n";
			try
			{
				for (auto line : Datas)
				{
					Item i(line);
					i.display(std::cout);
				}
				std::cout << "\n*****************************************************\n";
				std::cout << "           Item print using a graphviz\n";
				std::cout << "*****************************************************\n";

				for (auto line : Datas)
				{
					Item i(line);
					i.gengraphviz(std::cout);
				}
				
				im.parseItem(Datas);				
				im.gengraphviz(filename + std::string(".gv"));
			}
			catch (std::string& e) { std::cerr << "if failed: " << e << "\n"; }
			catch (std::exception& e) { std::cerr << "**if failed: " << e.what() << "\n"; }
		}

		//****************************************************************
		//if "Customer*.dat" is filename, this condition is implementated.
		// Load, Accept and Display the CustomerOrders
		if (argv[1][0] == 'C')
		{
			std::cout << "*****************************************************\n";
			std::cout << "             List of Customer Order\n";

			// end of command line processing

			// Load, Accept and Display the CustomerOrders

			std::cout << "CustomerOrder print using a range - based for loop to\n"
				<< "walk the vector list.\n";
			std::cout << "*****************************************************\n";
			try
			{
				for (auto line : Datas)
				{
					CustomerOrder coder(line);
					coder.display(std::cout);
				}
				std::cout << "\n*****************************************************\n";
				std::cout << "        CustomerOrder print using a graphviz\n";
				std::cout << "*****************************************************\n";

				for (auto line : Datas)
				{
					CustomerOrder coder(line);
					coder.gengraphviz(std::cout);
				}
							
				om.parseOrderManager(Datas);
				om.gengraphviz(filename + std::string(".gv"));
			}
			catch (std::string& e) { std::cerr << "if failed: " << e << "\n"; }
			catch (std::exception& e) { std::cerr << "**if failed: " << e.what() << "\n"; }
		}
	}
	//****************************************************************
	// Terminate
std::cout << "Done!\n";
return 0;
}

void LoadCsvreaderTest(const std::string filename, char delimeter)
{
	std::vector< std::vector<std::string> > Tasks;
	csvReader(filename, delimeter, Tasks);

	std::cout << "++++ 3 methods test csvreader for milestone here ++++\n";
	std::cout << "\n";

	try    //  important!
	{
		std::cout << "-----------------------------------------------------\n";
		std::cout << "Method 1 - range - based for loop\n";
		std::cout << "-----------------------------------------------------\n";
		for (auto line : Tasks)
		{
			for (auto field : line)
			{
				std::cout << "-->";
				std::cout << field;
			}	std::cout << "\n";
		}	std::cout << "\n";
		std::cout << "-----------------------------------------------------\n";
		std::cout << "Method 2 - conventional for loop\n";
		std::cout << "-----------------------------------------------------\n";
		for (int line = 0; line < Tasks.size(); line++)
		{
			for (int field = 0; field < Tasks[line].size(); field++)
			{
				std::cout << "-->";
				std::cout << Tasks[line][field];
			}	std::cout << "\n";
		}	std::cout << "\n";
		std::cout << "-----------------------------------------------------\n";
		std::cout << "Method 3 - iterator for loop\n";
		std::cout << "-----------------------------------------------------\n";
		for (auto line = Tasks.begin(); line < Tasks.end(); line++)
		{
			for (auto field = line->begin(); field < line->end(); field++)
			{
				std::cout << "-->";
				std::cout << *field;
			}	std::cout << "\n";
		}	std::cout << "\n";
	}
	catch (std::string& e) { std::cerr << "if failed: " << e << "\n"; }
	catch (std::exception& e) { std::cerr << "**if failed: " << e.what() << "\n"; }		
}