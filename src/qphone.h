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

public:
    explicit QPhone(QObject *parent = 0);
    void show();
    void out(const qpjsua::PjError &anError, const QString &aMessage);

public slots:
    void onLogin();
    void onLogout();

private slots:
    void onLog(int level, QString message);
    void onIncomingCall(qpjsua::AccountInfo anAccountInfo, qpjsua::CallInfo aCallInfo);
    void onCallState(qpjsua::CallInfo aCallInfo);
    void onCallMediaState(qpjsua::CallInfo aCallInfo);
    void onRegStarted(qpjsua::AccountInfo anAccountInfo, bool renew);

signals:
    void incomingCall(qpjsua::AccountInfo anAccountInfo, qpjsua::CallInfo aCallInfo);
    void callState(qpjsua::CallInfo aCallInfo);
    void callMediaState(qpjsua::CallInfo aCallInfo);
    void regStarted(qpjsua::AccountInfo anAccountInfo, bool renew);

private:
    void callInfoOut(qpjsua::CallInfo aCallInfo);
    void accountInfoOut(qpjsua::AccountInfo anAccountInfo);

    qpjsua::Engine *engine;
    QTextStream outStream;
};

} // namespace qphone

#endif // QPHONE_QPHONE_H
