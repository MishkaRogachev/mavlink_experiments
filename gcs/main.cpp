// MAVLink
#include <mavlink.h>

// Qt
#include <QCoreApplication>

// Internal
#include "udp_link.h"
#include "serial_link.h"

#include "mavlink_communicator.h"

#include "heartbeat_handler.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    // Для GCS 255 является стандартным sysid
    domain::MavLinkCommunicator communicator;

    domain::HeartbeatHandler heartbeatHandler(MAV_TYPE_GCS, 255, 0);
    QObject::connect(&communicator, &domain::MavLinkCommunicator::messageReceived,
                     &heartbeatHandler, &domain::HeartbeatHandler::processMessage);
    // heartbeat отправляем на все доступные каналы связи
    QObject::connect(&heartbeatHandler, &domain::HeartbeatHandler::sendMessage,
                     &communicator, &domain::MavLinkCommunicator::sendMessageOnAllLinks);

    // Настройки UDP через localhost
    domain::UdpLink link(14550, QString("127.0.0.1"), 14551);
    //domain::SerialLink link("/dev/ttyUSB0", 57600);
    communicator.addLink(&link, MAVLINK_COMM_0);
    link.up();

    return app.exec();
}
