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
    if (message.msgid != MAVLINK_MSG_ID_COMMAND_LONG) return;

    mavlink_command_long_t command;
    mavlink_msg_command_long_decode(&message, &command);

    if (command.target_system == m_communicator->systemId() &&
        (command.target_component == m_communicator->componentId() ||
         command.target_component == MAV_COMP_ID_ALL))
    {
        if (command.command == MAV_CMD_GET_HOME_POSITION)
            this->sendHomePosition();
    }
}

void SendHomePositionHandler::sendHomePosition()
{
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
