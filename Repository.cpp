#include "Repository.h"
#include <string>
#include <fstream>
#include "Utils.h"
#include <assert.h>
#include <iostream>
#include "RepositoryException.h"

using namespace std;
Repository::Repository(const std::string& filename)
{
	this->filename = filename;
	this->readFromFile();
}

int Repository::addDog(const Dog& s)
{

	std::string name = s.getName();
	for (auto i:dogs)
	{
		if (i.getName() == name)
		{
			throw DuplicateDogException();
		}
	}
	this->dogs.push_back(s);
	this->writeToFile();
	return 0;

}


void Repository::updateDog(const Dog& s)
{
	std::string name = s.getName();
	for (std::vector<Dog>::iterator i = dogs.begin(); i != dogs.end();i++)
	{
		if (i->getName() == name)
		{
			dogs.erase(i);
			dogs.push_back(s);

			this->writeToFile();
			return;
		}
	}

}

int Repository::deleteDog(const Dog& s)
{

	int exists = 0;
	std::string name = s.getName();
	for (std::vector<Dog>::iterator i = dogs.begin(); i != dogs.end(); i++)
	{
		if (i->getName() == name)
		{
			exists = 1;
			dogs.erase(i);

			this->writeToFile();
			return 0;
		}
	}

	throw RepositoryException("The dog with the given name does not exist!\n");

}

void Repository::readFromFile()
{
	ifstream file(this->filename);
	if (!file.is_open())
		throw FileException("The file could not be opened!");
	Dog s;
	while (file >> s)
	{
		if(s.getName()!="")
			this->dogs.push_back(s);
	}
	file.close();

}

void Repository::writeToFile()
{
	ofstream file(this->filename);
	if (!file.is_open())
		throw FileException("The file could not be opened!");

	for (auto s : this->dogs)
	{
		file << s;
	}

	file.close();


}

void testRepository()
{
	Repository repo("test.txt");
	Dog d{ "metis","patrocle",1,"google.ro" };
	std::vector<Dog> v = repo.getDogs();
	assert(v.size() == 0);
	repo.addDog(d);
	v = repo.getDogs();
	assert(v.size() == 1);
	repo.deleteDog(d);

	v = repo.getDogs();
	assert(v.size() == 0);

}