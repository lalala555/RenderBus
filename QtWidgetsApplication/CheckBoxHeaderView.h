#pragma once


#ifndef CHECKBOXHEADERVIEW_H
#define CHECKBOXHEADERVIEW_H

#include <QtGui>
#include <QPainter>
#include <QHeaderView>
#include <QStyleOptionButton>
#include <QStyle>
#include <QCheckBox>
#include <QObject>

class CheckBoxHeaderView : public QHeaderView
{
	Q_OBJECT

public:
	explicit CheckBoxHeaderView(int checkColumnIndex,QPoint topLeft,QSize size,Qt::Orientation orientation,QWidget * parent = nullptr);
	~CheckBoxHeaderView();

	//设置是否选中
	void setCheckState(bool state);

	void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;

	void mousePressEvent(QMouseEvent *event);

signals:
	void checkStatusChange(bool);


private:
	int     m_checkColIndex;    //列下标
	QPoint  m_topLeft;          //勾选框起始坐标
	QSize   m_checkSize;        //勾选框大小
	bool    m_isChecked;        //勾选框状态


};
#endif