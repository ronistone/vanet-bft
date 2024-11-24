
# VANET Blockchain Consensus Simulation

This project simulates a consensus-driven blockchain system for a Vehicular Ad Hoc Network (VANET), where each car node maintains a blockchain representing voting scores. The network reaches consensus on the correct blockchain state despite one Byzantine (malicious) node.

## Project Structure

```
project_directory/
├── blockchain.py           # Defines the Blockchain and Block classes
├── consensus.py            # Implements the voting and scoring consensus logic
├── block_consensus.py      # Implements fault-tolerant consensus for multiple blockchains
├── test.py                 # Test code to simulate VANET consensus with one Byzantine blockchain
└── README.md               # Project overview and usage instructions
```

## File Explanations

- **blockchain.py**: Contains the `Blockchain` and `Block` classes. Each car’s scores are recorded in blocks added to the blockchain.
- **consensus.py**: Defines `consensus_fault_tolerant` to calculate the final voting scores and reach consensus among cars on individual scores.
- **block_consensus.py**: Contains the `consensus_fault_tolerant_block` function, which identifies and selects the most common blockchain among cars in the VANET. This module handles discrepancies from Byzantine nodes.
- **test.py**: The driver code that initializes 5 blockchains, introduces one Byzantine (malicious) blockchain, and uses consensus to reach an agreement on the correct blockchain. This code demonstrates the overall functionality of the system.

## Usage

To run the simulation, ensure that all files are in the same directory, then run `test.py`:

```bash
python test.py
```

This script will:
1. Initialize five blockchain instances representing five cars in the VANET.
2. Introduce one Byzantine (malicious) node with a differing blockchain.
3. Run the `consensus_fault_tolerant_block` function to reach consensus on the correct blockchain.
4. Output the agreed-upon blockchain, ignoring the Byzantine blockchain.

### Example Output

The output will show the agreed-upon blockchain with blocks and their transactions, ensuring consistency across the VANET despite one malicious node.

```plaintext
Agreed Blockchain:
Block 0:
Transactions: ['Genesis Block']
Previous Hash: 0
Hash: <hash>

Block 1:
Transactions: ['Car_1: Initial Score']
Previous Hash: <previous_hash>
Hash: <hash>

...
```

## Requirements

- Python 3.x
- No external libraries are required; this code only uses Python’s standard library.

## How It Works

1. **Voting Consensus** (`consensus_fault_tolerant` in `consensus.py`): Each car in the network votes on scores for other cars. The most common scores are determined through a fault-tolerant algorithm, creating a set of final scores.
2. **Blockchain Consensus** (`consensus_fault_tolerant_block` in `block_consensus.py`): Each car maintains a local copy of the blockchain. This function ensures that, after each voting round, all cars adopt the most common blockchain version, preventing a single Byzantine car from corrupting the network state.
3. **Simulation** (`driver` in `test.py`): Demonstrates how the consensus functions work in practice by simulating a VANET with five cars and one Byzantine car.
