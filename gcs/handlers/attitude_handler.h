#ifndef ATTITUDE_HANDLER_H
#define ATTITUDE_HANDLER_H

#include "abstract_handler.h"

namespace domain
{
    class AttitudeHandler: public AbstractHandler
    {
        Q_OBJECT

    public:
        AttitudeHandler(MavLinkCommunicator* communicator);

    public slots:
        void processMessage(const mavlink_message_t& message) override;
    };
}

#endif // ATTITUDE_HANDLER_H
