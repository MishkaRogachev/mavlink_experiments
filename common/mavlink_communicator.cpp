#include "mavlink_communicator.h"

// MAVLink
#include <mavlink.h>
#include <mavlink_types.h>

// Qt
#include <QDebug>

// Internal
#include "abstract_link.h"

using namespace domain;

MavLinkCommunicator::MavLinkCommunicator(uint8_t systemId, uint8_t componentId,
                                         QObject* parent):
    QObject(parent),
    m_systemId(systemId),
    m_componentId(componentId)
{}

void MavLinkCommunicator::addLink(AbstractLink* link, uint8_t channel)
{
    if (m_linkChannels.contains(link)) return;

    m_linkChannels[link] = channel;
    connect(link, &AbstractLink::dataReceived,
            this, &MavLinkCommunicator::onDataReceived);
}

void MavLinkCommunicator::removeLink(AbstractLink* link)
{
    if (!m_linkChannels.contains(link)) return;

    m_linkChannels.remove(link);
    disconnect(link, &AbstractLink::dataReceived,
            this, &MavLinkCommunicator::onDataReceived);
}

void MavLinkCommunicator::sendMessage(mavlink_message_t& message, AbstractLink* link)
{
    if (!link || !link->isUp()) return;

    static const uint8_t messageKeys[256] = MAVLINK_MESSAGE_CRCS;
    mavlink_finalize_message_chan(&message,
                                  m_systemId,
                                  m_componentId,
                                  m_linkChannels.value(link, 0),
                                  message.len,
                                  message.len,
                                  messageKeys[message.msgid]);

    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    int lenght = mavlink_msg_to_send_buffer(buffer, &message);

    if (!lenght) return;
    link->sendData(QByteArray((const char*)buffer, lenght));

    qDebug() << "Sent packet from(" << message.sysid << ":" <<
                message.compid << ") with id: " << message.msgid << "Ch:" <<
                m_linkChannels.value(link, 0);

    // TODO: Link TX status
}

void MavLinkCommunicator::sendMessageLastReceivedLink(mavlink_message_t& message)
{
    this->sendMessage(message, m_lastReceivedLink);
}

void MavLinkCommunicator::sendMessageAllLinks(mavlink_message_t& message)
{
    for (AbstractLink* link: m_linkChannels.keys())
        this->sendMessage(message, link);
}

void MavLinkCommunicator::onDataReceived(const QByteArray& data)
{
    mavlink_message_t message;
    mavlink_status_t status;

    m_lastReceivedLink = qobject_cast<AbstractLink*>(this->sender());
    if (!m_lastReceivedLink) return;

    uint8_t channel = m_linkChannels.value(m_lastReceivedLink);
    for (int pos = 0; pos < data.length(); ++pos)
    {
        if (!mavlink_parse_char(channel, (uint8_t)data[pos],
                                &message, &status))
            continue;

        qDebug() << "Received packet from(" << message.sysid << ":" <<
                 message.compid << ") with id: " << message.msgid <<
                    "Ch:" << channel;

        emit messageReceived(message);
    }

    // TODO: Link RX status
}
