#ifndef QPHONE_QPHONEHANDLER_H
#define QPHONE_QPHONEHANDLER_H

#include <QObject>
#include <QString>

#include <pjsua-lib/pjsua.h>

#include "qphone.h"
#include "accountinfo.h"
#include "callinfo.h"

namespace qphone {

class QPhoneHandler : public QObject
{   
    Q_OBJECT

    Q_PROPERTY(QString state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(QString callState READ callState WRITE setCallState NOTIFY callStateChanged)
    Q_PROPERTY(QString remoteInfo READ remoteInfo WRITE setRemoteInfo NOTIFY remoteInfoChanged)
    Q_PROPERTY(QString mediaState READ mediaState WRITE setMediaState NOTIFY mediaStateChanged)
    Q_PROPERTY(QString callNumber READ callNumber WRITE setCallNumber NOTIFY callNumberChanged)
    Q_PROPERTY(QString accountId READ accountId WRITE setAccountId NOTIFY accountIdChanged)

public:
    explicit QPhoneHandler(QObject *parent = 0);
    
    QString state() const;
    void setState(const QString &state);

    QString remoteInfo() const;
    void setRemoteInfo(const QString &info);

    QString callState() const;
    void setCallState(const QString &state);

    QString mediaState() const;
    void setMediaState(const QString &state);

    QString callNumber() const;
    void setCallNumber(const QString &number);

    QString accountId() const;
    void setAccountId(const QString &accountId);

signals:
    void stateChanged();
    void callStateChanged();
    void remoteInfoChanged();
    void mediaStateChanged();
    void callNumberChanged();
    void accountIdChanged();

public slots:
    void onIncomingCall(qpjsua::AccountInfo anAccountInfo, qpjsua::CallInfo aCallInfo);
    void onCallState(qpjsua::CallInfo aCallInfo);
    void onCallMediaState(qpjsua::CallInfo aCallInfo);
    void onRegStarted(qpjsua::AccountInfo anAccountInfo, bool renew);

    void onBusy();
    void onRing();
    void onCancel();
    void onAccept();
    void onHangup();
    void onCall();

private:
    QString m_remoteInfo;
    QString m_callState;
    QString m_mediaState;
    QString m_state;
    QString m_number;
    QString m_accountId;

    pjsua_call_id callId;
    pjsip_status_code code;

    void callInfoOut(qpjsua::CallInfo aCallInfo);
    void accountInfoOut(qpjsua::AccountInfo anAccountInfo);
};

} // namespace qphone

#endif // QPHONE_QPHONEHANDLER_H
