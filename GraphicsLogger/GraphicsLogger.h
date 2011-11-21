#ifndef GRAPHICSLOGGER_H
#define GRAPHICSLOGGER_H

#include <QGraphicsScene>

class GraphicsLogger : public QObject
{
    Q_OBJECT
public:
    explicit GraphicsLogger(QObject *parent = 0);

    void setFilePath(QString p_path);

    void logMove(QPointF p_point,QString p_description);
    void logPoint(QPointF p_point,QString p_description);
    void logLine(QPointF p_point,QString p_description);
    void logAngle(qreal from, qreal to,QString p_description);
    void logItem(QGraphicsItem* p_item, QString p_description);
    void logPath(QPainterPath* p_item, QString p_description);
    void clearLog();

protected:
    void requestSave();
    void logText(QPointF p_point,QString p_description);

signals:

private slots:
    void saveLog();

private:
    QPointF m_position;
    QGraphicsScene m_scene;
    unsigned int m_counter;
    QString m_path;
    QTimer m_timer;

};

#endif // GRAPHICSLOGGER_H
