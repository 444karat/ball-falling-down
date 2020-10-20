#ifndef RW_H
#define RW_H

#include "pts.h"

#include <QtGui/QWindow>
#include <QtGui/QPainter>
#include <QtGui/QResizeEvent>
#include <QtGui/QExposeEvent>
#include <QtGui/QBackingStore>
#include <QObject>
#include <QRect>
#include <memory>
#include <QtCore/QElapsedTimer>

class RW : public QWindow
{
    Q_OBJECT
public:
    explicit RW(QWindow *parent = nullptr);
    bool     isAnimating() const;
    void     setAnimating(bool isAnimating);
    // QObject interface
    bool     event(QEvent *event)override ;
private:
    void     renderLater();
    void     renderNow();
//  void     render(QPainter *painter);
    void     updateScene(); // обновляет состояние сцены
    void     renderScene(); // перерисовывает содержимое сцены

    QBackingStore       *m_backingStore = nullptr;
    std::unique_ptr<PTS> m_scene; // объект сцены
    QElapsedTimer        m_updateTimer; // таймер обновления сцены
    bool                 m_isAnimating = false;
protected:
    // QWindow interface
    void    exposeEvent(QExposeEvent *)override ;
    void    resizeEvent(QResizeEvent *)override ;

signals:
};

#endif // RW_H
