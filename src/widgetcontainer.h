#ifndef WIDGETCONTAINER_H
#define WIDGETCONTAINER_H

#include <QWidget>

class WidgetContainer : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetContainer(QWidget *parent = nullptr);
    static QWidget *createContainer(const QString &iAppName, bool iAutoOpen = true);
    static unsigned long findProcessId(const QString &iAppName);
signals:

public slots:
};

#endif // WIDGETCONTAINER_H
