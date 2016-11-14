#include "send_home_position_handler.h"

// MAVLink
#include <mavlink.h>

// Internal
#include "uav_model.h"
#include "mavlink_communicator.h"

using namespace domain;

SendHomePositionHandler::SendHomePositionHandler(MavLinkCommunicator* communicator,
                                                 UavModel* model):
    AbstractHandler(communicator),
    m_model(model)
{
    this->startTimer(1000); // 1 Hz
}

void SendHomePositionHandler::processMessage(const mavlink_message_t& message)
{
    Q_UNUSED(message)
}

void SendHomePositionHandler::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event)

    mavlink_message_t message;
    mavlink_home_position_t position;

    QGeoCoordinate coordinate = m_model->homePosition();
    position.latitude = coordinate.latitude() * 1e7;
    position.longitude = coordinate.longitude() * 1e7;
    position.altitude = coordinate.altitude() * 1000;

    mavlink_msg_home_position_encode(m_communicator->systemId(),
                                     m_communicator->componentId(),
                                     &message, &position);

    m_communicator->sendMessageOnLastReceivedLink(message);
}
