import optparse
import os
import sys

if 'SUMO_HOME' in os.environ:
    tools = os.path.join(os.environ['SUMO_HOME'], 'tools')
    sys.path.append(tools)

import traci
import traci.constants as tc

import random


class ReputationSystem:

    def __init__(self):
        self.nodes = {}

    def add_node(self, node_id):
        self.nodes[node_id] = 0

    def update_reputation(self, node_id, v):
        self.nodes[node_id] += v

    def get_reputation(self, node_id):
        return self.nodes[node_id]


vote_possibility = [-1, 0, 0, 0, 1, 1]


class Node:

    def __init__(self, node_id, rs):
        self.node_id = node_id
        self.reputation_system = rs
        self.reputation_system.add_node(node_id)

    def receive_message_info(self, from_id, message):
        vote_position = (
                            random.randint(0, 100) +
                            self.reputation_system.get_reputation(from_id) +
                            message
                    ) % len(vote_possibility)
        return from_id, vote_possibility[vote_position]


key_mapping = {
    tc.VAR_ROAD_ID: "ROAD_ID",
    tc.VAR_LANEPOSITION: "LANEPOSITION",
    tc.VAR_POSITION: "POSITION",
    tc.VAR_SPEED: "SPEED"
}


def convert_info_values(vehicle_info):
    for old_key, new_key in key_mapping.items():
        if old_key in vehicle_info:
            vehicle_info[new_key] = vehicle_info[old_key]
            del vehicle_info[old_key]
    return vehicle_info


def get_options():
    opt = optparse.OptionParser()
    opt.add_option("--nogui", action="store_true",
                         default=False, help="run the commandline version of sumo")
    options, _ = opt.parse_args()
    return options


# this is the main entry point of this script
if __name__ == "__main__":
    options = get_options()
    if options.nogui:
        sumoBinary = 'sumo'
    else:
        sumoBinary = 'sumo-gui'

    simulation_config_path = "./data/second.sumocfg"

    traci.start([sumoBinary, "-c", simulation_config_path])
    vehicles = {}
    step_num = 0
    reputation_system = ReputationSystem()
    while traci.simulation.getMinExpectedNumber() > 0:

        traci.simulationStep()
        step_num += 1
        print("\n\nstep", step_num)

        vehiclesIDs = traci.vehicle.getIDList()
        if len(vehiclesIDs) == 0:
            continue
        vehicle_to_send = random.choice(vehiclesIDs)
        votes = []
        for vehicle in vehiclesIDs:
            if vehicle not in vehicles:
                vehicles[vehicle] = Node(vehicle, reputation_system)
                traci.vehicle.subscribe(vehicle, (tc.VAR_ROAD_ID, tc.VAR_LANEPOSITION, tc.VAR_POSITION, tc.VAR_SPEED))
            print("\tVehicle %s:" % vehicle, convert_info_values(traci.vehicle.getSubscriptionResults(vehicle)))
        for vehicle in vehiclesIDs:
            if vehicle != vehicle_to_send:
                votes.append(vehicles[vehicle].receive_message_info(vehicle_to_send, random.randint(0, 100)))

        if len(votes) == 0:
            continue
        votes_count = {-1: 0, 0: 0, 1: 0}
        for vote in votes:
            print("Vote from %s: %s" % (vote[0], vote[1]))
            votes_count[vote[1]] += 1
        most_voted = max(votes_count, key=votes_count.get)
        reputation_system.update_reputation(vehicle_to_send, most_voted)

    print("Simulation finished")
    print("Reputation System:", reputation_system.nodes)

    traci.close()
