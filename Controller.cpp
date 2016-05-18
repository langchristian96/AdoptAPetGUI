#include "Controller.h"
#include "DynamicVector.h"
#include "Dog.h"
#include "CSVDoglist.h"
#include <assert.h>
int Controller::addDogToRepository(const std::string& breed, const std::string& name, const int age, const std::string& photograph)
{
	int rez;
	Dog s{ breed,name,age,photograph };

	this->validator.validate(s);
	rez=this->repo.addDog(s);
	return rez;
}

void Controller::updateDogToRepository(const std::string& breed, const std::string& name, const int age, const std::string& photograph)
{

	Dog s{ breed,name,age,photograph };
	this->validator.validate(s);
	this->repo.updateDog(s);

}
void Controller::cleanBreed()
{
	this->breed.cleanDogList();
}

int Controller::removeDogFromRepository(const std::string& name)
{
	int rez;
	Dog s{ "",name,0,"" };
	rez=this->repo.deleteDog(s);
	return rez;
}


void Controller::addDogToAll(const Dog& dog)
{
	this->allDogs.add(dog);

}
void Controller::addDogToAdoption(const Dog& dog)
{
	std::vector<Dog> v = this->adoption->getDogs();
	for (int i = 0; i < v.size(); i++)
	{
		if (dog.getName() == v[i].getName())
			return;
	}
	this->adoption->add(dog);
}
void Controller::addDogToBreed(const Dog& dog)
{
	this->breed.add(dog);
}


void Controller::addAllDogs()
{

	std::vector<Dog> v = this->repo.getDogs();
	for (int i = 0; i < v.size(); i++)
	{
		this->allDogs.add(v[i]);



	}
}

void Controller::addDogsByBreedAndAge(const std::string& breed, int age)
{
	std::vector<Dog> v = this->repo.getDogs();
	for (int i = 0; i < v.size(); i++)
	{
		Dog d = v[i];
		if (d.getBreed() == breed&&d.getAge() <= age)
			this->addDogToBreed(v[i]);



	}
}
void Controller::saveDoglist(const std::string& filename)
{
	if (this->adoption == nullptr)
		return;
	this->adoption->setFilename(filename);
	this->adoption->writeToFile();

}

void Controller::openDoglist() const
{
	if (this->adoption == nullptr)
		return;
	this->adoption->displayDoglist();
}

void Controller::startDogList()
{
	this->allDogs.startPhoto();
}
void Controller::nextDogList()
{
	this->allDogs.next();
}
void Controller::startAdoptionList()
{
	this->adoption->startPhoto();
}
void Controller::nextAdoptionList()
{
	this->adoption->next();

}
void Controller::startBreedList()
{
	this->breed.startPhoto();
}
void Controller::nextBreedList()
{
	this->breed.next();
}


void testController()
{

	Repository repo("test.txt");

	FileDoglist* p = new CSVDoglist{};
	Controller ctrl(repo,p, DogValidator{});
	std::vector<Dog> v = repo.getDogs();
	assert(v.size() == 0);


	ctrl.addDogToRepository("metis", "Patrocle", 1, "www.google.ro");

	v = ctrl.getRepo().getDogs();
	assert(v.size() == 1);
	ctrl.removeDogFromRepository("Patrocle");

	v = ctrl.getRepo().getDogs();
	assert(v.size() == 0);


}