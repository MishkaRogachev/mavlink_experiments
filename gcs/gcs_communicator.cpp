#include "gcs_communicator.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QTimer>

using namespace domain;

GcsCommunicator::GcsCommunicator(QObject* parent):
    MavLinkCommunicator(255, 0, parent) // 255 is default id for GCS
{
    QTimer* heartbeatTimer = new QTimer(this);
    connect(heartbeatTimer, &QTimer::timeout, this, &GcsCommunicator::sendHeartbeat);

    heartbeatTimer->start(1000); // 1 Hz
}

void GcsCommunicator::sendHeartbeat()
{
    mavlink_message_t message;

    mavlink_heartbeat_t heartbeat;
    heartbeat.type = MAV_TYPE_GCS;
    mavlink_msg_heartbeat_encode(m_systemId, m_componentId, &message, &heartbeat);

    this->sendMessageAllLinks(message);
}
