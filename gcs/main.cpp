// Qt
#include <QCoreApplication>

// Internal
#include "udp_link.h"
#include "gcs_communicator.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    domain::GcsCommunicator communicator;

    domain::UdpLink link(50001, QString("127.0.0.1"), 50002);
    communicator.addLink(&link, MAVLINK_COMM_0);
    link.up();

    return app.exec();
}
