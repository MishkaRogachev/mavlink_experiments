#include "uav_communicator_factory.h"

// MAVLink
#include <mavlink.h>

// Internal
#include "mavlink_communicator.h"

#include "heartbeat_handler.h"
#include "send_position_handler.h"

using namespace domain;

UavCommunicatorFactory::UavCommunicatorFactory(domain::UavModel* model):
    m_model(model)
{}

MavLinkCommunicator* UavCommunicatorFactory::create()
{
    MavLinkCommunicator* communicator = new MavLinkCommunicator(1, 0);

    new domain::HeartbeatHandler(MAV_TYPE_FIXED_WING, communicator);
    new domain::SendPositionHandler(communicator, m_model);

    return communicator;
}
