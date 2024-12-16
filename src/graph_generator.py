import networkx as nx
import matplotlib.pyplot as plt
import numpy as np

def visualize_graph(G):
    """
    Simple vizualisation of the graph with Networkx
    """
    pos = nx.spring_layout(G)
    nx.draw(G, pos, with_labels=True)
    labels = nx.get_edge_attributes(G, 'weight')
    nx.draw_networkx_edge_labels(G, pos, edge_labels=labels)
    plt.show()

def save_graph_as_matrix(G, file_name: str):
    """
    Function to save the graph in the adjacency matrix format
    """
    adj_matrix = nx.to_numpy_array(G)
    min_cut_value, subsets = calculate_mincut(G)
    with open(f"graph_data/{file_name}_matrix.txt", 'w') as f:
        f.write(f"mincut: {min_cut_value}\n")
        f.write(f"subsetCut1: {' '.join(map(str, subsets[0]))}\n")
        f.write(f"subsetCut2: {' '.join(map(str, subsets[1]))}\n")
        np.savetxt(f, adj_matrix, fmt='%d')
    print(f"Graph saved to graph_data/{file_name}_adjmatrix.txt")

def calculate_mincut(G):
    """
    Function to calculate the mincut of the graph
    """
    min_cut = nx.stoer_wagner(G)
    return min_cut

def plot_all_graphs():
    visualize_graph(G)
    visualize_graph(G2)
    visualize_graph(G3)
    visualize_graph(G4)

G = nx.barbell_graph(15, 0)
save_graph_as_matrix(G, "barbell_graph")

G2 = nx.turan_graph(15, 3)
save_graph_as_matrix(G2, "turan_graph")

G3 = nx.complete_graph(15)
save_graph_as_matrix(G3, "complete_graph")

G4 = nx.fast_gnp_random_graph(15, 0.8)
save_graph_as_matrix(G4, "random_graph")

plot_all_graphs()
