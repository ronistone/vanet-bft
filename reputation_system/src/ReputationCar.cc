#include "ReputationCar.h"

#include "veins/modules/application/traci/TraCIDemo11pMessage_m.h"

#include <cassert>
#include <utility>
#include <algorithm>

using namespace veins;

Define_Module(veins::ReputationCar);

void ReputationCar::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0) {
        sentMessage = false;
        lastDroveAt = simTime();
        currentSubscribedServiceId = -1;
        blockChain.push_back(*createBlock(NULL, -1, 0));
    }
}

unsigned long ReputationCar::calculateHash(Block block) {
    unsigned long hash = 0;
    for(int repu=0;repu < block.getReputationArraySize(); repu++){
        hash += block.getReputation(repu) * 31;
    }
    hash += block.getLast_hash() * 31;
    return hash;
}

Block* ReputationCar::createBlock(Block* example, int peerToChange, int vote) {
    Block* block;
    size_t reputationSize;
    if(example != NULL) {
        block = new Block(*example);
        block->setLast_hash(example->getHash());
        reputationSize = std::max((int)example->getReputationArraySize(), peerToChange+1);
    } else {
        block = new Block();
        reputationSize = std::max(0, peerToChange+1);
    }

    if(peerToChange >= 0) {
        block->setReputationArraySize(reputationSize);
        block->insertReputation(peerToChange, vote);
    }
    block->setTimestamp(simTime().inUnit(SIMTIME_NS));
    block->setHash(calculateHash(*block));
    return block;
}

void ReputationCar::sendReputationMessage(Block* block, simtime_t delay) {
    ReputationMessage* rm = new ReputationMessage();
    rm->setPeer(0);
    rm->setMessageType(VOTE);

    rm->setBlock(*block);
    rm->setChannelNumber(178); // Channel::cch

    sendDelayedDown(rm, delay);
}

const int QUORUM_MINIMUM = 4;

const Block* ReputationCar::reachConsensus(std::vector<Block>* votes) {
    std::map<unsigned long, int> countVotes;
    std::pair<const Block*, int> mostVoted = std::make_pair((Block*)NULL, -1);
    for(const Block& block: *votes) {
        if(countVotes.find(block.getHash()) == countVotes.end()) {
            countVotes[block.getHash()] = 0;
        }
        countVotes[block.getHash()]++;
        if(mostVoted.second < countVotes[block.getHash()]) {
            mostVoted = std::make_pair(&block, countVotes[block.getHash()]);
        }
    }

    if(mostVoted.first != NULL) {
        std::cout << "Vote to block hash=" << mostVoted.first->getHash() << " with count=" << mostVoted.second << endl;
        if (mostVoted.second >= QUORUM_MINIMUM) {
            return mostVoted.first;
        }
    }
    return NULL;
}

void ReputationCar::onWSA(DemoServiceAdvertisment* wsa)
{
    if (currentSubscribedServiceId == -1) {
        mac->changeServiceChannel(static_cast<Channel>(wsa->getTargetChannel()));
        currentSubscribedServiceId = wsa->getPsid();
        if (currentOfferedServiceId != wsa->getPsid()) {
            stopService();
            startService(static_cast<Channel>(wsa->getTargetChannel()), wsa->getPsid(), "Mirrored Traffic Service");
        }
    }
    sendReputationMessage(createBlock(&blockChain.back(), wsa->getPsid(), 1), 0.5 + uniform(0.1, 0.2));
    std::cout << "Received a WSA" << endl;
    EV << "Received a WSA" << endl;
}

void ReputationCar::onWSM(BaseFrame1609_4* frame)
{
    TraCIDemo11pMessage* wsm = check_and_cast<TraCIDemo11pMessage*>(frame);

    findHost()->getDisplayString().setTagArg("i", 1, "green");

    if (mobility->getRoadId()[0] != ':') traciVehicle->changeRoute(wsm->getDemoData(), 9999);
    if (!sentMessage) {
        sentMessage = true;
        // repeat the received traffic update once in 2 seconds plus some random delay
        wsm->setSenderAddress(myId);
        wsm->setSerial(3);
        scheduleAt(simTime() + 2 + uniform(0.01, 0.2), wsm->dup());
    }
    sendReputationMessage(createBlock(&blockChain.back(), wsm->getPsid(), 1), 0.5 + uniform(0.1, 0.2));
    std::cout << "Received a WSM" << endl;
    EV << "Received a WSM" << endl;
}

void ReputationCar::onRM(ReputationMessage* msg) {

    std::ostringstream oss;

    oss << "Received a Reputation Message"
        << " block->hash=" << msg->getBlock().getHash()
        << " block->last_hash=" << msg->getBlock().getLast_hash()
        << " messageType=" << msg->getMessageType()
        << " my blockchain size=" << blockChain.size() << endl
        << endl;

    std::string log = oss.str();
    std::cout << log;
    EV << log;


    Block blockRcv = msg->getBlock();
    std::vector<Block>* votes;
    switch(msg->getMessageType()) {
    case VOTE:
        if(blockRcv.getLast_hash() != blockChain.back().getHash()) {
            std::cout << "Ignoring block because this broken the chain hash=" << blockRcv.getHash() << " lastHash=" << blockRcv.getLast_hash() << endl;
            EV << "Ignoring block because this broken the chain hash=" << blockRcv.getHash() << " lastHash=" << blockRcv.getLast_hash() << endl;
            return;
        }
        if(nextBlock.find(blockRcv.getLast_hash()) == nextBlock.end()) {
           nextBlock[blockRcv.getLast_hash()] = new std::vector<Block>();
        }
        votes = nextBlock[blockRcv.getLast_hash()];

        if(const Block* decidedBlock = reachConsensus(votes)) {
            blockChain.push_back(*decidedBlock);
        } else {
            votes->push_back(blockRcv);
        }
        break;
    case ASK_REPUTATION:
        sendReputationMessage(&blockChain.back(), 0.5 + uniform(0.1, 0.2));
        break;
    case SEND_REPUTATION:
        break;
    }
}

void ReputationCar::handleLowerMsg(cMessage* msg)
{

    BaseFrame1609_4* wsm = dynamic_cast<BaseFrame1609_4*>(msg);
    ASSERT(wsm);

    if (DemoSafetyMessage* bsm = dynamic_cast<DemoSafetyMessage*>(wsm)) {
        receivedBSMs++;
        onBSM(bsm);
    }
    else if (DemoServiceAdvertisment* wsa = dynamic_cast<DemoServiceAdvertisment*>(wsm)) {
        receivedWSAs++;
        onWSA(wsa);
    } else if (ReputationMessage* rm = dynamic_cast<ReputationMessage*>(wsm)) {
        receivedRm++;
        onRM(rm);
    }
    else {
        receivedWSMs++;
        onWSM(wsm);
    }

    delete (msg);
}


void ReputationCar::handleSelfMsg(cMessage* msg)
{
    if (TraCIDemo11pMessage* wsm = dynamic_cast<TraCIDemo11pMessage*>(msg)) {
        // send this message on the service channel until the counter is 3 or higher.
        // this code only runs when channel switching is enabled
        EV << "Receive Message with serial " << wsm->getSerial() << endl;
        sendReputationMessage(createBlock(&blockChain.back(), wsm->getPsid(), 1), 0.5 + uniform(0.1, 0.2));
        sendDown(wsm->dup());
        wsm->setSerial(wsm->getSerial() + 1);
        if (wsm->getSerial() >= 3) {
            // stop service advertisements
            stopService();
            delete (wsm);
        }
        else {
            scheduleAt(simTime() + 1, wsm);
        }
    } else if(DemoSafetyMessage* dsm = dynamic_cast<DemoSafetyMessage*>(msg)) {
        const Coord& coord = dsm->getSenderPos();
        EV << "Receive Message with position X=" << coord.x << " Y=" << coord.y << " Z=" << coord.z << endl;
     }
    else {
        DemoBaseApplLayer::handleSelfMsg(msg);
    }


}

void ReputationCar::handlePositionUpdate(cObject* obj)
{
    DemoBaseApplLayer::handlePositionUpdate(obj);

    // stopped for for at least 10s?
    if (mobility->getSpeed() < 1) {
        if (simTime() - lastDroveAt >= 10 && sentMessage == false) {
            findHost()->getDisplayString().setTagArg("i", 1, "red");
            sentMessage = true;

            TraCIDemo11pMessage* wsm = new TraCIDemo11pMessage();
            populateWSM(wsm);
            wsm->setDemoData(mobility->getRoadId().c_str());

            // host is standing still due to crash
            if (dataOnSch) {
                startService(Channel::sch2, 42, "Traffic Information Service");
                // started service and server advertising, schedule message to self to send later
                scheduleAt(computeAsynchronousSendingTime(1, ChannelType::service), wsm);
            }
            else {
                // send right away on CCH, because channel switching is disabled
                sendDown(wsm);
            }
        }
    }
    else {
        lastDroveAt = simTime();
    }
}
