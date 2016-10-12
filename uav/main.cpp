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

    domain::MavLinkCommunicator communicator(1, 0);
    domain::HeartbeatHandler heartbeatHandler(MAV_TYPE_FIXED_WING, &communicator);

    domain::UdpLink link(14551, QString("127.0.0.1"), 14550);
    communicator.addLink(&link, MAVLINK_COMM_0);
    link.up();

    return app.exec();
}
