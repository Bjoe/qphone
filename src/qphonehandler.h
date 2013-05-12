#ifndef QPHONE_QPHONEHANDLER_H
#define QPHONE_QPHONEHANDLER_H

#include <QObject>

#include <pjsua-lib/pjsua.h>

#include "qphone.h"
#include "qphoneview.h"
#include "accountinfo.h"
#include "callinfo.h"

namespace qphone {

class QPhoneHandler : public QObject
{
    Q_OBJECT
public:
    explicit QPhoneHandler(QPhone *aPhone, QPhoneView *aView, QObject *parent = 0);
    
signals:
    
public slots:
    void onIncomingCall(qpjsua::AccountInfo anAccountInfo, qpjsua::CallInfo aCallInfo);
    void onCallState(qpjsua::CallInfo aCallInfo);
    void onCallMediaState(qpjsua::CallInfo aCallInfo);
    void onRegStarted(qpjsua::AccountInfo anAccountInfo, bool renew);

    void onBusy();
    void onCancel();
    void onRing();
    void onAccept();
    void onHangup();
    void onCall();

private:
    QPhone *phone;
    QPhoneView *view;
    pjsua_call_id callId;
    pjsip_status_code code;
};

} // namespace qphone

#endif // QPHONE_QPHONEHANDLER_H
