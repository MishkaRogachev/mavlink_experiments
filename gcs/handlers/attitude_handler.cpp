#include "attitude_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QtMath>
#include <QDebug>

using namespace domain;

AttitudeHandler::AttitudeHandler(MavLinkCommunicator* communicator):
    AbstractHandler(communicator)
{}

void AttitudeHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_ATTITUDE ||
        message.sysid == 0) return;

    mavlink_attitude_t attitude;
    mavlink_msg_attitude_decode(&message, &attitude);

    qDebug() << "pitch" << qRadiansToDegrees(attitude.pitch)
             << "roll" << qRadiansToDegrees(attitude.roll)
             << "yaw" << qRadiansToDegrees(attitude.yaw);
}
