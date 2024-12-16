import networkx as nx
import matplotlib.pyplot as plt

def visualize_graph(G):
    """
    Simple vizualisation of the graph with Networkx
    """
    pos = nx.spring_layout(G)
    nx.draw(G, pos, with_labels=True)
    labels = nx.get_edge_attributes(G, 'weight')
    nx.draw_networkx_edge_labels(G, pos, edge_labels=labels)
    plt.show()

def save_graph(G, file_name:str):
    """
    Function to save the graph in the adjlist format and remove the comments
    """
    nx.write_adjlist(G, f"graph_data/{file_name}.adjlist", comments='')
    with open(f"graph_data/{file_name}.adjlist", 'r') as f:
        lines = f.readlines()
    with open(f"graph_data/{file_name}.adjlist", 'w') as f:
        f.writelines(lines[3:])
    print(f"Graph saved to graph_data/{file_name}.adjlist")

def calculate_mincut(G):
    """
    Function to calculate the mincut of the graph
    """
    min_cut = nx.stoer_wagner(G)
    print(f"Value of the min cut of the graph: {min_cut[0]}")
    print(f"Sets of the min cut: {min_cut[1]}")
    return min_cut

def plot_all_graphs():
    visualize_graph(G)
    visualize_graph(G2)
    visualize_graph(G3)

G = nx.barbell_graph(5, 0)
save_graph(G, "barbell_graph")
calculate_mincut(G)

G2 = nx.turan_graph(10, 3)
save_graph(G2, "turan_graph")
calculate_mincut(G2)

G3 = nx.karate_club_graph()
save_graph(G3, "karate_club_graph")
calculate_mincut(G3)

# plot_all_graphs()
