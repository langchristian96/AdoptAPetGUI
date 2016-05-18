#include "qt1.h"
#include "qt2.h"
#include <qapplication.h>
#include <QPushButton>
#include <qlistwidget>
#include <qboxlayout.h>
#include <qlineedit.h>
#include <qformlayout.h>
#include <qlabel.h>
#include <qmessagebox.h>
#include "barchart.h"
#include "datapoint.h"
#include <QtWidgets/QApplication>
#include "CSVDoglist.h"
#include "HTMLDoglist.h"
#include "DogList.h"
#include <map>

QWidget* global1;
QWidget* global2;
QT1* global3;

DataPointList dataPoints;
BarChart* barChart;
std::map<std::string, int> dgs;
	
void adminm()
{
	global1->show();
}

void userm()
{
	global2->show();
}

void chartm()
{
	std::vector<Dog> all = global3->getCtrl().getRepo().getDogs();
	for (auto it = all.begin(); it != all.end(); ++it)
	{
		if (dgs.find(it->getBreed()) == dgs.end())
		{
			dgs.insert(std::make_pair(it->getBreed(), 1));
		}
		else dgs[it->getBreed()] += 1;
	}

	for (auto it = dgs.begin(); it != dgs.end(); ++it)
	{

		dataPoints.append(new DataPoint(QString::fromStdString(it->first), it->second));
	}

	barChart = new BarChart;

	//...

	barChart->setDataPointList(dataPoints);
	barChart->show();
	/*
	std::vector<Dog> all = global3->getCtrl().getRepo().getDogs();
	for (auto it = all.begin(); it != all.end(); ++it)
	{
		if (dgs.find(it->getBreed()) == dgs.end())
		{
			dgs.insert(std::make_pair(it->getBreed(), 1));
		}
		else dgs[it->getBreed()]+=1;
	}
	
		for (auto it = dgs.begin(); it != dgs.end(); ++it)
	{

		dataPoints.append(new DataPoint(QString::fromStdString(it->first), it->second));
	}
	
	

	dataPoints.append(new DataPoint(QString::fromStdString("Sharpei"), 1));
	dataPoints.append(new DataPoint("Bulldog", 2));

	DataPoint *colorPoint = new DataPoint("test", 3);
	colorPoint->setColor(QColor(qRgb(250, 0, 0)));
	dataPoints.append(colorPoint);

	dataPoints.append(new DataPoint("test", 4));

	DataPoint *widthPoint = new DataPoint("test", 5);

	dataPoints.append(widthPoint);

	dataPoints.append(new DataPoint("test", 6));

	barChart->setDataPointList(dataPoints);
	barChart->show();
	*/
}


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Repository repo{ "Dogs.txt" };
	FileDoglist* doglist;

	QMessageBox reply;
	reply.setText(QString::fromStdString("HTML or CSV? "));
	QAbstractButton* myHtmlButton = reply.addButton(QString::fromStdString("HTML"), QMessageBox::YesRole);
	QAbstractButton* myCSVButton = reply.addButton(QString::fromStdString("CSV"), QMessageBox::NoRole);
	reply.setIcon(QMessageBox::Question);
	reply.exec();
	if (reply.clickedButton() == myCSVButton) 
	{
		doglist = new CSVDoglist{};
	}
	else 
	{
		doglist = new HTMLDoglist{};
	}
	Controller ctrl{ repo,doglist,DogValidator{} };
	QT1 w{ ctrl };
	QT2 um{ ctrl };
	global3 = &w;
	global2 = &um;
	global1 = &w;
	QWidget* ww = new QWidget{};
	QHBoxLayout* hlayout = new QHBoxLayout{ ww };
	QPushButton* button1 = new QPushButton{};
	QPushButton* button2 = new QPushButton{};
	QPushButton* button3 = new QPushButton{};
	button1->setText(QString::fromStdString("Admin mode"));
	button2->setText(QString::fromStdString("User mode"));
	button3->setText(QString::fromStdString("Dogs chart"));
	hlayout->addWidget(button1);
	hlayout->addWidget(button2);
	hlayout->addWidget(button3);
	QObject::connect(button1, &QPushButton::clicked, adminm);
	QObject::connect(button2, &QPushButton::clicked, userm);
	QObject::connect(button3, &QPushButton::clicked, chartm);
	
	ww->show();

	return a.exec();
}
