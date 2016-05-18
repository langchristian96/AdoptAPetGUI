#include "CSVDoglist.h"
#include <fstream>
#include <Windows.h>
#include "RepositoryException.h"

using namespace std;

void CSVDoglist::writeToFile()
{
	ofstream f(this->filename);
	if (!f.is_open())
		throw FileException("The file could not be opened");
	for (auto d : this->dogs)
		f << d.getBreed() << "," << d.getName() << "," << d.getAge() << "," << d.getPhotograph() << endl;
	f.close();


}


void CSVDoglist::displayDoglist() 
{

	string aux = "\"" + this->filename + "\""; // if the path contains spaces, we must put it inside quotations

	ShellExecuteA(NULL, NULL, "C:\\Program Files (x86)\\Microsoft Office\\Office14\\EXCEL.EXE", aux.c_str(), NULL, SW_SHOWMAXIMIZED);
}