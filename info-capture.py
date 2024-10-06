import os
import sys

if 'SUMO_HOME' in os.environ:
    tools = os.path.join(os.environ['SUMO_HOME'], 'tools')
    sys.path.append(tools)

import traci
import traci.constants as tc

simulation_config_path = "./data/second.sumocfg"

traci.start(["sumo-gui", "-c", simulation_config_path])
vehicles = {}
step_num = 0
while traci.simulation.getMinExpectedNumber() > 0:

    traci.simulationStep()
    step_num += 1
    print("step", step_num)

    for vehicle in traci.vehicle.getIDList():
        if vehicle not in vehicles:
            vehicles[vehicle] = True
            traci.vehicle.subscribe(vehicle, (tc.VAR_ROAD_ID, tc.VAR_LANEPOSITION, tc.VAR_POSITION, tc.VAR_SPEED))
        print("Vehicle %s:" % vehicle, traci.vehicle.getSubscriptionResults(vehicle))
traci.close()