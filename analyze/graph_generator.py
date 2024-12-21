import networkx as nx
import matplotlib.pyplot as plt
import numpy as np
import random

random.seed(42)

def visualize_graph(G, name=" ", save=False):
    """
    Simple vizualisation of the graph with Networkx
    """
    pos = nx.spring_layout(G)
    nx.draw(G, pos, with_labels=True)
    labels = nx.get_edge_attributes(G, 'weight')
    nx.draw_networkx_edge_labels(G, pos, edge_labels=labels)
    if save:
        plt.savefig(f'figs/{name}_{G.number_of_nodes()}.png',dpi=200)
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
    print(f"Graph saved to graph_data/{file_name}.txt")

def calculate_mincut(G):
    """
    Function to calculate the mincut of the graph
    """
    min_cut = nx.stoer_wagner(G)
    return min_cut

def generate_graphs_size_n(n=20, plot=False):
    """
    Function to generate graphs of size n
    """

    G = nx.barbell_graph(int(n/2), 0)
    save_graph_as_matrix(G, f"barbell_graph_{n}")
    G2 = nx.watts_strogatz_graph(n, 4, 0.4)
    save_graph_as_matrix(G2, f"watts_strogatz_graph_{n}")
    G3 = nx.complete_graph(n)
    save_graph_as_matrix(G3, f"complete_graph_{n}")
    G4 = nx.fast_gnp_random_graph(n, 0.8, seed=42)
    save_graph_as_matrix(G4, f"random_graph_{n}")
    G5 = nx.fast_gnp_random_graph(n, 0.8, seed=42)
    for (u, v) in G5.edges():
        G5.edges[u, v]['weight'] = random.randint(1, 10)
    save_graph_as_matrix(G5, f"random_weighted_graph_{n}")
    G6 = nx.barabasi_albert_graph(n, 3)
    save_graph_as_matrix(G6, f"barabasi_albert_graph_{n}")

    def plot_all_graphs():
        visualize_graph(G)
        visualize_graph(G2)
        visualize_graph(G3)
        visualize_graph(G4)
        visualize_graph(G5)
        visualize_graph(G6)
    if plot:
        plot_all_graphs()

if __name__ == "__main__":
    sizes = [size for size in range(10, 251, 10)]
    for size in sizes:
        generate_graphs_size_n(size, plot=False)
