// OOP345 Milestone - CSVreader
// csvreader.cpp
// Date	2016/Mar.23 - Apr.
// EUNSUN KIM / OOP345-SAB/SAAL
////////////////////////////////////////////
#pragma once
#include <ciso646>  // for Visual Studio 2015
#include <iostream>
#include <vector>
#include "Task.h"
#include "Item.h"
#include "CustomerOrder.h"

std::string& trim(std::string& s);
void csvReader(std::string fileName, char delimiter, std::vector< std::vector<std::string> >& data);
