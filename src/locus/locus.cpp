#include <QDebug>
#include "locus.h"

MyPushButton::MyPushButton(const QString &text)
    : QPushButton(text)
{
    setObjectName("mypushbutton");
    qDebug() << "My PushButton has been constructed";
}
