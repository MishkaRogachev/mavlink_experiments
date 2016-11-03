#include "send_vfr_hud_handler.h"

// MAVLink
#include <mavlink.h>

// Internal
#include "uav_model.h"
#include "mavlink_communicator.h"

using namespace domain;

SendVfrHudHandler::SendVfrHudHandler(MavLinkCommunicator* communicator,
                                     UavModel* model):
    AbstractHandler(communicator),
    m_model(model)
{
    this->startTimer(40); // 25 Hz
}

void SendVfrHudHandler::processMessage(const mavlink_message_t& message)
{
    Q_UNUSED(message)
}

void SendVfrHudHandler::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event)

    mavlink_message_t message;
    mavlink_vfr_hud_t hud;

    hud.airspeed = m_model->airspeed(); // TODO: wind
    hud.groundspeed = m_model->groundspeed();
    hud.climb = m_model->climb();
    hud.alt = m_model->position().altitude();
    hud.heading = m_model->yaw();

    mavlink_msg_vfr_hud_encode(m_communicator->systemId(),
                               m_communicator->componentId(),
                               &message, &hud);

    m_communicator->sendMessageOnLastReceivedLink(message);
}
