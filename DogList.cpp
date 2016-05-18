#include "DogList.h"


DogList::DogList()
{
	this->current = 0;
}

std::vector<Dog> DogList::getDogs()
{
	return this->dogs;
}


void DogList::add(const Dog& dog)
{

	this->dogs.push_back(dog);

}

void DogList::cleanDogList()
{
	this->dogs.erase(dogs.begin(), dogs.end());
}

Dog DogList::getCurrentDog()
{
	if (this->current == this->dogs.size())
		this->current = 0;
	if(dogs.size()!=0)
		return dogs[this->current];
	return Dog{};


}


void DogList::startPhoto()
{
	if (this->dogs.size() == 0)
		return;
	this->current = 0;
	Dog currentDog = this->getCurrentDog();
	currentDog.seePhotograph();

}


void DogList::next()
{
	if (this->dogs.size() == 0)
		return;
	this->current++;
	Dog currentDog = this->getCurrentDog();
	currentDog.seePhotograph();


}

bool DogList::isEmpty()
{
	return this->dogs.size() == 0;
}