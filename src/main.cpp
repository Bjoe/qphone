
#include <QtGui/QGuiApplication>

#include "qphone.h"
#include "qphoneview.h"
#include "acceptor.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setOrganizationName("devolab");
    app.setOrganizationDomain("devolab.de");
    app.setApplicationName("QPjsua Example");

    qphone::QPhone phone;
    qphone::QPhoneView view;
    qphone::Acceptor acceptor(&phone, &view);

    phone.connect(&view, SIGNAL(login()), SLOT(onLogin()));
    phone.connect(&view, SIGNAL(logout()), SLOT(onLogout()));

    acceptor.connect(&phone, SIGNAL(callMediaState(qpjsua::CallInfo)), SLOT(onCallMediaState(qpjsua::CallInfo)));
    acceptor.connect(&phone, SIGNAL(callState(qpjsua::CallInfo)), SLOT(onCallState(qpjsua::CallInfo)));
    acceptor.connect(&phone, SIGNAL(incomingCall(qpjsua::AccountInfo,qpjsua::CallInfo)), SLOT(onIncomingCall(qpjsua::AccountInfo,qpjsua::CallInfo)));
    acceptor.connect(&phone, SIGNAL(regStarted(qpjsua::AccountInfo,bool)), SLOT(onRegStarted(qpjsua::AccountInfo,bool)));
    acceptor.connect(&view, SIGNAL(busy()), SLOT(onBusy()));
    acceptor.connect(&view, SIGNAL(cancel()), SLOT(onCancel()));
    acceptor.connect(&view, SIGNAL(ring()), SLOT(onRing()));

    return app.exec();
}
