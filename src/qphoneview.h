#ifndef QPHONE_QPHONEVIEW_H
#define QPHONE_QPHONEVIEW_H

#include <QObject>
#include <QtQuick/QQuickView>
#include "callinfo.h"
#include "accountinfo.h"

namespace qphone {

class QPhoneView : public QObject
{
    Q_OBJECT
public:
    explicit QPhoneView(QObject *parent = 0);
    
    void setButtonText(const QString &aText);
    QString getCallNumber();
    void accountInfoOut(qpjsua::AccountInfo anAccountInfo);
    void callInfoOut(qpjsua::CallInfo aCallInfo);

signals:
    void login();
    void logout();
    void busy();
    void cancel();
    void ring();
    void accept();

public slots:

private slots:
    void onLogin();
    void onLogout();
    void onBusy();
    void onCancel();
    void onRing();
    void onAccept();

private:
    QQuickView *view;
};

} // namespace qphone

#endif // QPHONE_QPHONEVIEW_H
