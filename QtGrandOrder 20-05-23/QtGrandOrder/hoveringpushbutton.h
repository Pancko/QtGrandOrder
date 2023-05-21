#ifndef HOVERINGPUSHBUTTON_H
#define HOVERINGPUSHBUTTON_H

#include <QPushButton>
#include <QHoverEvent>
#include <QEvent>

class HoveringPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit HoveringPushButton(QWidget *parent = 0);

    using QPushButton::QPushButton;

protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    bool event(QEvent * e);

    void hoverEnter(QHoverEvent * event);
    void hoverLeave(QHoverEvent * event);
    void hoverMove(QHoverEvent * event);

signals:
    void s_hoverEnter();
    void s_hoverLeave();
    void s_hoverMove();

public slots:

private:
    int m_count;
};

#endif // HOVERINGPUSHBUTTON_H
