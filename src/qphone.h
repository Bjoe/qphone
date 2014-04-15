#ifndef QPHONE_QPHONE_H
#define QPHONE_QPHONE_H

#include <QObject>
#include <QString>
#include <QTextStream>

#include <pjsua-lib/pjsua.h>
#include "pjerror.h"
#include "callinfo.h"
#include "accountinfo.h"
#include "engine.h"

namespace qphone {

class QPhone : public QObject
{
    Q_OBJECT

    Q_ENUMS(Status)

    Q_PROPERTY(QString state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(QString callState READ callState WRITE setCallState NOTIFY callStateChanged)
    Q_PROPERTY(QString remoteInfo READ remoteInfo WRITE setRemoteInfo NOTIFY remoteInfoChanged)
    Q_PROPERTY(QString mediaState READ mediaState WRITE setMediaState NOTIFY mediaStateChanged)
    Q_PROPERTY(QString callNumber READ callNumber WRITE setCallNumber NOTIFY callNumberChanged)
    Q_PROPERTY(Status phoneState READ phoneState WRITE setPhoneState NOTIFY phoneStateChanged)

public:
    enum class Status { RINGING = PJSIP_SC_RINGING, BUSY = PJSIP_SC_BUSY_HERE};

    explicit QPhone(QObject *parent = 0);

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

    Status phoneState() const;
    void setPhoneState(const Status &state);

    void out(const qpjsua::PjError &anError, const QString &aMessage);

public slots:
    void onLogin();
    void onLogout();
    void onCancel();
    void onAccept();
    void onHangup();
    void onCall();

private slots:
    void onIncomingCall(qpjsua::AccountInfo anAccountInfo, qpjsua::CallInfo aCallInfo);
    void onCallState(qpjsua::CallInfo aCallInfo);
    void onCallMediaState(qpjsua::CallInfo aCallInfo);
    void onRegStarted(qpjsua::AccountInfo anAccountInfo, bool renew);
    void onLog(int level, QString message);

signals:
    void stateChanged();
    void callStateChanged();
    void remoteInfoChanged();
    void mediaStateChanged();
    void callNumberChanged();
    void phoneStateChanged();

private:
    void callInfoOut(qpjsua::CallInfo aCallInfo);
    void accountInfoOut(qpjsua::AccountInfo anAccountInfo);

    QString m_remoteInfo = "";
    QString m_callState = "";
    QString m_mediaState = "";
    QString m_state = "";
    QString m_number = "";
    Status m_phoneState = Status::RINGING;

    qpjsua::Engine *m_engine = nullptr;
    pjsua_acc_id m_accountId = 0;
    pjsua_call_id m_callId = 0;
};

} // namespace qphone

#endif // QPHONE_QPHONE_H
