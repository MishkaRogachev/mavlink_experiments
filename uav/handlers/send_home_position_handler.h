#ifndef SEND_HOME_POSITION_HANDLER_H
#define SEND_HOME_POSITION_HANDLER_H

#include "abstract_handler.h"

namespace domain
{
    class UavModel;

    class SendHomePositionHandler: public AbstractHandler
    {
    public:
        SendHomePositionHandler(MavLinkCommunicator* communicator,
                                UavModel* model);

    public slots:
        void processMessage(const mavlink_message_t& message) override;

        void sendHomePosition();

    private:
        UavModel* m_model;
    };
}

#endif // SEND_HOME_POSITION_HANDLER_H
