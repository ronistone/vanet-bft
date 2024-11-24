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

#include "ReputationRSU.h"
#include "ReputationMessage_m.h"

using namespace veins;

Define_Module(veins::ReputationRSU);

void ReputationRSU::onWSM(BaseFrame1609_4* frame)
{
    // this rsu repeats the received traffic update in 2 seconds plus some random delay
    sendDelayedDown(frame->dup(), 2 + uniform(0.01, 0.2));
}
