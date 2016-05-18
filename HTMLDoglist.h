#pragma once
#include "FileDoglist.h"
#include <string>

class HTMLDoglist :public FileDoglist
{
public:
	void writeToFile() override;

	void displayDoglist() override;


};