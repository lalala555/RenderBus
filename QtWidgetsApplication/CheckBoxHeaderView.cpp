#include "CheckBoxHeaderView.h"

CheckBoxHeaderView::CheckBoxHeaderView(int checkColumnIndex, QPoint topLeft, QSize size, Qt::Orientation orientation, QWidget * parent) : QHeaderView(orientation, parent)
	
{
	m_checkColIndex = checkColumnIndex;
	m_topLeft = topLeft;
	m_checkSize = size;
	m_isChecked = false;
	m_bPressed = false;
	m_bTristate = false;
	m_bNoChange = false;
	m_bMoving = false;
	setHighlightSections(false);
	setMouseTracking(true);
	// 响应鼠标
	setSectionsClickable(true);
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
	/*painter->save();
	QHeaderView::paintSection(painter, rect, logicalIndex);
	painter->restore();
	if (logicalIndex == 0)
	{
		QStyleOptionButton option;
		option.initFrom(this);
		if (m_isChecked)
			option.state |= QStyle::State_Sunken;
		if (m_bTristate && m_bNoChange)
			option.state |= QStyle::State_NoChange;
		else
			option.state |= m_isChecked ?
			QStyle::State_On : QStyle::State_Off;
		if (testAttribute(Qt::WA_Hover) && underMouse()) {
			if (m_bMoving)
				option.state |= QStyle::State_MouseOver;
			else
				option.state &= ~QStyle::State_MouseOver;
		}
		QCheckBox checkBox;
		option.iconSize = QSize(20, 20);
		option.rect = rect;
		style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &option, painter,&checkBox);
		qDebug() << "update";*/
		
		//style()->drawItemPixmap(painter, rect, Qt::AlignCenter, QPixmap(":/images/checkBoxChecked"));
		//style()->drawControl(QStyle::CE_CheckBox, &option, painter, this);
	//}
}

void CheckBoxHeaderView::mousePressEvent(QMouseEvent *event)
{
	if (visualIndexAt(event->pos().x()) == m_checkColIndex)
	{
		m_isChecked = !m_isChecked;
		this->updateSection(m_checkColIndex);
		//update();
		emit checkStatusChange(m_isChecked);
	}

	QHeaderView::mousePressEvent(event);
}

// 鼠标滑过、离开，更新复选框状态
bool CheckBoxHeaderView::event(QEvent *event)
{
	if (event->type() == QEvent::Enter || event->type() == QEvent::Leave)
	{
		QMouseEvent *pEvent = static_cast<QMouseEvent *>(event);
		int nColumn = logicalIndexAt(pEvent->x());
		if (nColumn == 0)
		{
			m_bMoving = (event->type() == QEvent::Enter);
			update();
			return true;
		}
	}
   return QHeaderView::event(event);
}

void CheckBoxHeaderView::checkstate(int value)
{
	if (value == Qt::Unchecked)
		m_isChecked = false;
	if (value == Qt::Checked)
		m_isChecked = true;
	//if (value == Qt::PartiallyChecked) {
	//	m_bTristate = true;
	//	m_bNoChange = true;
	//}
	//else {
	//	m_bNoChange = false;
	//}
	//m_isChecked = (value != Qt::Unchecked);
	////adjustSize();
	//qDebug() << "revice";
	////paintSection();
	//this->updateSection(0);
	////emit refresh();
	//
	//update();
	////repaint();
	////showNormal();
	//this->updateSection(m_checkColIndex);

}
