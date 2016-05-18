#include "barchart.h"

#include <QtGui/QPainter>
#include <QtGui/QFontMetricsF>
#include <QtCore/QPointF>
#include <QtGui/QPen>
#include <QtGui/QBrush>

BarChart::BarChart(QWidget *parent) :
	QWidget(parent)
{
	spaceBetweenBars = 90;
	chartOuterMargin = 100;
}

void BarChart::setDataPointList(const DataPointList &pointList)
{
	m_dataPointList = pointList;
	update();
}

void BarChart::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);

	QPainter painter(this);

	if (m_dataPointList.isEmpty())
		drawEmptyBarChart(&painter);
	else {
		drawXAxis(&painter);
		drawYAxis(&painter);
		drawDataPoints(&painter);
	}
}

qreal BarChart::maximumHeight()
{
	qreal height = 0;

	foreach(DataPoint *point, m_dataPointList) {
		if (point->y() > height)
			height = point->y();
	}

	return height;
}

qreal BarChart::maximumWidth()
{
	qreal width = 0;

	foreach(DataPoint *point, m_dataPointList) {
		width += point->width() + spaceBetweenBars;
	}

	return width;
}

qreal BarChart::yAxisWidth()
{
	QString maximumValue = QString::number(maximumHeight());
	QFontMetrics fm(font());
	qreal textWidth = fm.width(maximumValue);

	return textWidth + 5;
}

qreal BarChart::xAxisHeight()
{
	QFontMetrics fm(font());
	qreal textHeight = fm.height();

	return textHeight + 5;
}

qreal BarChart::dataPointHeight(qreal y)
{
	QFontMetrics fm(font());
	qreal textHeight = fm.height();

	return y * ((height() - (2 * (chartOuterMargin + (textHeight / 2))) - xAxisHeight()) / maximumHeight());
}

void BarChart::drawEmptyBarChart(QPainter *painter)
{
	QString text("No datapoints available!");

	qreal centreX = width() / 2;
	qreal centreY = height() / 2;

	QFontMetricsF fontMetrics(font());
	qreal textWidth = fontMetrics.width(text);
	qreal textHeight = fontMetrics.height();

	qreal textX = centreX - (textWidth / 2);
	qreal textY = centreY - (textHeight / 2);

	painter->drawText(QPointF(textX, textY), text);
}

void BarChart::drawYAxis(QPainter *painter)
{
	QPen yAxisPen(QColor(qRgb(0, 0, 0)));

	QString maximumValue = QString::number(maximumHeight());
	QFontMetrics fm(font());
	qreal textWidth = fm.width(maximumValue);
	qreal textHeight = fm.height();

	qreal yAxisX = chartOuterMargin + textWidth + 5;
	qreal yAxisY = chartOuterMargin + (textHeight / 2);
	qreal yAxisHeight = height() - yAxisY - xAxisHeight();

	painter->save();

	painter->setPen(yAxisPen);
	painter->drawLine(QPointF(yAxisX, yAxisY), QPointF(yAxisX, yAxisHeight));

	painter->drawLine(QPointF(yAxisX - 3, yAxisY), QPointF(yAxisX, yAxisY));
	painter->drawLine(QPointF(yAxisX - 3, yAxisHeight), QPointF(yAxisX, yAxisHeight));

	painter->drawText(QPointF(chartOuterMargin, chartOuterMargin + textHeight), maximumValue);
	painter->drawText(QPointF(chartOuterMargin, height() - chartOuterMargin - xAxisHeight()), "0");

	painter->restore();
}

void BarChart::drawXAxis(QPainter *painter)
{
	QPen xAxisPen(QColor(qRgb(0, 0, 0)));

	QFontMetrics fm(font());
	qreal textHeight = fm.height();

	qreal xAxisX = chartOuterMargin + yAxisWidth();
	qreal xAxisY = height() - xAxisHeight() - chartOuterMargin - (textHeight / 2);
	qreal xAxisWidth = xAxisX + maximumWidth() + spaceBetweenBars;
	painter->save();

	painter->setPen(xAxisPen);
	painter->drawLine(QPointF(xAxisX, xAxisY), QPointF(xAxisWidth, xAxisY));

	qreal xAxisMark = xAxisX + spaceBetweenBars; // Keep some space between the first bar and the Y axis

	foreach(DataPoint *point, m_dataPointList) {
		xAxisMark += point->width() / 2;

		painter->drawLine(QPointF(xAxisMark, xAxisY), QPointF(xAxisMark, xAxisY + 3));

		QFontMetrics fm(font());
		qreal markTextWidth = fm.width(point->x());
		qreal markTextHeight = fm.height();

		painter->drawText(QPointF(xAxisMark - (markTextWidth / 2), xAxisY + markTextHeight + 5), point->x());

		xAxisMark += (point->width() / 2) + spaceBetweenBars;
	}

	painter->restore();
}

void BarChart::drawDataPoints(QPainter *painter)
{
	qreal dataPointCentre = chartOuterMargin + yAxisWidth() + spaceBetweenBars;

	QFontMetrics fm(font());
	qreal textHeight = fm.height();

	foreach(DataPoint *point, m_dataPointList) {
		QBrush dataPointBrush(point->color());
		QPen dataPointPen(QColor(qRgb(0, 0, 0)));

		dataPointCentre += point->width() / 2;

		painter->save();

		painter->setBrush(dataPointBrush);
		painter->setPen(dataPointPen);

		qreal dpHeight = dataPointHeight(point->y());

		painter->drawRect(QRectF(dataPointCentre - (point->width() / 2), height() - xAxisHeight() - chartOuterMargin - (textHeight / 2), point->width(), -dpHeight));

		painter->restore();

		dataPointCentre += (point->width() / 2) + spaceBetweenBars;
	}
}