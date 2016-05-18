#include "Dog.h"
#include <Windows.h>
#include <iostream>
#include <assert.h>

#include <shellapi.h>
using namespace std;


Dog::Dog() : breed(""), name(""), age(0), photograph("") {}
Dog::Dog(const std::string& breed, const std::string& name, const int age, const std::string& photograph)
{
	this->breed = breed;
	this->name = name;
	this->age = age;
	this->photograph = photograph;
}

void Dog::seePhotograph()
{
	ShellExecuteA(NULL, NULL, "chrome.exe", this->getPhotograph().c_str(), NULL, SW_SHOWMAXIMIZED);
}


istream & operator>>(istream & is, Dog & s)
{
	string line;
	getline(is, line);

	vector<string> tokens = tokenize(line, '|');
	if (tokens.size() != 4) // make sure all the dog data was valid
		return is; 
	s.breed = tokens[0];
	s.name = tokens[1];

	s.age = stod(tokens[2]);
	s.photograph = tokens[3];

	return is;

}

ostream & operator<<(ostream & os, const Dog & s)
{
	os << s.breed << "|" << s.name << "|" <<s.age << "|" << s.photograph << "\n";
	return os;
}


void testDog()
{
	Dog d{ "metis","aurel",12,"google.ro" };
	assert(d.getAge() == 12);
	assert(d.getBreed() == "metis");
	assert(d.getName() == "aurel");
	assert(d.getPhotograph() == "google.ro");


}