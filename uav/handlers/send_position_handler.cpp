#include "send_position_handler.h"

// MAVLink
#include <mavlink.h>

// Internal
#include "uav_model.h"
#include "mavlink_communicator.h"

using namespace domain;

SendPositionHandler::SendPositionHandler(MavLinkCommunicator* communicator,
                                         UavModel* model):
    AbstractHandler(communicator),
    m_model(model)
{
    this->startTimer(100); // 10 Hz
}

void SendPositionHandler::processMessage(const mavlink_message_t& message)
{
    Q_UNUSED(message)
}

void SendPositionHandler::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event)

    mavlink_message_t message;
    mavlink_global_position_int_cov_t position;

    QGeoCoordinate coordinate = m_model->position();
    position.lat = coordinate.latitude() * 1e7;
    position.lon = coordinate.longitude() * 1e7;
    position.alt = coordinate.altitude() * 1000;

    mavlink_msg_global_position_int_cov_encode(m_communicator->systemId(),
                                               m_communicator->componentId(),
                                               &message, &position);

    m_communicator->sendMessageOnLastReceivedLink(message);
}
