#ifndef BARCHART_H
#define BARCHART_H

#include <QTWidgets/QWidget>
#include <QtGui/QPaintEvent>
#include <QTcore/QtGlobal>

#include "datapoint.h"

class BarChart : public QWidget
{
	Q_OBJECT
public:
	explicit BarChart(QWidget *parent = 0);

	void setDataPointList(const DataPointList &pointList);

protected:
	void paintEvent(QPaintEvent *event);

signals:

	public slots :

private:
	DataPointList m_dataPointList;

	qreal maximumHeight();
	qreal maximumWidth();

	qreal yAxisWidth();
	qreal xAxisHeight();

	qreal spaceBetweenBars;
	qreal chartOuterMargin;

	qreal dataPointHeight(qreal y);

	void drawEmptyBarChart(QPainter *painter);
	void drawYAxis(QPainter *painter);
	void drawXAxis(QPainter *painter);
	void drawDataPoints(QPainter *painter);
};

#endif // BARCHART_H