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
        void sendMessageLastReceivedLink(mavlink_message_t& message);
        void sendMessageAllLinks(mavlink_message_t& message);

    signals:
        void messageReceived(const mavlink_message_t& message);

    protected slots:
        void onDataReceived(const QByteArray& data);

    protected:
        QMap<AbstractLink*, uint8_t> m_linkChannels;
        AbstractLink* m_lastReceivedLink = nullptr;

        const uint8_t m_systemId = 255;
        const uint8_t m_componentId = 0;
    };
}

#endif // MAVLINK_COMMUNICATOR_H
