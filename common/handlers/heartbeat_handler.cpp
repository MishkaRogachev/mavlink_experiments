#include "heartbeat_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDebug>

// Internal
#include "mavlink_communicator.h"

using namespace domain;

HeartbeatHandler::HeartbeatHandler(uint8_t type, MavLinkCommunicator* communicator):
    AbstractHandler(communicator),
    m_type(type)
{
    this->startTimer(1000); // 1 Hz
}

void HeartbeatHandler::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event)

    mavlink_message_t message;
    mavlink_heartbeat_t heartbeat;
    heartbeat.type = m_type;

    mavlink_msg_heartbeat_encode(m_communicator->systemId(),
                                 m_communicator->componentId(),
                                 &message, &heartbeat);

    m_communicator->sendMessageOnAllLinks(message);
}

void HeartbeatHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_HEARTBEAT) return;

    mavlink_heartbeat_t heartbeat;
    mavlink_msg_heartbeat_decode(&message, &heartbeat);

    qDebug() << "Heartbeat received, system type:" << heartbeat.type
             << "System status:" << heartbeat.system_status;
}
