#include "acceptor.h"

namespace qphone {

Acceptor::Acceptor(QPhone *aPhone, QPhoneView *aView, QObject *parent) :
    QObject(parent), phone(aPhone), view(aView), callId(), code(PJSIP_SC_RINGING)
{
    view->setButtonText("Anrufen");
    connect(view, SIGNAL(accept()), SLOT(onCall()));
}

void Acceptor::onIncomingCall(qpjsua::AccountInfo anAccountInfo, qpjsua::CallInfo aCallInfo)
{
    view->accountInfoOut(anAccountInfo);
    view->callInfoOut(aCallInfo);

    callId = aCallInfo.getId();
    pjsua_call_answer(callId, code, nullptr, nullptr);

    view->setButtonText("Annehmen");
    connect(view, SIGNAL(accept()), SLOT(onAccept()));
}

void Acceptor::onCallState(qpjsua::CallInfo aCallInfo)
{
    view->callInfoOut(aCallInfo);

    if(aCallInfo.getInviteState() == PJSIP_INV_STATE_DISCONNECTED) {
      //  view->setButtonText("Anrufen");
      //  connect(view, SIGNAL(accept()), SLOT(onCall()));
    }
}

void Acceptor::onCallMediaState(qpjsua::CallInfo aCallInfo)
{
    view->callInfoOut(aCallInfo);

    if(aCallInfo.getMediaStatus() == PJSUA_CALL_MEDIA_ACTIVE) {
        pjsua_conf_connect(0, aCallInfo.getConferenceSlot());
        pjsua_conf_connect(aCallInfo.getConferenceSlot(), 0);

       // view->setButtonText("Auflegen");
      //  connect(view, SIGNAL(accept()), SLOT(onHangup()));
    }
}

void Acceptor::onRegStarted(qpjsua::AccountInfo anAccountInfo, bool renew)
{
    Q_UNUSED(renew);
    view->accountInfoOut(anAccountInfo);
}

void Acceptor::onBusy()
{
    code = PJSIP_SC_BUSY_HERE;
}

void Acceptor::onCancel()
{
    pjsua_call_answer(callId, PJSIP_SC_TEMPORARILY_UNAVAILABLE, nullptr, nullptr);
}

void Acceptor::onRing()
{
    code = PJSIP_SC_RINGING;
}

void Acceptor::onAccept()
{
    pjsua_call_answer(callId, PJSIP_SC_OK, nullptr, nullptr);
}

void Acceptor::onHangup()
{
    pjsua_call_hangup(callId, 0, nullptr, nullptr);
    view->setButtonText("Anrufen");
    connect(view, SIGNAL(accept()), SLOT(onCall()));
}

void Acceptor::onCall()
{
    QString callNumber = view->getCallNumber();
    QByteArray chr = callNumber.toLatin1();
    pj_str_t uri = pj_str(chr.data());
    pjsua_call_make_call(phone->getAccountId(), &uri, nullptr, nullptr, nullptr, &callId);

    view->setButtonText("Auflegen");
    connect(view, SIGNAL(accept()), SLOT(onHangup()));
}

} // namespace qphone
