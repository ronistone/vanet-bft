#pragma once

#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"
#include "ReputationMessage_m.h"
#include <map>
#include <vector>

namespace veins {

class VEINS_API ReputationCar : public DemoBaseApplLayer {
public:
    void initialize(int stage) override;
    void finish() override;

private:
    std::map<unsigned long, std::vector<Block>*> nextBlock;
    std::vector<Block> blockChain;


protected:
    simtime_t lastDroveAt;
    bool sentMessage;
    int currentSubscribedServiceId;
    uint32_t receivedRm;
    uint32_t chainSize;

protected:
    void onRM(ReputationMessage* msg);
    void sendReputationMessage(Block* block, simtime_t delay);
    const Block* reachConsensus(std::vector<Block>* votes);
    Block* createBlock(Block* example, int peerToChange, int vote);
    unsigned long calculateHash(Block block);

    void onWSM(BaseFrame1609_4* wsm) override;
    void onWSA(DemoServiceAdvertisment* wsa) override;

    void handleSelfMsg(cMessage* msg) override;
    void handlePositionUpdate(cObject* obj) override;
    void handleLowerMsg(cMessage* msg) override;
};
}
