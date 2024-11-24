//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef REPUTATIONRSU_H_
#define REPUTATIONRSU_H_

#include "veins/modules/application/traci/TraCIDemoRSU11p.h"

namespace veins {

    class VEINS_API ReputationRSU: public TraCIDemoRSU11p {
    protected:
        void onWSM(BaseFrame1609_4* wsm) override;
    };

}

#endif /* REPUTATIONRSU_H_ */
