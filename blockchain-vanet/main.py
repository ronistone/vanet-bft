from blockchain import Blockchain, Block
from block_consensus import consensus_fault_tolerant_block

def create_vanet_blockchains():
    blockchain_dict = {}
    for i in range(5):
        blockchain = Blockchain()

        scores = [f"Car_{i+1}: Initial Score"]
        initial_block = Block(scores=scores)
        blockchain.add_block(initial_block)

        scores = [f"Car_{i+1}: Updated Score"]
        second_block = Block(scores=scores)
        blockchain.add_block(second_block)

        blockchain_dict[i] = blockchain

    byzantine_blockchain = Blockchain()
    scores = [f"Car_6: I'm malicious"]
    initial_block = Block(scores=scores)
    byzantine_blockchain.add_block(initial_block)
    blockchain_dict[4] = byzantine_blockchain  # replace by the byzantine block

    return blockchain_dict

def driver():
    blockchain_dict = create_vanet_blockchains()
    agreed_blockchain = consensus_fault_tolerant_block(blockchain_dict)
    if agreed_blockchain:
        print("Agreed Blockchain:")
        for index, block in enumerate(agreed_blockchain.chain):
            print(f"Block {index}:")
            print(f"Scores: {block.scores}")
            print(f"Previous Hash: {block.previous_hash}")
            print(f"Hash: {block.hash}")
            print("-" * 40)
    else:
        print("No consensus could be reached.")

# Run the driver function
if __name__ == "__main__":
    driver()
