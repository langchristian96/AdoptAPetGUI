#include "datapoint.h"

DataPoint::DataPoint() :
	m_x(""),
	m_y(0),
	m_color(QColor(qRgb(250, 0, 0))),
	m_width(50)
{
}

DataPoint::DataPoint(QString x, qreal y) :
	m_x(x),
	m_y(y),
	m_color(QColor(qRgb(250, 0, 0))),
	m_width(10)
{
}

void DataPoint::setX(QString x)
{
	m_x = x;
}

void DataPoint::setY(qreal y)
{
	m_y = y;
}

void DataPoint::setColor(const QColor &color)
{
	m_color = color;
}

void DataPoint::setWidth(int width)
{
	m_width = width;
}

QString DataPoint::x() const
{
	return m_x;
}

qreal DataPoint::y() const
{
	return m_y;
}

QColor DataPoint::color() const
{
	return m_color;
}

int DataPoint::width() const
{
	return m_width;
}