#include "GraphicsLogger.h"
#include <QGraphicsItem>
#include <QPainterPath>
#include <QPainter>

GraphicsLogger::GraphicsLogger(QObject *parent) :
    QGraphicsScene(parent)
{
}


void GraphicsLogger::logMove(QPointF p_point,QString p_description)
{
    addLine(QLineF(m_position,p_point),QPen(QBrush(Qt::green),0.5,Qt::DotLine));
    m_position = p_point;
    QRectF(m_position,p_point).center();
    logText(QRectF(m_position,p_point).center(),p_description);
}

void GraphicsLogger::logPoint(QPointF p_point,QString p_description)
{
    addEllipse(QRectF(m_position + p_point - QPointF(5,5),QSizeF(10,10)),QPen(Qt::NoPen),QBrush(Qt::blue));
    logText(m_position + p_point,p_description);
}

void GraphicsLogger::logLine(QPointF p_point,QString p_description)
{
    addLine(QLineF(m_position,p_point),QPen(QBrush(Qt::yellow),1));
    m_position = p_point;
    QRectF(m_position,p_point).center();
    logText(QRectF(m_position,p_point).center(),p_description);
}

void GraphicsLogger::logAngle(qreal from, qreal to,QString p_description)
{
    QPainterPath anglePath;
    QPainter painter;
    painter.begin(&anglePath);
    painter.drawPie(Text(p_point,QFont(),p_description);
    painter.end();
    addPath(QLineF(m_position,p_point),QPen(QBrush(Qt::yellow),1));
    m_position = p_point;
    QRectF(m_position,p_point).center();
    logText(QRectF(m_position,p_point).center(),p_description);
}

void GraphicsLogger::logText(QPointF p_point,QString p_description)
{
    QPainterPath textPath;
    textPath.addText(p_point,QFont(),p_description);
    QGraphicsPathItem* text = addPath(textPath);
    text->setBrush(QBrush(Qt::blue));
    text->setPos(m_position + p_point);
}
