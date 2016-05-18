#pragma once
#include "Repository.h"
#include <string>
#include "DogList.h"
#include "FileDoglist.h"
#include "DogValidator.h"
class Controller
{
private:
	Repository repo;
	DogValidator validator;
	FileDoglist* adoption;	//Used for adoption list
	DogList allDogs;	//Used for showing the database of dogs
	DogList breed;	//Used for showing the dogs from the database that have a given breed and age less than a given number
public:

	Controller(const Repository& r, FileDoglist* p, const DogValidator& validator) : repo(r), adoption{ p }, validator(validator) {}
	Repository getRepo() const { return repo; }

	DogList getDogList() const { return allDogs; }	//Getter for DogList allDogs

	DogList* getAdoptionList() const { return adoption; }	//Getter for DogList adoption
	DogList getBreedList() const { return breed; }	//Getter for DogList breed
	void addDogToAll(const Dog& dog);	//Adds a dog to the DogList allDogs
	void addDogToAdoption(const Dog& dog);	//Adds a dog to the DogList adoption
	void addDogToBreed(const Dog& dog);	//Adds a dog to the DogList breed

	void addAllDogs();	//Adds all the dogs from the repo to the DogList allDogs
	void cleanBreed();	//Cleans the DogList(deletes all the dogs from it)
	void addDogsByBreedAndAge(const std::string& breed, int age);	//Adds all the dogs of a given breed and
																	//with age less than a given number to the DogList allDogs
	void saveDoglist(const std::string& filename);

	void openDoglist() const;
	int addDogToRepository(const std::string& breed, const std::string& name, const int age, const std::string& photograph);
	/*
	Adds a dog to the repository
	Input: breed - string
			name - string
			age - int
			photograph - string
	Output: 0 - if the dog with the given info was added to the repo
			-1 - if the dog with the given name already exists
	*/


	void updateDogToRepository(const std::string& breed, const std::string& name, const int age, const std::string& photograph);
	/*
	Updates a dog to the repository
	Input: breed - string
	name - string
	age - int
	photograph - string
	Output: the dog with the given info is updated to the repo if it exists
	*/


	int removeDogFromRepository(const std::string& name);
	/*
	Removes a dog from the repository
	Input: 
	name - string
	Output: 0 - if the dog with the given info was removed from the repo
			-1 - if the dog with the given name already exists
	*/


	void startDogList();	//Starts the DogList allDogs
	void nextDogList();		//Goes to the next dog from the DogList allDogs
	void startAdoptionList();	//Starts the DogList adoption
	void nextAdoptionList();	//Goes to the next from from the DogList adoption
	void startBreedList();		//Starts the DogList breed
	void nextBreedList();		//Goes to the next dog from the DogList breed

};

void testController();	//tester for Controller
