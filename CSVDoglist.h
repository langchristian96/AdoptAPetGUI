#pragma once
#include "FileDoglist.h"
#include <string>

class CSVDoglist :public FileDoglist
{
public:
	void writeToFile() override;

	void displayDoglist() override;


};