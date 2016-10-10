#ifndef HEARTBEAT_HANDLER_H
#define HEARTBEAT_HANDLER_H

#include "abstract_handler.h"

namespace domain
{
    class HeartbeatHandler: public AbstractHandler
    {
        Q_OBJECT

    public:
        HeartbeatHandler(uint8_t type, uint8_t systemId,
                         uint8_t componentId, QObject* parent = nullptr);

    protected:
        void timerEvent(QTimerEvent *event) override;

    public slots:
        void processMessage(const mavlink_message_t& message) override;

    private:
        const uint8_t m_type;
        const uint8_t m_systemId;
        const uint8_t m_componentId;
    };
}

#endif // HEARTBEAT_HANDLER_H
