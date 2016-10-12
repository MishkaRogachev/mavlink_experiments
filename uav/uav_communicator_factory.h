#ifndef UAV_COMMUNICATOR_FACTORY_H
#define UAV_COMMUNICATOR_FACTORY_H

#include "abstract_communicator_factory.h"

namespace domain
{
    class UavCommunicatorFactory: public AbstractCommunicatorFactory
    {
    public:
        UavCommunicatorFactory();

        MavLinkCommunicator* create() override;
    };
}

#endif // UAV_COMMUNICATOR_FACTORY_H
