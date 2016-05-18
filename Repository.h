#pragma once
#include "Dog.h"
#include "DynamicVector.h"
#include <vector>


class Repository
{
private:
	std::vector<Dog> dogs;
	std::string filename;

public:
	Repository(const std::string& filename); //Constructor with parameters; initializes repo with dogs from a given file
	int addDog(const Dog& s);
	/*
	Adds a dog to the repo
	Input:s - dog
	Output: the dog is added to the repository
	*/

	void updateDog(const Dog& s);
	/*
	Updates a dog to the repo
	Input:s - dog
	Output: the dog is updated to the repository
	*/

	int deleteDog(const Dog& s);

	/*
	Deletes a dog from the repo
	Input:s - dog
	Output: the dog is deleted from the repository
	*/

	std::vector<Dog> getDogs() const { return dogs; }
	//Returns the DynamicVector dogs

private:
	void readFromFile();//reading from file
	void writeToFile();//writing to file


};


void testRepository();	//tester for Repository