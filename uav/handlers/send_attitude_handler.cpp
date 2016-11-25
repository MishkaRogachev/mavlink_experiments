#include "send_attitude_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QtMath>
#include <QDebug>

// Internal
#include "uav_model.h"
#include "mavlink_communicator.h"

using namespace domain;

SendAttitudeHandler::SendAttitudeHandler(MavLinkCommunicator* communicator,
                                         UavModel* model):
    AbstractHandler(communicator),
    m_model(model)
{
    this->startTimer(40); // 25 Hz
}

void SendAttitudeHandler::processMessage(const mavlink_message_t& message)
{
    Q_UNUSED(message)
}

void SendAttitudeHandler::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event)

    mavlink_message_t message;
    mavlink_attitude_t attitude;

    attitude.pitch = qDegreesToRadians(m_model->pitch());
    attitude.roll = qDegreesToRadians(m_model->roll());
    attitude.yaw = qDegreesToRadians(m_model->yaw());

    mavlink_msg_attitude_encode(m_communicator->systemId(),
                                m_communicator->componentId(),
                                &message, &attitude);

    m_communicator->sendMessageOnLastReceivedLink(message);
}
