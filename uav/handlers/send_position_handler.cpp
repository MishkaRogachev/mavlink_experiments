#include "send_position_handler.h"

// MAVLink
#include <mavlink.h>

// Internal
#include "uav_model.h"
#include "mavlink_communicator.h"

#include "mavlink_protocol_helpers.h"

using namespace domain;

SendPositionHandler::SendPositionHandler(MavLinkCommunicator* communicator,
                                         UavModel* model):
    AbstractHandler(communicator),
    m_model(model)
{
    this->startTimer(500); // 2 Hz
}

void SendPositionHandler::processMessage(const mavlink_message_t& message)
{
    Q_UNUSED(message)
}

void SendPositionHandler::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event)

    mavlink_message_t message;
    mavlink_global_position_int_t position;

    QGeoCoordinate coordinate = m_model->position();
    position.lat = encodeLatLon(coordinate.latitude());
    position.lon = encodeLatLon(coordinate.longitude());
    position.alt = encodeAltitude(coordinate.altitude());

    mavlink_msg_global_position_int_encode(m_communicator->systemId(),
                                           m_communicator->componentId(),
                                           &message, &position);

    m_communicator->sendMessageOnLastReceivedLink(message);
}
