#include "rw.h"

constexpr unsigned WINDOW_WIDTH = 600;
constexpr unsigned WINDOW_HEIGHT = 800;

RW::RW(QWindow *parent) : QWindow(parent)
                        , m_backingStore(new QBackingStore(this))
                        ,  m_scene(std::make_unique<PTS>(RectF{0, 0, float(WINDOW_WIDTH ), float(WINDOW_HEIGHT)}))
{
    setMinimumSize(QSize(600,800));
    m_updateTimer.start();
}

bool RW::isAnimating() const
{
    return m_isAnimating;
}

void RW::setAnimating(bool isAnimating)
{
    m_isAnimating = isAnimating;
    if (isAnimating)
        renderLater();
}

bool RW::event(QEvent *event)
{
    if(event->type() == QEvent::UpdateRequest){
        renderNow();
        return true;
    }
    return QWindow::event(event);
}

void RW::renderLater()
{
    requestUpdate();
}

void RW::renderNow()
{
    if ( isExposed() == false)
        return;

    updateScene();
    renderScene();

    if(m_isAnimating)
        renderLater();
}

void RW::updateScene()
{
    const double elapsedSeconds  = double (m_updateTimer.elapsed())/1000.f;

    if (elapsedSeconds > 0)
    {
        m_updateTimer.restart();
        m_scene->update(elapsedSeconds);
    }

}

void RW::renderScene()
{
    QRect rect(0,0, width(),height());
    m_backingStore->beginPaint(rect);

    QPaintDevice * device = m_backingStore->paintDevice();
    QPainter painter(device);
    painter.fillRect(0,0, width(),height(), Qt::black);
    m_scene->redraw(painter);
    painter.end();

    m_backingStore->endPaint();
    m_backingStore->flush(rect);
}

/*void RW::render(QPainter *painter)
{
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setBrush(QBrush(QColor(Qt::blue)));
    //painter->drawEllipse(QRect(0,0,width() - 10,height()- 10));
    painter->drawEllipse(QRect(width()/2,height()/2,50,50));

}*/

void RW::exposeEvent(QExposeEvent *)
{
    if(isExposed())
        renderNow();
}

void RW::resizeEvent(QResizeEvent *resizeEvent)
{
    m_backingStore->resize(resizeEvent->size());
    if(isExposed())
        renderNow();
}
