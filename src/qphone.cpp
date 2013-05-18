#include "qphone.h"

#include <QUrl>
#include <QSettings>

#include <QByteArray>

#include <QDebug>

#include "loggingconfiguration.h"
#include "mediaconfiguration.h"
#include "transportconfiguration.h"
#include "accountconfiguration.h"

namespace qphone {

QPhone::QPhone(QObject *parent) : QObject(parent),
    engine(nullptr), outStream(stdout), accountId(0)
{
}

pjsua_acc_id QPhone::getAccountId()
{
    return accountId;
}

void QPhone::onLogin()
{
    QSettings settings;
    //settings.setValue("foo", "bar");
    unsigned sipPort = settings.value("sip.port").toUInt();

    qpjsua::LoggingConfiguration loggingConfiguration = qpjsua::LoggingConfiguration::build()
            .withConsoleLevel(9999999)
            .withLogOutput(this, SLOT(onLog(int,QString)));

    qpjsua::TransportConfiguration transportConfiguration = qpjsua::TransportConfiguration::build()
            .withPort(sipPort);

    qpjsua::MediaConfiguration mediaConfiguration = qpjsua::MediaConfiguration::build();

    engine = qpjsua::Engine::build()
            .withLoggingConfiguration(loggingConfiguration)
            .withMediaConfiguration(mediaConfiguration)
            .withTransportConfiguration(transportConfiguration)
            .create();
    out(engine->lastError(), "Create Engine");
    if(engine->isValid() == false) {
        return;
    }
    connect(engine,
                    SIGNAL(incomingCall(qpjsua::AccountInfo, qpjsua::CallInfo)),
                    SLOT(onIncomingCall(qpjsua::AccountInfo, qpjsua::CallInfo)),
                    Qt::QueuedConnection);
    connect(engine,
                    SIGNAL(callState(qpjsua::CallInfo)),
                    SLOT(onCallState(qpjsua::CallInfo)),
                    Qt::QueuedConnection);
    connect(engine,
                    SIGNAL(callMediaState(qpjsua::CallInfo)),
                    SLOT(onCallMediaState(qpjsua::CallInfo)),
                    Qt::QueuedConnection);
    connect(engine,
                    SIGNAL(regStarted(qpjsua::AccountInfo, bool)),
                    SLOT(onRegStarted(qpjsua::AccountInfo, bool)),
                    Qt::QueuedConnection);

    QString realm = settings.value("realm").toString();
    QString scheme = settings.value("scheme").toString();
    QString username = settings.value("username").toString();
    QString password = settings.value("password").toString();
    QString registration = settings.value("registration").toString();
    QString sip = settings.value("sip").toString();
    QString proxy = settings.value("proxy").toString();
    unsigned rtpPort = settings.value("rtp.port").toUInt();

    qpjsua::AccountCredential *credential = qpjsua::AccountCredential::build()
            .withRealm(realm)
            .withScheme(scheme)
            .withUsername(username)
            .withPasswordType(PJSIP_CRED_DATA_PLAIN_PASSWD)
            .withPassword(password)
            .create();
    qpjsua::AccountConfiguration *accountConfiguration = qpjsua::AccountConfiguration::build()
            .withRegistrationUri("sip:" + registration)
            .withSipUrl("sip:" + sip)
            .withRtpPort(rtpPort)
            .withAllowContactRewrite(false)
            .addCredential(credential)
            .addProxy("sip:" + proxy)
            .create();

    accountId = engine->addAccount(accountConfiguration);

    out(engine->lastError(), "Add account");
    if(engine->isValid() == false) {
        return;
    }

    delete accountConfiguration;
    delete credential;
}

void QPhone::onLogout()
{
    if(engine) {
        delete engine;
        engine = nullptr;
    }
}

void QPhone::out(const qpjsua::PjError &anError, const QString &aMessage)
{
    QString message = aMessage;
    if(anError.getStatus() != PJ_SUCCESS) {
        message = QString("%1 Code: %2").arg(anError.getMessage()).arg(anError.getStatus());
    }
    outStream << ">>> Output: " << message << "\n";
    outStream.flush();
}

void QPhone::onLog(int level, QString message)
{
    outStream << "Level " << level << " " << message << "\n";
    outStream.flush();
}

void QPhone::onIncomingCall(qpjsua::AccountInfo anAccountInfo, qpjsua::CallInfo aCallInfo)
{
    emit incomingCall(anAccountInfo, aCallInfo);
}

void QPhone::onCallState(qpjsua::CallInfo aCallInfo)
{
    emit callState(aCallInfo);
}

void QPhone::onCallMediaState(qpjsua::CallInfo aCallInfo)
{
    emit callMediaState(aCallInfo);
}

void QPhone::onRegStarted(qpjsua::AccountInfo anAccountInfo, bool renew)
{
    emit regStarted(anAccountInfo, renew);
}


} // namespace qphone
