#include "heartbeat_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDebug>

using namespace domain;

HeartbeatHandler::HeartbeatHandler(uint8_t type, QObject* parent):
    AbstractHandler(parent),
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

    // sysid и comid будут перезаписаны mavlink_finalize_message_chan
    mavlink_msg_heartbeat_encode(0, 0, &message, &heartbeat);

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
