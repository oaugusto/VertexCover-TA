import networkx as nx
from networkx.generators.trees import random_tree
from networkx.generators.random_graphs import random_powerlaw_tree
from networkx.generators.classic import full_rary_tree
import matplotlib.pyplot as plt
import sys

num_nodes = int(sys.argv[1])

# g = random_powerlaw_tree(num_nodes)
g = random_tree(num_nodes)
# g = full_rary_tree(20,num_nodes)

print(num_nodes, g.number_of_edges())
for node1, node2, data in g.edges(data=True):
    print(node1, node2)

# da plot no grafo
# pos=nx.spring_layout(g)
# labels = nx.get_edge_attributes(g,'weight')
# nx.draw(g, with_labels=True)
# plt.show()