#ifndef SEND_ATTITUDE_HANDLER_H
#define SEND_ATTITUDE_HANDLER_H

#include "abstract_handler.h"

namespace domain
{
    class UavModel;

    class SendAttitudeHandler: public AbstractHandler
    {
    public:
        SendAttitudeHandler(MavLinkCommunicator* communicator,
                            UavModel* model);

    public slots:
        void processMessage(const mavlink_message_t& message) override;

    protected:
        void timerEvent(QTimerEvent *event) override;

    private:
        UavModel* m_model;
    };
}

#endif // SEND_ATTITUDE_HANDLER_H
