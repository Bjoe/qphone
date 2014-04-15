#include "mainwindowcontroller.h"

#include <QtQml>

#include "qphone.h"
#include "qphonehandler.h"

namespace qphone {

MainWindowController::~MainWindowController()
{
    delete m_engine;
    delete m_window;
}

MainWindowController *MainWindowController::createInstance(const QString &qmlUrl)
{
    qmlRegisterType<qphone::QPhone>("Phone", 1, 0, "QPhone");

    QQmlApplicationEngine* engine = new QQmlApplicationEngine();
    initContext(engine);
    engine->load(QUrl(qmlUrl));
    QQuickWindow* window = createAndInitWindow(engine);
    return new MainWindowController(engine, window);
}

void MainWindowController::show()
{
    m_window->show();
}

void MainWindowController::initContext(QQmlApplicationEngine *engine)
{
    QQmlContext* context = engine->rootContext();
}

QQuickWindow *MainWindowController::createAndInitWindow(QQmlApplicationEngine *engine)
{
    QList<QObject *> list = engine->rootObjects();
    QObject *topLevel = list.value(0);
    QQuickWindow* window = qobject_cast<QQuickWindow *>(topLevel);

    return window;
}

MainWindowController::MainWindowController(QQmlApplicationEngine *engine, QQuickWindow *window)
    : m_engine(engine), m_window(window)
{
}

} // namespace qphone
