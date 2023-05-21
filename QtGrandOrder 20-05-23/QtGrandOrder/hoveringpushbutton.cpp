#include "hoveringpushbutton.h"

HoveringPushButton::HoveringPushButton(QWidget *parent) :
    QPushButton(parent)
{
    setAttribute(Qt::WA_Hover);
    //    this->setMouseTracking(true);
    //m_count = 0;
    //this->setText(QString::number(m_count));
}

bool HoveringPushButton::event(QEvent * e)
{
    switch(e->type())
    {
    case QEvent::HoverEnter:
        hoverEnter(static_cast<QHoverEvent*>(e));
        return true;
        break;
    case QEvent::HoverLeave:
        hoverLeave(static_cast<QHoverEvent*>(e));
        return true;
        break;
    case QEvent::HoverMove:
        hoverMove(static_cast<QHoverEvent*>(e));
        return true;
        break;
    default:
        break;
    }
    return QWidget::event(e);
}

void HoveringPushButton::enterEvent(QEvent * e)
{
    //qDebug() << Q_FUNC_INFO << e->type();
}

void HoveringPushButton::leaveEvent(QEvent * e)
{
    //qDebug() << Q_FUNC_INFO << e->type();
}


void HoveringPushButton::hoverEnter(QHoverEvent * event)
{
    emit s_hoverEnter();
    //qDebug() << Q_FUNC_INFO << event->type();
}

void HoveringPushButton::hoverLeave(QHoverEvent * event)
{
    emit s_hoverLeave();
    //m_count = 0;
    //qDebug() << Q_FUNC_INFO << event->type();
    //this->setText(QString::number(m_count));
}

void HoveringPushButton::hoverMove(QHoverEvent * event)
{
    emit s_hoverMove();
    //m_count++;
    //qDebug() << Q_FUNC_INFO << event->type() << m_count;
    //this->setText(QString::number(m_count));
}
