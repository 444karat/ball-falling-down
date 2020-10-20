#ifndef PTS_H
#define PTS_H

#include "rf.h"

#include <QtGui/QPainter>

class PTS
{
public:
    explicit PTS(const RectF& bounds);

    void update(float deltaSeconds);
    void redraw(QPainter& painter);
private:
    double m_ballPosX = 300;
    double m_ballPosY = 399;

    Vector2f    m_ballPosition;
    Vector2f    m_ballSpeed;
const Vector2f  m_ballSize;
const  RectF    m_bounds;
};

#endif // PTS_H
