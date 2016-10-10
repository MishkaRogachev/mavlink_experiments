#include "heartbeat_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDebug>

using namespace domain;

HeartbeatHandler::HeartbeatHandler(uint8_t type, uint8_t systemId,
                                   uint8_t componentId, QObject* parent):
    AbstractHandler(parent),
    m_type(type),
    m_systemId(systemId),
    m_componentId(componentId)
{
    this->startTimer(1000); // 1 Hz
}

void HeartbeatHandler::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event)

    mavlink_message_t message;
    mavlink_heartbeat_t heartbeat;
    heartbeat.type = m_type;

    mavlink_msg_heartbeat_encode(m_systemId, m_componentId,
                                 &message, &heartbeat);

    emit sendMessage(message);
}

void HeartbeatHandler::processMessage(const mavlink_message_t& message)
{
    // проверям, можем ли обработать пакет
    if (message.msgid != MAVLINK_MSG_ID_HEARTBEAT) return;

    mavlink_heartbeat_t heartbeat; // создаём сообщение heartbeat
    mavlink_msg_heartbeat_decode(&message, &heartbeat); // наполняем его из полученного пакета

    qDebug() << "Heartbeat received, system type:" << heartbeat.type
             << "System status:" << heartbeat.system_status;
}
