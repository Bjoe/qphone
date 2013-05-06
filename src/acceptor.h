#ifndef QPHONE_ACCEPTOR_H
#define QPHONE_ACCEPTOR_H

#include <QObject>

#include <pjsua-lib/pjsua.h>

#include "qphoneview.h"
#include "accountinfo.h"
#include "callinfo.h"

namespace qphone {

class Acceptor : public QObject
{
    Q_OBJECT
public:
    explicit Acceptor(QPhoneView *aView, QObject *parent = 0);
    
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

private:
    QPhoneView *view;
    qpjsua::CallInfo callInfo;
    pjsip_status_code code;
};

} // namespace qphone

#endif // QPHONE_ACCEPTOR_H
