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

	//�����Ƿ�ѡ��
	void setCheckState(bool state);

	void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;

	void mousePressEvent(QMouseEvent *event);

	void fresh();
	bool event(QEvent *event);

signals:
	void checkStatusChange(bool value);

	void refresh();

public slots:
    void  checkstate(int value);



private:
	int     m_checkColIndex;    //���±�
	QPoint  m_topLeft;          //��ѡ����ʼ����
	QSize   m_checkSize;        //��ѡ���С
	bool    m_isChecked;        //��ѡ��״̬
	bool    m_bPressed;
	bool	m_bTristate;
	bool	m_bNoChange;
	bool    m_bMoving;


};
#endif