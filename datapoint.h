#ifndef DATAPOINT_H
#define DATAPOINT_H

#include <Qtcore/QtGlobal>
#include <QtGui/QColor>
#include <qtcore/QList>
#include <qtcore/QMetaType>

class DataPoint
{
public:
	DataPoint();
	DataPoint(QString x, qreal Y);

	void setX(QString x);
	void setY(qreal y);

	void setColor(const QColor &color);
	void setWidth(int width);

	QString x() const;
	qreal y() const;

	QColor color() const;
	int width() const;

private:
	QString m_x;
	qreal m_y;
	QColor m_color;
	int m_width;
};

typedef QList<DataPoint*> DataPointList;

#endif // DATAPOINT_H