#ifndef GCS_COMMUNICATOR_H
#define GCS_COMMUNICATOR_H

#include "mavlink_communicator.h"

namespace domain
{
    class GcsCommunicator: public MavLinkCommunicator
    {
        Q_OBJECT

    public:
        GcsCommunicator(QObject* parent = nullptr);

    public slots:
        void sendHeartbeat();
    };
}

#endif // GCS_COMMUNICATOR_H
