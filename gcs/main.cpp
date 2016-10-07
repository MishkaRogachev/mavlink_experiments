// Qt
#include <QCoreApplication>

// Internal
#include "udp_link.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    domain::UdpLink link(50001, QString("127.0.0.1"), 50002);
    link.up();

    return app.exec();
}
