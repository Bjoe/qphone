#include "acceptor.h"

#include <QDebug>

namespace qphone {

Acceptor::Acceptor(QPhoneView *aView, QObject *parent) :
    QObject(parent), view(aView), callInfo(), code(PJSIP_SC_RINGING)
{
}

void Acceptor::onIncomingCall(qpjsua::AccountInfo anAccountInfo, qpjsua::CallInfo aCallInfo)
{
    qDebug() << "incommingCall";
    view->accountInfoOut(anAccountInfo);
    view->callInfoOut(aCallInfo);

    callInfo = aCallInfo;
    pjsua_call_answer(aCallInfo.getId(), code, nullptr, nullptr);
}

void Acceptor::onCallState(qpjsua::CallInfo aCallInfo)
{
    qDebug() << "callState";
    view->callInfoOut(aCallInfo);
}

void Acceptor::onCallMediaState(qpjsua::CallInfo aCallInfo)
{
    qDebug() << "callInfo";
    view->callInfoOut(aCallInfo);

    if(aCallInfo.getMediaStatus() == PJSUA_CALL_MEDIA_ACTIVE) {
        pjsua_conf_connect(aCallInfo.getConferenceSlot(), 0);
        pjsua_conf_connect(0, aCallInfo.getConferenceSlot());
    }
}

void Acceptor::onRegStarted(qpjsua::AccountInfo anAccountInfo, bool renew)
{
    qDebug() << "regStarted";
    Q_UNUSED(renew);
    view->accountInfoOut(anAccountInfo);
}

void Acceptor::onBusy()
{
    code = PJSIP_SC_BUSY_HERE;
}

void Acceptor::onCancel()
{
    pjsua_call_answer(callInfo.getId(), PJSIP_SC_TEMPORARILY_UNAVAILABLE, nullptr, nullptr);
}

void Acceptor::onRing()
{
    code = PJSIP_SC_RINGING;
}

void Acceptor::onAccept()
{
    pjsua_call_answer(callInfo.getId(), PJSIP_SC_OK, nullptr, nullptr);
}

} // namespace qphone
