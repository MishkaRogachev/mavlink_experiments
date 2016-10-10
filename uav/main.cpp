// MAVLink
#include <mavlink.h>

// Qt
#include <QCoreApplication>

// Internal
#include "udp_link.h"

#include "mavlink_communicator.h"

#include "heartbeat_handler.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    domain::MavLinkCommunicator communicator;

    domain::HeartbeatHandler heartbeatHandler(MAV_TYPE_FIXED_WING, 1, 0);
    QObject::connect(&communicator, &domain::MavLinkCommunicator::messageReceived,
                     &heartbeatHandler, &domain::HeartbeatHandler::processMessage);
    QObject::connect(&heartbeatHandler, &domain::HeartbeatHandler::sendMessage,
                     &communicator, &domain::MavLinkCommunicator::sendMessageOnAllLinks);

    domain::UdpLink link(14551, QString("127.0.0.1"), 14550);
    communicator.addLink(&link, MAVLINK_COMM_0);
    link.up();

    return app.exec();
}
