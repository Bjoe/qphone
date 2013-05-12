
#include <QtGui/QGuiApplication>

#include "qphone.h"
#include "qphoneview.h"
#include "qphonehandler.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setOrganizationName("devolab");
    app.setOrganizationDomain("devolab.de");
    app.setApplicationName("QPjsua Example");

    qphone::QPhone phone;
    qphone::QPhoneView view;
    qphone::QPhoneHandler handler(&phone, &view);

    phone.connect(&view, SIGNAL(login()), SLOT(onLogin()));
    phone.connect(&view, SIGNAL(logout()), SLOT(onLogout()));

    handler.connect(&phone, SIGNAL(callMediaState(qpjsua::CallInfo)), SLOT(onCallMediaState(qpjsua::CallInfo)));
    handler.connect(&phone, SIGNAL(callState(qpjsua::CallInfo)), SLOT(onCallState(qpjsua::CallInfo)));
    handler.connect(&phone, SIGNAL(incomingCall(qpjsua::AccountInfo,qpjsua::CallInfo)), SLOT(onIncomingCall(qpjsua::AccountInfo,qpjsua::CallInfo)));
    handler.connect(&phone, SIGNAL(regStarted(qpjsua::AccountInfo,bool)), SLOT(onRegStarted(qpjsua::AccountInfo,bool)));
    handler.connect(&view, SIGNAL(busy()), SLOT(onBusy()));
    handler.connect(&view, SIGNAL(cancel()), SLOT(onCancel()));
    handler.connect(&view, SIGNAL(ring()), SLOT(onRing()));

    return app.exec();
}
