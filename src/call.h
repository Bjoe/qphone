#ifndef QPHONE_CALL_H
#define QPHONE_CALL_H

#include <QObject>

namespace qphone {

class Call : public QObject
{
    Q_OBJECT
public:
    explicit Call(QObject *parent = 0);
    
signals:
    
public slots:
    
};

} // namespace qphone

#endif // QPHONE_CALL_H
