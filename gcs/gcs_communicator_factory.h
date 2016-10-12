#ifndef GCS_COMMUNICATOR_FACTORY_H
#define GCS_COMMUNICATOR_FACTORY_H

#include "abstract_communicator_factory.h"

namespace domain
{
    class GcsCommunicatorFactory: public AbstractCommunicatorFactory
    {
    public:
        GcsCommunicatorFactory();

        MavLinkCommunicator* create() override;
    };
}

#endif // GCS_COMMUNICATOR_FACTORY_H
