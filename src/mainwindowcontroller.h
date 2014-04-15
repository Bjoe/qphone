#ifndef QPHONE_MAINWINDOWCONTROLLER_H
#define QPHONE_MAINWINDOWCONTROLLER_H

#include <QString>
#include <QtQml/QQmlApplicationEngine>
#include <QtQuick/QQuickWindow>

namespace qphone {

class MainWindowController
{
public:
    ~MainWindowController();

    static MainWindowController *createInstance(const QString &qmlUrl);
    void show();

private:
    static void initContext(QQmlApplicationEngine *engine);
    static QQuickWindow *createAndInitWindow(QQmlApplicationEngine *engine);
    MainWindowController(QQmlApplicationEngine* engine, QQuickWindow* window);

    QQmlApplicationEngine* m_engine;
    QQuickWindow* m_window;
};

} // namespace qphone

#endif // QPHONE_MAINWINDOWCONTROLLER_H
