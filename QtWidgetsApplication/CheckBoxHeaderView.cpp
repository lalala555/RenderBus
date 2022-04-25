#include "CheckBoxHeaderView.h"

CheckBoxHeaderView::CheckBoxHeaderView(int checkColumnIndex, QPoint topLeft, QSize size, Qt::Orientation orientation, QWidget * parent) : QHeaderView(orientation, parent)
	
{
	m_checkColIndex = checkColumnIndex;
	m_topLeft = topLeft;
	m_checkSize = size;
	m_isChecked = false;

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
	/*painter->save();
	QHeaderView::paintSection(painter, rect, logicalIndex);
	painter->restore();
	if (logicalIndex == m_checkColIndex)
	{
		QStyleOptionButton option;
		int width = 10;
		for (int i = 0; i < logicalIndex; ++i)
		{
			width += sectionSize(i);
		}
		option.rect = QRect(m_topLeft.x(), m_topLeft.y(), m_checkSize.width(), m_checkSize.height());
		if (m_isChecked)
		{
			option.state = QStyle::State_On;
		}
		else
		{
			option.state = QStyle::State_Off;
		}
		QCheckBox *check = new QCheckBox;
		QString sheet = QString("QCheckBox::indicator {width: %1px;  height: %2px;}").arg(m_checkSize.width()).arg(m_checkSize.height());
		check->setStyleSheet(sheet);
		this->style()->drawControl(QStyle::CE_CheckBox, &option, painter, check);
	}*/
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
	if (visualIndexAt(event->pos().x()) == m_checkColIndex)
	{
		m_isChecked = !m_isChecked;
		this->updateSection(m_checkColIndex);
		emit checkStatusChange(m_isChecked);
	}
	QHeaderView::mousePressEvent(event);
}
