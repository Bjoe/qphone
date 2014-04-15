#include "qphonehandler.h"

namespace qphone {

QPhoneHandler::QPhoneHandler(QObject *parent) :
    QObject(parent), callId(), code(PJSIP_SC_RINGING)
{
}

QString QPhoneHandler::state() const
{
    return m_state;
}

void QPhoneHandler::setState(const QString &state)
{
    m_state = state;
    emit stateChanged();
}

QString QPhoneHandler::remoteInfo() const
{
    return m_remoteInfo;
}

void QPhoneHandler::setRemoteInfo(const QString &info)
{
    m_remoteInfo = info;
    emit remoteInfoChanged();
}

QString QPhoneHandler::callState() const
{
    return m_callState;
}

void QPhoneHandler::setCallState(const QString &state)
{
    m_callState = state;
    emit callStateChanged();
}

QString QPhoneHandler::mediaState() const
{
    return m_mediaState;
}

void QPhoneHandler::setMediaState(const QString &state)
{
    m_mediaState = state;
    emit mediaStateChanged();
}

QString QPhoneHandler::callNumber() const
{
    return m_number;
}

void QPhoneHandler::setCallNumber(const QString &number)
{
    m_number = number;
    emit callNumberChanged();
}

QString QPhoneHandler::accountId() const
{
    return m_accountId;
}

void QPhoneHandler::setAccountId(const QString &accountId)
{
    m_accountId = accountId;
    emit accountIdChanged();
}

void QPhoneHandler::onIncomingCall(qpjsua::AccountInfo anAccountInfo, qpjsua::CallInfo aCallInfo)
{
    accountInfoOut(anAccountInfo);
    callInfoOut(aCallInfo);

    callId = aCallInfo.getId();
    pjsua_call_answer(callId, code, nullptr, nullptr);

    // TODO
    //view->setButtonText("Annehmen");
    //connect(view, SIGNAL(accept()), SLOT(onAccept()));
}

void QPhoneHandler::onCallState(qpjsua::CallInfo aCallInfo)
{
    callInfoOut(aCallInfo);

    if(aCallInfo.getInviteState() == PJSIP_INV_STATE_DISCONNECTED) {
      //  view->setButtonText("Anrufen");
      //  connect(view, SIGNAL(accept()), SLOT(onCall()));
    }
}

void QPhoneHandler::onCallMediaState(qpjsua::CallInfo aCallInfo)
{
    callInfoOut(aCallInfo);

    if(aCallInfo.getMediaStatus() == PJSUA_CALL_MEDIA_ACTIVE) {
        pjsua_conf_connect(0, aCallInfo.getConferenceSlot());
        pjsua_conf_connect(aCallInfo.getConferenceSlot(), 0);

       // view->setButtonText("Auflegen");
      //  connect(view, SIGNAL(accept()), SLOT(onHangup()));
    }
}

void QPhoneHandler::onRegStarted(qpjsua::AccountInfo anAccountInfo, bool renew)
{
    Q_UNUSED(renew);
    accountInfoOut(anAccountInfo);
}

void QPhoneHandler::onBusy()
{
    code = PJSIP_SC_BUSY_HERE;
}

void QPhoneHandler::onCancel()
{
    pjsua_call_answer(callId, PJSIP_SC_TEMPORARILY_UNAVAILABLE, nullptr, nullptr);
}

void QPhoneHandler::onRing()
{
    code = PJSIP_SC_RINGING;
}

void QPhoneHandler::onAccept()
{
    pjsua_call_answer(callId, PJSIP_SC_OK, nullptr, nullptr);
}

void QPhoneHandler::onHangup()
{
    pjsua_call_hangup(callId, 0, nullptr, nullptr);

    // TODO
    // view->setButtonText("Anrufen");
    // connect(view, SIGNAL(accept()), SLOT(onCall()));
}

void QPhoneHandler::onCall()
{
    QByteArray chr = m_number.toLatin1();
    int id = m_accountId.toInt();
    pj_str_t uri = pj_str(chr.data());
    pjsua_acc_id accountId = static_cast<pjsua_acc_id>(id);
    pjsua_call_make_call(accountId, &uri, nullptr, nullptr, nullptr, &callId);

    // TODO
    //view->setButtonText("Auflegen");
    //connect(view, SIGNAL(accept()), SLOT(onHangup()));
}

void QPhoneHandler::callInfoOut(qpjsua::CallInfo aCallInfo)
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

void QPhoneHandler::accountInfoOut(qpjsua::AccountInfo anAccountInfo)
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
