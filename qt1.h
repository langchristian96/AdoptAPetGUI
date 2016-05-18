#ifndef QT1_H
#define QT1_H
#include <QtWidgets/QMainWindow>
#include "Controller.h"
#include <QListWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
//#include "ui_qt1.h"

class QT1 : public QWidget
{
	Q_OBJECT

public:
	QT1(Controller& c,QWidget *parent = 0);
	~QT1();
	Controller& getCtrl() { return ctrl; }

private:
	Controller& ctrl;
	std::vector<Dog> currentDogsInRepoList;

	QListWidget* repoList;
	QLineEdit* breedEdit;
	QLineEdit* nameEdit;
	QLineEdit* ageEdit;
	QLineEdit* linkEdit;
	QPushButton* addButton;
	QPushButton* deleteButton;
	QPushButton* filterButton;


	void initGUI();
	void populateRepoList();
	int getRepoListSelectedIndex();

	void connectSignalsAndSlots();

	private slots:
	// When an item in the list is clicked, the text boxes get filled with the item's information
	void listItemChanged();

	void addNewDog();
	void deleteDog();

	// filters the elements in the list, by the artist written in the artist edit box
	void filterRepoDogs();


};

#endif // QT1_H
