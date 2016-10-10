#ifndef ABSTRACT_HANDLER_H
#define ABSTRACT_HANDLER_H

// MAVLink
#include <mavlink_types.h>

// Qt
#include <QObject>

namespace domain
{
    class AbstractHandler: public QObject
    {
        Q_OBJECT

    public:
        explicit AbstractHandler(QObject* parent);

    public slots:
        virtual void processMessage(const mavlink_message_t& message) = 0;

    signals:
        void sendMessage(mavlink_message_t& message);
    };
}

#endif // ABSTRACT_HANDLER_H
