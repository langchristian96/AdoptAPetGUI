#ifndef QT2_H
#define QT2_H
#include <QtWidgets/QMainWindow>
#include "Controller.h"
#include <QListWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class QT2 : public QWidget
{
	Q_OBJECT

public:
	QT2(Controller& c, QWidget *parent = 0);
	~QT2();

private:
	Controller& ctrl;
	std::vector<Dog> currentDogsInRepoList;

	QListWidget* repoList;
	QLineEdit* breedEdit;
	QLineEdit* nameEdit;
	QLineEdit* ageEdit;
	QLineEdit* linkEdit;
	QPushButton* openButton;
	QPushButton* openButton2;
	QPushButton* seeAdoption;
	QPushButton* filterButton;
	QPushButton* moveOneDogButton;

	QListWidget* dogList;

	void initGUI();
	void populateRepoList();
	void populateDoglist();
	int getRepoListSelectedIndex();
	int getDogListSelectedIndex();

	void connectSignalsAndSlots();

	private slots:
	// When an item in the list is clicked, the text boxes get filled with the item's information
	void listItemChanged();

	void openDog();
	void openDog2();
	void saveAdoptionAndOpen();

	void filterRepoDogs();

	void moveDogToDoglist();
};

#endif // QT2_H
