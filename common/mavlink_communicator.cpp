#include "mavlink_communicator.h"

// MAVLink
#include <mavlink.h>

// Internal
#include "abstract_link.h"

using namespace domain;

MavLinkCommunicator::MavLinkCommunicator(uint8_t systemId, uint8_t componentId,
                                         QObject* parent):
    QObject(parent),
    m_lastReceivedLink(nullptr),
    m_systemId(systemId),
    m_componentId(componentId)
{
    qRegisterMetaType<mavlink_message_t>("mavlink_message_t");
}

QList<AbstractLink*> MavLinkCommunicator::links() const
{
    return m_linkChannels.keys();
}

uint8_t MavLinkCommunicator::systemId() const
{
    return m_systemId;
}

uint8_t MavLinkCommunicator::componentId() const
{
    return m_componentId;
}

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

void MavLinkCommunicator::setSystemId(uint8_t systemId)
{
    m_systemId = systemId;
}

void MavLinkCommunicator::setComponentId(uint8_t componentId)
{
    m_componentId = componentId;
}

void MavLinkCommunicator::sendMessage(mavlink_message_t& message, AbstractLink* link)
{
    if (!link || !link->isUp()) return;

    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    int lenght = mavlink_msg_to_send_buffer(buffer, &message);

    if (!lenght) return;
    link->sendData(QByteArray((const char*)buffer, lenght));
}

void MavLinkCommunicator::sendMessageOnLastReceivedLink(mavlink_message_t& message)
{
    this->sendMessage(message, m_lastReceivedLink);
}

void MavLinkCommunicator::sendMessageOnAllLinks(mavlink_message_t& message)
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

        emit messageReceived(message);
    }

    // TODO: Link RX status
}
