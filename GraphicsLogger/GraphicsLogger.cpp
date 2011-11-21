#include "GraphicsLogger.h"
#include <QGraphicsItem>
#include <QPainterPath>
#include <QPainter>
#include <QDir>
#include <QTimer>

GraphicsLogger::GraphicsLogger(QObject *parent) :
    QObject(parent)
  , m_path(QDir::tempPath())
{
    m_timer.blockSignals(true);
    m_timer.setSingleShot(true);
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(saveLog()));
}

void GraphicsLogger::setFilePath(QString p_path)
{
    m_path = p_path;
}

void GraphicsLogger::logMove(QPointF p_point,QString p_description)
{
    m_scene.addLine(QLineF(m_position,p_point),QPen(QBrush(Qt::green),0.5,Qt::DotLine));
    m_position = p_point;
    QRectF(m_position,p_point).center();
    logText(QRectF(m_position,p_point).center(),p_description);
}

void GraphicsLogger::logPoint(QPointF p_point,QString p_description)
{
    m_scene.addEllipse(QRectF(m_position + p_point - QPointF(5,5),QSizeF(10,10)),QPen(Qt::NoPen),QBrush(Qt::blue));
    logText(m_position + p_point,p_description);
}

void GraphicsLogger::logLine(QPointF p_point,QString p_description)
{
    m_scene.addLine(QLineF(m_position,p_point),QPen(QBrush(Qt::yellow),1));
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
    m_scene.addPath(QLineF(m_position,p_point),QPen(QBrush(Qt::yellow),1));
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
    logText(text->boundingRect().center(),p_description);
}

void GraphicsLogger::logItem(QGraphicsItem* p_item, QString p_description)
{
    QGraphicsPathItem* text = addPath(p_item->mapToScene(p_item->shape()));
    text->setBrush(QBrush(Qt::blue));
    text->setPos(m_position + p_point);
    logText(text->boundingRect().center(),p_description);
}

void GraphicsLogger::logPath(QPainterPath* p_item, QString p_description)
{
    QGraphicsPathItem* text = addPath(textPath);
    text->setBrush(QBrush(Qt::blue));
    text->setPos(m_position + p_point);
    logText(text->boundingRect().center(),p_description);
}

void GraphicsLogger::clearLog()
{
    m_scene.clear();
    m_counter = 1;
}

void GraphicsLogger::requestSave()
{
    m_timer.blockSignals(true);
    m_timer.stop();
    m_timer.start(500);
    m_timer.blockSignals(false);
}

void GraphicsLogger::saveLog()
{
//![configure SVG generator]
    QSvgGenerator generator;
    generator.setFileName(m_path);
    generator.setSize(QSize(200, 200));
    generator.setViewBox(QRect(0, 0, 200, 200));
    generator.setTitle(tr("SVG Generator Example Drawing"));
    generator.setDescription(tr("An SVG drawing created by the SVG Generator "
                                "Example provided with Qt."));
//![configure SVG generator]
//![begin painting]
    QPainter painter;
    painter.begin(&generator);
//![begin painting]
    paint(&painter,ui->graphicsView->scene());
//![end painting]
    painter.end();
//![end painting]
}
