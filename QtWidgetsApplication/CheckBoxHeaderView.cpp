#include "CheckBoxHeaderView.h"

CheckBoxHeaderView::CheckBoxHeaderView(int checkColumnIndex, QPoint topLeft, QSize size, Qt::Orientation orientation, QWidget * parent) : QHeaderView(orientation, parent)
	
{
	m_checkColIndex = checkColumnIndex;
	m_topLeft = topLeft;
	m_checkSize = size;
	m_isChecked = false;
	/*connect(checkBox, &QCheckBox::clicked, [this]() {
		emit checkStateChange(checkBox->checkState());
	});*/
}

CheckBoxHeaderView::~CheckBoxHeaderView()
{
}

void CheckBoxHeaderView::setCheckState(bool state)
{
	m_isChecked = state;
}

void CheckBoxHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
	painter->save();
	QHeaderView::paintSection(painter, rect, logicalIndex);
	painter->restore();

	if (logicalIndex == 0)
	{
		QStyleOptionButton option;
		option.iconSize = QSize(10, 10);
		option.rect = rect;

		if (m_isChecked)
			option.state = QStyle::State_On;
		else
			option.state = QStyle::State_Off;
		this->style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &option, painter);
	}
}

void CheckBoxHeaderView::mousePressEvent(QMouseEvent *event)
{
	/*if (m_isChecked) {
		m_isChecked = false;
	}
	else {
		m_isChecked = true;
	}
	emit checkStatusChange(m_isChecked);
	this->viewport()->update();
	QHeaderView::mousePressEvent(event);*/
	if (visualIndexAt(event->pos().x()) == m_checkColIndex)
	{
		m_isChecked = !m_isChecked;
		this->updateSection(m_checkColIndex);
		emit checkStatusChange(m_isChecked);
	}

	QHeaderView::mousePressEvent(event);
}

void CheckBoxHeaderView::checkstate(int row,int col)
{
	qDebug() << row << col;
	//option.state = QStyle::State_Selected;
}
