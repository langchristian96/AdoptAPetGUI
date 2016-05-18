#pragma once
#include "DogList.h"

class FileDoglist : public DogList
{
protected:
	std::string filename;
public:
	FileDoglist();
	virtual ~FileDoglist(){}
	void setFilename(const std::string& filename);
	virtual void writeToFile() = 0;
	virtual void displayDoglist() = 0;



};