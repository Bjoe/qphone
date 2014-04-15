#include "qphone.h"

#include <QDebug>
#include <QUrl>
#include <QSettings>

#include <QByteArray>

#include "loggingconfiguration.h"
#include "mediaconfiguration.h"
#include "transportconfiguration.h"
#include "accountconfiguration.h"

namespace qphone {

QPhone::QPhone(QObject *parent) : QObject(parent)
{
}

QString QPhone::state() const
{
    return m_state;
}

void QPhone::setState(const QString &state)
{
    m_state = state;
    emit stateChanged();
}

QString QPhone::remoteInfo() const
{
    return m_remoteInfo;
}

void QPhone::setRemoteInfo(const QString &info)
{
    m_remoteInfo = info;
    emit remoteInfoChanged();
}

QString QPhone::callState() const
{
    return m_callState;
}

void QPhone::setCallState(const QString &state)
{
    m_callState = state;
    emit callStateChanged();
}

QString QPhone::mediaState() const
{
    return m_mediaState;
}

void QPhone::setMediaState(const QString &state)
{
    m_mediaState = state;
    emit mediaStateChanged();
}

QString QPhone::callNumber() const
{
    return m_number;
}

void QPhone::setCallNumber(const QString &number)
{
    m_number = number;
    emit callNumberChanged();
}

QPhone::Status QPhone::phoneState() const
{
    return m_phoneState;
}

void QPhone::setPhoneState(const QPhone::Status &state)
{
    m_phoneState = state;
    emit phoneStateChanged();
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

    m_engine = qpjsua::Engine::build()
            .withLoggingConfiguration(loggingConfiguration)
            .withMediaConfiguration(mediaConfiguration)
            .withTransportConfiguration(transportConfiguration)
            .create();
    out(m_engine->lastError(), "Create Engine");
    if(m_engine->isValid() == false) {
        return;
    }
    connect(m_engine,
                    SIGNAL(incomingCall(qpjsua::AccountInfo, qpjsua::CallInfo)),
                    SLOT(onIncomingCall(qpjsua::AccountInfo, qpjsua::CallInfo)),
                    Qt::QueuedConnection);
    connect(m_engine,
                    SIGNAL(callState(qpjsua::CallInfo)),
                    SLOT(onCallState(qpjsua::CallInfo)),
                    Qt::QueuedConnection);
    connect(m_engine,
                    SIGNAL(callMediaState(qpjsua::CallInfo)),
                    SLOT(onCallMediaState(qpjsua::CallInfo)),
                    Qt::QueuedConnection);
    connect(m_engine,
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

    m_accountId = m_engine->addAccount(accountConfiguration);

    out(m_engine->lastError(), "Add account");
    if(m_engine->isValid() == false) {
        return;
    }

    delete accountConfiguration;
    delete credential;
}

void QPhone::onLogout()
{
    if(m_engine) {
        delete m_engine;
        m_engine = nullptr;
    }
}

void QPhone::out(const qpjsua::PjError &anError, const QString &aMessage)
{
    QString message = aMessage;
    if(anError.getStatus() != PJ_SUCCESS) {
        message = QString("%1 Code: %2").arg(anError.getMessage()).arg(anError.getStatus());
    }
    qDebug() << ">>> Output: " << message;
}

void QPhone::onLog(int level, QString message)
{
    qDebug() << "Level " << level << " " << message;
}

void QPhone::onIncomingCall(qpjsua::AccountInfo anAccountInfo, qpjsua::CallInfo aCallInfo)
{
    accountInfoOut(anAccountInfo);
    callInfoOut(aCallInfo);

    m_callId = aCallInfo.getId();

    pjsip_status_code code = static_cast<pjsip_status_code>(m_phoneState);
    pjsua_call_answer(m_callId, code, nullptr, nullptr);

}

void QPhone::onCallState(qpjsua::CallInfo aCallInfo)
{
    callInfoOut(aCallInfo);

    if(aCallInfo.getInviteState() == PJSIP_INV_STATE_DISCONNECTED) {
      //  view->setButtonText("Anrufen");
      //  connect(view, SIGNAL(accept()), SLOT(onCall()));
    }
}

void QPhone::onCallMediaState(qpjsua::CallInfo aCallInfo)
{
    callInfoOut(aCallInfo);

    if(aCallInfo.getMediaStatus() == PJSUA_CALL_MEDIA_ACTIVE) {
        pjsua_conf_connect(0, aCallInfo.getConferenceSlot());
        pjsua_conf_connect(aCallInfo.getConferenceSlot(), 0);

       // view->setButtonText("Auflegen");
      //  connect(view, SIGNAL(accept()), SLOT(onHangup()));
    }
}

void QPhone::onRegStarted(qpjsua::AccountInfo anAccountInfo, bool renew)
{
    Q_UNUSED(renew);
    accountInfoOut(anAccountInfo);
}

void QPhone::onCancel()
{
    pjsua_call_answer(m_callId, PJSIP_SC_TEMPORARILY_UNAVAILABLE, nullptr, nullptr);
}

void QPhone::onAccept()
{
    pjsua_call_answer(m_callId, PJSIP_SC_OK, nullptr, nullptr);
}

void QPhone::onHangup()
{
    pjsua_call_hangup(m_callId, 0, nullptr, nullptr);

    // TODO
    // view->setButtonText("Anrufen");
    // connect(view, SIGNAL(accept()), SLOT(onCall()));
}

void QPhone::onCall()
{
    QByteArray chr = m_number.toLatin1();
    pj_str_t uri = pj_str(chr.data());
    pjsua_call_make_call(m_accountId, &uri, nullptr, nullptr, nullptr, &m_callId);

    // TODO
    //view->setButtonText("Auflegen");
    //connect(view, SIGNAL(accept()), SLOT(onHangup()));
}

void QPhone::callInfoOut(qpjsua::CallInfo aCallInfo)
{
    m_remoteInfo = aCallInfo.getRemoteInfo();
    m_callState = aCallInfo.getStateText();

    switch(aCallInfo.getMediaStatus()) {
    case PJSUA_CALL_MEDIA_NONE:
        m_mediaState = "NONE";
        break;
    case PJSUA_CALL_MEDIA_ACTIVE:
        m_mediaState = "ACTIVE";
        break;
    case PJSUA_CALL_MEDIA_LOCAL_HOLD:
        m_mediaState = "LOCAL HOLD";
        break;
    case PJSUA_CALL_MEDIA_REMOTE_HOLD:
        m_mediaState = "REMOTE HOLD";
        break;
    case PJSUA_CALL_MEDIA_ERROR:
        m_mediaState = "ERROR";
        break;
    default:
        m_mediaState = "ERROR";
    }
    emit mediaStateChanged();
}

void QPhone::accountInfoOut(qpjsua::AccountInfo anAccountInfo)
{
    m_state.clear();

    if(anAccountInfo.hasRegistartion()) {
        m_state.append("Client is registered\n");
    } else {
        m_state.append("Client is not registered\n");
    }
    m_state.append(QString("Status Text: %1\n").arg(anAccountInfo.getStatusText()));
    m_state.append(QString("Last Error: %1\n").arg(anAccountInfo.getLastError()));
    emit stateChanged();
}

} // namespace qphone
