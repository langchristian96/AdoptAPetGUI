#include "FileDoglist.h"

FileDoglist::FileDoglist(): DogList{},filename{""}
{

}

void FileDoglist::setFilename(const std::string& filename)
{
	this->filename = filename;
}