import sys
sys.path.append('../')

import emu.mt as mt

# Example usage
leaf_contents = [b"hello", b"world", b"merkle", b"tree", b"with", b"eight", b"leaf", b"nodes"]
mtree = mt.MerkleTree(leaf_contents)
print("Merkle Tree:", mtree)

leaf_idx = 5  # Index of the leaf for which you want the inclusion proof
proof = mtree.inclusion_proof(leaf_idx)
print("Inclusion Proof for index={}: {}".format(leaf_idx, [x.hex()[:6] for x in proof]))

leaf = mtree.leaves[leaf_idx]
print("Proof is", mt.is_valid_proof(mtree.root, leaf, leaf_idx, proof))
