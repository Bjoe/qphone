#include "qphoneview.h"

#include <QQuickItem>
#include <QQmlProperty>

#include <pjsua-lib/pjsua.h>
#include "pjerror.h"

#include "config.h"

namespace qphone {

QPhoneView::QPhoneView(QObject *parent) :
    QObject(parent), view(new QQuickView())
{
    view->setSource(QUrl::fromLocalFile(QML_PATH));

    QObject *rootObject = view->rootObject();
    connect(rootObject, SIGNAL(qLogin()), SLOT(onLogin()));
    connect(rootObject, SIGNAL(qLogout()), SLOT(onLogout()));
    connect(rootObject, SIGNAL(qBusy()), SLOT(onBusy()));
    connect(rootObject, SIGNAL(qCancel()), SLOT(onCancel()));
    connect(rootObject, SIGNAL(qRing()), SLOT(onRing()));
    connect(rootObject, SIGNAL(qAccept()), SLOT(onAccept()));

    view->show();
}

void QPhoneView::onLogin()
{
    emit login();
}

void QPhoneView::onLogout()
{
    emit logout();
}

void QPhoneView::onBusy()
{
    emit busy();
}

void QPhoneView::onCancel()
{
    emit cancel();
}

void QPhoneView::onRing()
{
    emit ring();
}

void QPhoneView::onAccept()
{
    emit accept();
}

void QPhoneView::callInfoOut(qpjsua::CallInfo aCallInfo)
{
    QQuickItem *rootObject = view->rootObject();
    QQmlProperty(rootObject, "qIncommingCall").write(aCallInfo.getRemoteInfo());
    QQmlProperty(rootObject, "qCallState").write(aCallInfo.getStateText());
    QString status;
    switch(aCallInfo.getMediaStatus()) {
    case PJSUA_CALL_MEDIA_NONE:
        status = "NONE";
        break;
    case PJSUA_CALL_MEDIA_ACTIVE:
        status = "ACTIVE";
        break;
    case PJSUA_CALL_MEDIA_LOCAL_HOLD:
        status = "LOCAL HOLD";
        break;
    case PJSUA_CALL_MEDIA_REMOTE_HOLD:
        status = "REMOTE HOLD";
        break;
    case PJSUA_CALL_MEDIA_ERROR:
        status = "ERROR";
        break;
    default:
        status = "ERROR";
    }

    QQmlProperty(rootObject, "qCallMediaState").write(status);
}

void QPhoneView::accountInfoOut(qpjsua::AccountInfo anAccountInfo)
{
    QString state;
    if(anAccountInfo.hasRegistartion()) {
        state.append("Client is registered\n");
    } else {
        state.append("Client is not registered\n");
    }
    state.append(anAccountInfo.getStatusText() + "\n");
    state.append(anAccountInfo.getLastError() + "\n");

    QQuickItem *item = view->rootObject();
    QQmlProperty(item, "qState").write(state);
}

} // namespace qphone
