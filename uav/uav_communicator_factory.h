#ifndef UAV_COMMUNICATOR_FACTORY_H
#define UAV_COMMUNICATOR_FACTORY_H

#include "abstract_communicator_factory.h"

namespace domain
{
    class UavModel;

    class UavCommunicatorFactory: public AbstractCommunicatorFactory
    {
    public:
        UavCommunicatorFactory(domain::UavModel* model);

        MavLinkCommunicator* create() override;

    private:
        domain::UavModel* m_model;
    };
}

#endif // UAV_COMMUNICATOR_FACTORY_H
