#include "qt1.h"
#include <vector>
#include "Dog.h"
#include "Utils.h"
#include <QMessageBox>
#include "RepositoryException.h"


QT1::QT1(Controller& c, QWidget *parent) : ctrl{ c }, QWidget{ parent }
{
	this->initGUI();
	this->currentDogsInRepoList = this->ctrl.getRepo().getDogs();
	this->populateRepoList();
}

QT1::~QT1()
{

}

void QT1::initGUI()
{
	QHBoxLayout* layout = new QHBoxLayout{ this };

	QWidget* leftWidget = new QWidget{};
	QVBoxLayout* leftside = new QVBoxLayout{ leftWidget };
	this->repoList = new QListWidget{};
	this->repoList->setSelectionMode(QAbstractItemView::SingleSelection);
	QWidget* dogDataWidget = new QWidget{};

	QFormLayout* formlayout = new QFormLayout{ dogDataWidget };
	this->breedEdit = new QLineEdit{};
	this->nameEdit = new QLineEdit{};
	this->ageEdit = new QLineEdit{};
	this->linkEdit = new QLineEdit{};
	formlayout->addRow("Breed", breedEdit);
	formlayout->addRow("Name", nameEdit);
	formlayout->addRow("Age", ageEdit);
	formlayout->addRow("Link", linkEdit);

	QWidget* buttonsWidget = new QWidget{};
	QGridLayout* gridlayout = new QGridLayout{ buttonsWidget };
	this->addButton = new QPushButton("Add");
	this->deleteButton = new QPushButton("Remove");
	this->filterButton = new QPushButton("Filter");

	gridlayout->addWidget(addButton, 0, 0);
	gridlayout->addWidget(deleteButton, 0, 1);
	gridlayout->addWidget(filterButton, 0, 3);

	//add everything to left layout

	leftside->addWidget(new QLabel{ "All dogs" });
	leftside->addWidget(repoList);
	leftside->addWidget(dogDataWidget);
	leftside->addWidget(buttonsWidget);
	





	//add all to main widget
	layout->addWidget(leftWidget);

	this->connectSignalsAndSlots();


}

void QT1::connectSignalsAndSlots()
{
	QObject::connect(this->repoList, SIGNAL(itemSelectionChanged()), this, SLOT(listItemChanged()));


	QObject::connect(this->addButton, SIGNAL(clicked()), this, SLOT(addNewDog()));
	QObject::connect(this->deleteButton, SIGNAL(clicked()), this, SLOT(deleteDog()));
	QObject::connect(this->filterButton, SIGNAL(clicked()), this, SLOT(filterRepoDogs()));



}

void QT1::populateRepoList()
{
	if (this->repoList->count() > 0)this->repoList->clear();

	for (auto s : this->currentDogsInRepoList)
	{
		QString iteminlist = QString::fromStdString(s.getBreed() + " - " + s.getName());
		this->repoList->addItem(iteminlist);

	}
	if (this->currentDogsInRepoList.size() > 0)this->repoList->setCurrentRow(0);



}


int QT1::getRepoListSelectedIndex()
{
	if (this->repoList->count() == 0)return -1;
	QModelIndexList index = this->repoList->selectionModel()->selectedIndexes();
	if (index.size() == 0)
	{
		this->nameEdit->clear();
		this->breedEdit->clear();
		this->ageEdit->clear();
		this->linkEdit->clear();
		return -1;

	}
	int idx = index.at(0).row();
	return idx;


}

void QT1::listItemChanged()
{
	int idx = this->getRepoListSelectedIndex();
	if (idx == -1)	return;
	std::vector<Dog> dogs = this->currentDogsInRepoList;
	if (idx > dogs.size())return;
	Dog s = dogs[idx];
	this->nameEdit->setText(QString::fromStdString(s.getName()));
	this->breedEdit->setText(QString::fromStdString(s.getBreed()));
	QString w;
	w.setNum(s.getAge());
	this->ageEdit->setText(w);
	this->linkEdit->setText(QString::fromStdString(s.getPhotograph()));
}

void QT1::addNewDog()
{
	std::string name = this->nameEdit->text().toStdString();
	std::string breed = this->breedEdit->text().toStdString();
	std::string source = this->linkEdit->text().toStdString();
	int age = std::stoi(this->ageEdit->text().toStdString());

	try
	{
		this->ctrl.addDogToRepository(breed, name, age, source);
		this->currentDogsInRepoList = this->ctrl.getRepo().getDogs();
		this->populateRepoList();
	}
	catch (DogException& e)
	{
		QMessageBox messagebox;
		messagebox.critical(0, "Error", QString::fromStdString(e.getErrorsAsString()));
	}
	catch(DuplicateDogException& e)
	{
		QMessageBox messagebox;
		messagebox.critical(0, "Error", e.what());	
	}
}

void QT1::deleteDog()
{
	std::string name = this->nameEdit->text().toStdString();
	try
	{
		this->ctrl.removeDogFromRepository(name);
		this->currentDogsInRepoList = this->ctrl.getRepo().getDogs();
		this->populateRepoList();


	}
	catch (RepositoryException& e)
	{
		QMessageBox messagebox;
		messagebox.critical(0, "Error", e.what());

	}

}

void QT1::filterRepoDogs()
{
	std::string breed = this->breedEdit->text().toStdString();

	int age = std::stoi(this->ageEdit->text().toStdString());
	
	if (breed == "")
	{
		this->currentDogsInRepoList = this->ctrl.getRepo().getDogs();
		this->populateRepoList();
		return;
	}
	this->ctrl.addDogsByBreedAndAge(breed,age);
	this->currentDogsInRepoList = this->ctrl.getBreedList().getDogs();
	this->populateRepoList();


}
