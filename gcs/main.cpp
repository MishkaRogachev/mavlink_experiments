// Qt
#include <QCoreApplication>

// Internal
#include "udp_link.h"
#include "serial_link.h"

#include "gcs_communicator_factory.h"
#include "mavlink_communicator.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    domain::GcsCommunicatorFactory factory;
    domain::MavLinkCommunicator* communicator = factory.create();
    communicator->setParent(&app);

    domain::UdpLink link(14550, QString("127.0.0.1"), 14551);
    //domain::SerialLink link("/dev/ttyUSB0", 57600);
    communicator->addLink(&link, MAVLINK_COMM_0);
    link.up();

    return app.exec();
}
