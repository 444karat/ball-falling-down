#include "pts.h"

namespace  {
    constexpr double BALL_SPEED = 100;
    constexpr double BALL_SIZE  = 50;
}

PTS::PTS(const RectF &bounds)
    : m_bounds(bounds)
  , m_ballSpeed(BALL_SPEED, BALL_SPEED)
  , m_ballSize(BALL_SIZE, BALL_SIZE)
{

}

void PTS::update(float deltaSeconds)
{
    m_ballPosY += BALL_SPEED * deltaSeconds;

    if (m_ballPosition.x < m_bounds.leftEdge())
    {
        m_ballPosition.x = m_bounds.leftEdge();
        m_ballSpeed.x = -m_ballSpeed.x;
    }
    else if (m_ballPosition.x > m_bounds.rightEdge() - m_ballSize.x)
    {
        m_ballPosition.x = m_bounds.rightEdge() - m_ballSize.x;
        m_ballSpeed.x = -m_ballSpeed.x;
    }
}

void PTS::redraw(QPainter &painter)
{
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setBrush(QBrush(QColor(Qt::blue)));
    //painter->drawEllipse(QRect(0,0,width() - 10,height()- 10));
    painter.drawEllipse(QRect(m_ballPosX,m_ballPosY,BALL_SIZE,BALL_SIZE));
}
