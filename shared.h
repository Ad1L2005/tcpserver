#ifndef SHARED_H
#define SHARED_H

#include <QTime>
#include <QString>
#include <QDataStream>

struct ClientInfo {
    QTime time;
    QString message;
    int clientCount;
};

inline QDataStream &operator<<(QDataStream &out, const ClientInfo &info) {
    out << info.time << info.message << info.clientCount;
    return out;
}

inline QDataStream &operator>>(QDataStream &in, ClientInfo &info) {
    in >> info.time >> info.message >> info.clientCount;
    return in;
}

#endif // SHARED_H
