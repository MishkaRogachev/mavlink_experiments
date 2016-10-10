#ifndef MAVLINK_COMMUNICATOR_H
#define MAVLINK_COMMUNICATOR_H

// MAVLink
#include <mavlink_types.h>

// Qt
#include <QObject>
#include <QMap>

namespace domain
{
    class AbstractLink;

    class MavLinkCommunicator: public QObject
    {
        Q_OBJECT

    public:
        MavLinkCommunicator(uint8_t systemId, uint8_t componentId,
                            QObject* parent = nullptr);

    public slots:
        void addLink(AbstractLink* link, uint8_t channel);
        void removeLink(AbstractLink* link);

        void sendMessage(mavlink_message_t& message, AbstractLink* link);
        void sendMessageOnLastReceivedLink(mavlink_message_t& message);
        void sendMessageOnAllLinks(mavlink_message_t& message);

    signals:
        void messageReceived(const mavlink_message_t& message);

    protected slots:
        void onDataReceived(const QByteArray& data);

    protected:
        QMap<AbstractLink*, uint8_t> m_linkChannels;
        AbstractLink* m_lastReceivedLink;

        const uint8_t m_systemId;
        const uint8_t m_componentId;
    };
}

#endif // MAVLINK_COMMUNICATOR_H
