#include "HTMLDoglist.h"
#include <fstream>
#include <Windows.h>
#include "RepositoryException.h"

using namespace std;

void HTMLDoglist::writeToFile()
{
	ofstream f(this->filename);
	if (!f.is_open())
		throw FileException("The file could not be opened");
	f << "<!DOCTYPE html>\n";
	f << "<html>" << endl;
	f << "<head>" << endl;
	f << "<title>Adoptions</title>" << endl;
	f << "</head> \n";
	f << "<body>\n";
	f << "<table border=\"1\">\n";
	f << " <tr>\n";
	f << "<td>Breed</td>\n";
	f << "<td>Name</td>\n";
	f << "<td>Age</td>\n";
	f << "<td>Photo</td>\n";
	f << "</tr>\n";
	for (auto d : this->dogs)
	{
		f << " <tr>\n";
		f << "<td>" << d.getBreed() << "</td>" << endl;
		f << "<td>" << d.getName() << "</td>" << endl;
		f << "<td>" << d.getAge() << "</td>" << endl;
		f << "<td><a href=\"" << d.getPhotograph() << "\">Link</a></td>" << endl;
		f << "</tr>\n";

	}


	f << "</table> \n";
	f << "</body> \n";
	f << "</HTML> \n";

	f.close();


}


void HTMLDoglist::displayDoglist()
{

	string aux = "\"" + this->filename + "\""; // if the path contains spaces, we must put it inside quotations

	ShellExecuteA(NULL, NULL, "chrome.EXE", aux.c_str(), NULL, SW_SHOWMAXIMIZED);
}