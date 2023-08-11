# Simple Merkle Tree implementation that stores all nodes.
#
#  h=3                 root                d = 0
#                  __/      \__            
#  h=2          X               +          d = 1
#             /   \           /   \       
#  h=1      +       +       +       X      d = 2
#          / \     / \     / \     / \     
#  h=0    +   +   +   +   X   +   +   +    d = 3
#         0   1   2   3   4   5   6   7    
#                                    
# Fig 1: Merkle tree of height h and depth d.
#        + and X are hashes. X are used to prove 5.    

import hashlib, math


def sha256(data):
    return hashlib.sha256(data).digest()


def is_valid_proof(root, leaf, leaf_idx, proof):
    next = leaf
    for sibling in proof:
        next = sha256(sibling + next) if leaf_idx % 2 else sha256(next + sibling)
        leaf_idx //= 2
    return next == root


class MerkleTree:
    def __init__(self, leaf_contents):
        self.leaves = [sha256(content) for content in leaf_contents]
        self.height = math.ceil(math.log2(len(self.leaves)))
        self.tree = self._build_tree()
        self.root = self.tree[-1][0]


    def _build_tree(self):
        tree = [self.leaves.copy()]

        for lvl in range(self.height):
            new_lvl = []
            for i in range(0, len(tree[lvl]), 2):
                left = tree[lvl][i]
                right = tree[lvl][i + 1] if i + 1 < len(tree[lvl]) else b""
                new_lvl.append(sha256(left + right))
            tree.append(new_lvl)

        return tree


    def inclusion_proof(self, leaf_idx):
        proof = []
        idx = leaf_idx
        for lvl in range(0, self.height):
            idx = idx + 1 if idx % 2 == 0 else idx - 1
            proof.append(self.tree[lvl][idx])
            idx //= 2
        return proof
    

    def __str__(self) -> str:
        return "MT<h={}, L={}, root=0x{}..> Layers:\n{}".format(
            self.height, len(self.leaves), self.root.hex()[:6], 
            '\n'.join([str(["{}:".format(i)+y.hex()[:6] for i,y in enumerate(x)]) 
                       for x in self.tree[::-1]]))
