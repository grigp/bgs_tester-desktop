#ifndef BLEDATAPROVIDER_H
#define BLEDATAPROVIDER_H

#include <QObject>

class BLEDataProvider : public QObject
{
    Q_OBJECT
public:
    explicit BLEDataProvider(QObject *parent = nullptr);

signals:

public slots:
};

#endif // BLEDATAPROVIDER_H
