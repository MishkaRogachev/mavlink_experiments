#include "send_gps_raw_handler.h"

// MAVLink
#include <mavlink.h>

// Internal
#include "uav_model.h"
#include "mavlink_communicator.h"

#include "mavlink_protocol_helpers.h"

using namespace domain;

SendGpsRawHandler::SendGpsRawHandler(MavLinkCommunicator* communicator,
                                     UavModel* model):
    AbstractHandler(communicator),
    m_model(model)
{
    this->startTimer(2000); // 0.5 Hz
}

void SendGpsRawHandler::processMessage(const mavlink_message_t& message)
{
    Q_UNUSED(message)
}

void SendGpsRawHandler::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event)

    mavlink_message_t message;
    mavlink_gps_raw_int_t gps;

    gps.fix_type = rand() % 4;
    gps.satellites_visible = rand() % 16;

    QGeoCoordinate coordinate = m_model->position();
    gps.lat = encodeLatLon(coordinate.latitude());
    gps.lon = encodeLatLon(coordinate.longitude());
    gps.alt = encodeAltitude(coordinate.altitude());

    mavlink_msg_gps_raw_int_encode(m_communicator->systemId(),
                                   m_communicator->componentId(),
                                   &message, &gps);

    m_communicator->sendMessageOnLastReceivedLink(message);
}
