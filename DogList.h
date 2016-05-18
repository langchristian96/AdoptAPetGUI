#pragma once
#include "DynamicVector.h"
#include <vector>

class DogList
{
protected:
	std::vector<Dog> dogs;
	int current;
public:
	DogList();

	void add(const Dog& dog); //adds a dog to the DogList

	Dog getCurrentDog();
	void cleanDogList();
	void startPhoto();
	std::vector<Dog> getDogs();
	int getNumberOfDogs() { return dogs.size(); }
	void next();

	bool isEmpty();


};