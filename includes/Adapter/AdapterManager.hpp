/**********************************************************************************
* 
* Adapter Manager
* 
* Singleton class responsible of creating and managing
* 
* every adapters detected of the device.
*
* 
/**********************************************************************************/

#pragma once

#include <list>
#include <utility>

#include "Adapter/Adapter.hpp"

#include "Miscs/IObserver.hpp"

class AdapterManager : public IObserver
{
    public:
        // We admit that it cannot exceed 10 adapters
        static constexpr int                    maxAdapterNumber = 10;

        typedef std::pair<Adapter*, Adapter*>   AdapterPair;
        typedef std::list<AdapterPair>          AdapterPairsList;

        /* AObserver */

        virtual void                            update(ISubject *);

        /* !AObserver */

        template<typename T>
        const                                   Adapter *getAdapter(T attribute) const;

        static AdapterManager                   &Instance();

        ~AdapterManager();

    private:
        explicit                                AdapterManager();

        void                                    getBluezMGMTPacket();

        void                                    getBluezHCIPacket();

        void                                    getAllAdapters();

        AdapterPairsList                        _adapterPairsList;
};