#include "qt2.h"
#include <vector>
#include "Dog.h"
#include "Utils.h"
#include <QMessageBox>
#include "RepositoryException.h"


QT2::QT2(Controller& c, QWidget *parent) : ctrl{ c }, QWidget{ parent }
{
	this->initGUI();
	this->currentDogsInRepoList = this->ctrl.getRepo().getDogs();
	this->populateRepoList();
}

QT2::~QT2()
{

}

void QT2::initGUI()
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
	this->filterButton = new QPushButton("Filter");
	this->openButton = new QPushButton("Open");
	this->openButton2 = new QPushButton("Open");
	gridlayout->addWidget(openButton, 0, 2);
	gridlayout->addWidget(filterButton, 0, 3);

	//add everything to left layout

	leftside->addWidget(new QLabel{ "All dogs" });
	leftside->addWidget(repoList);
	leftside->addWidget(dogDataWidget);
	leftside->addWidget(buttonsWidget);


	//middle widget

	QWidget* middleWidget = new QWidget{};
	QVBoxLayout* vlayoutmiddle = new QVBoxLayout{ middleWidget };
	this->moveOneDogButton = new QPushButton(">Adopt this dog");
	QWidget* upperpart = new QWidget{};
	QWidget* lowerpart = new QWidget{};
	QVBoxLayout* vlayoutupperpart = new QVBoxLayout{ upperpart };
	vlayoutupperpart->addWidget(this->moveOneDogButton);
	vlayoutmiddle->addWidget(upperpart);
	vlayoutmiddle->addWidget(lowerpart);


	//right widget

	QWidget* rightwidget = new QWidget{};
	QVBoxLayout* rightside = new QVBoxLayout{ rightwidget };

	dogList = new QListWidget{};


	QWidget* doglistButtonsWidget = new QWidget{};
	QHBoxLayout* doglistButtonsLayout = new QHBoxLayout{ doglistButtonsWidget };
	doglistButtonsLayout->addWidget(openButton2);
	seeAdoption = new QPushButton{ "See adoption List" };
	doglistButtonsLayout->addWidget(seeAdoption);


	rightside->addWidget(new QLabel{ "Adoption list" });
	rightside->addWidget(dogList);
	rightside->addWidget(doglistButtonsWidget);


	//add all to main widget
	layout->addWidget(leftWidget);
	layout->addWidget(middleWidget);
	layout->addWidget(rightwidget);

	this->connectSignalsAndSlots();


}

void QT2::connectSignalsAndSlots()
{
	QObject::connect(this->repoList, SIGNAL(itemSelectionChanged()), this, SLOT(listItemChanged()));


	QObject::connect(this->openButton, SIGNAL(clicked()), this, SLOT(openDog()));

	QObject::connect(this->openButton2, SIGNAL(clicked()), this, SLOT(openDog2()));
	QObject::connect(this->filterButton, SIGNAL(clicked()), this, SLOT(filterRepoDogs()));

	QObject::connect(this->moveOneDogButton, SIGNAL(clicked()), this, SLOT(moveDogToDoglist()));

	QObject::connect(this->seeAdoption, SIGNAL(clicked()), this, SLOT(saveAdoptionAndOpen()));



}

void QT2::populateRepoList()
{
	if (this->repoList->count() > 0)this->repoList->clear();

	for (auto s : this->currentDogsInRepoList)
	{
		QString iteminlist = QString::fromStdString(s.getBreed() + " - " + s.getName());
		this->repoList->addItem(iteminlist);

	}
	if (this->currentDogsInRepoList.size() > 0)this->repoList->setCurrentRow(0);



}

void QT2::populateDoglist()
{

	if (this->dogList->count() > 0)
		this->dogList->clear();

	for (auto s : this->ctrl.getAdoptionList()->getDogs())
	{
		QString itemInList = QString::fromStdString(s.getBreed() + " - " + s.getName());
		this->dogList->addItem(itemInList);
	}

}

int QT2::getRepoListSelectedIndex()
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


int QT2::getDogListSelectedIndex()
{
	if (this->dogList->count() == 0)return -1;
	QModelIndexList index = this->dogList->selectionModel()->selectedIndexes();
	
	int idx = index.at(0).row();
	return idx;


}

void QT2::listItemChanged()
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


void QT2::openDog()
{
	std::string name = this->nameEdit->text().toStdString();
	try
	{
		std::vector<Dog> all = this->ctrl.getRepo().getDogs();
		for (std::vector<Dog>::iterator it = all.begin(); it != all.end(); it++)
		{
			if (it->getName() == name)
			{
				it->seePhotograph();
				return;
			}
			
		}
		throw RepositoryException("The dog does not exist");

	}
	catch (RepositoryException& e)
	{
		QMessageBox messagebox;
		messagebox.critical(0, "Error", e.what());

	}

}


void QT2::openDog2()
{
	int idx = this->getDogListSelectedIndex();
	
	if (idx <= -1)	return;
	if (idx >= this->ctrl.getAdoptionList()->getNumberOfDogs())return;
	std::vector<Dog> adoptions = this->ctrl.getAdoptionList()->getDogs();
	adoptions[idx].seePhotograph();
}

void QT2::filterRepoDogs()
{
	std::string breed = this->breedEdit->text().toStdString();

	int age = std::stoi(this->ageEdit->text().toStdString());

	if (breed == "")
	{
		this->currentDogsInRepoList = this->ctrl.getRepo().getDogs();
		this->populateRepoList();
		return;
	}
	this->ctrl.addDogsByBreedAndAge(breed, age);
	this->currentDogsInRepoList = this->ctrl.getBreedList().getDogs();
	this->populateRepoList();


}

void QT2::saveAdoptionAndOpen()
{
	this->ctrl.saveDoglist("adoptions");
	this->ctrl.openDoglist();
	

}

void QT2::moveDogToDoglist()
{
	int idx = this->getRepoListSelectedIndex();
	if (idx == -1 || idx > this->currentDogsInRepoList.size())
		return;
	const Dog& s = this->currentDogsInRepoList[idx];
	this->ctrl.addDogToAdoption(s);
	this->populateDoglist();
	this->dogList->setCurrentRow(0);


}

