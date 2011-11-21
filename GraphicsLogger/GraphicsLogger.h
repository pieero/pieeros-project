#ifndef GRAPHICSLOGGER_H
#define GRAPHICSLOGGER_H

#include <QGraphicsScene>

class GraphicsLogger : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphicsLogger(QObject *parent = 0);

    void setFilePath(QString p_path);
    void requestSave();

    void logMove(QPointF p_point,QString p_description);
    void logPoint(QPointF p_point,QString p_description);
    void logLine(QPointF p_point,QString p_description);
    void logAngle(qreal from, qreal to,QString p_description);
    void logText(QPointF p_point,QString p_description);

signals:

public slots:

private:
    QPointF m_position;

};

#endif // GRAPHICSLOGGER_H
