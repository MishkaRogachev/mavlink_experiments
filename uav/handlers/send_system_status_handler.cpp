#include "send_system_status_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDebug>

// Internal
#include "uav_model.h"
#include "mavlink_communicator.h"

using namespace domain;

SendSystemStatusHandler::SendSystemStatusHandler(MavLinkCommunicator* communicator,
                                                 UavModel* model):
    AbstractHandler(communicator),
    m_model(model)
{
    this->startTimer(150); // 1 Hz
}

void SendSystemStatusHandler::processMessage(const mavlink_message_t& message)
{
    Q_UNUSED(message)
}

void SendSystemStatusHandler::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event)

    mavlink_message_t message;
    mavlink_sys_status_t status;

    static int battery = 100;
    status.battery_remaining = battery;

    battery = battery > 1 ? battery - 1: 100;

    mavlink_msg_sys_status_encode(m_communicator->systemId(),
                                  m_communicator->componentId(),
                                  &message, &status);

    m_communicator->sendMessageOnLastReceivedLink(message);
}
