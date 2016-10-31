// Qt
#include <QCoreApplication>

// Internal
#include "udp_link.h"

#include "uav_model.h"
#include "uav_communicator_factory.h"
#include "mavlink_communicator.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    domain::UavModel model;
    domain::UavCommunicatorFactory factory(&model);
    domain::MavLinkCommunicator* communicator = factory.create();
    communicator->setParent(&app);

    domain::UdpLink link(14551, QString("127.0.0.1"), 14550);
    communicator->addLink(&link, MAVLINK_COMM_0);
    link.up();

    return app.exec();
}
