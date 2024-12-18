import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from graph_generator import visualize_graph
import networkx as nx
import random

def plot_time_complexity(dfs:list[pd.DataFrame], graph_families:list[str], save=False):
    for i, df in enumerate(dfs):
        #calculate average time for each size
        df = df.groupby('size').mean(numeric_only=True)
        df.reset_index(inplace=True)
        plt.plot(df['size'], df['fastcut_time'], label=graph_families[i])

    # generate x and y values for n^2 log n
    x_values = np.linspace(min(df['size']), max(df['size']), 100)
    y_values = x_values**2 * np.log(x_values)
    plt.plot(x_values, y_values/100, label=r'$\frac{1}{100}n^2 \log{n}$', color='red', linestyle="--")

    plt.xlabel('Number of vertices (n)')
    plt.ylabel('Time (ms)')
    plt.title('FastCut Time complexity')
    plt.grid(True)
    plt.legend()
    if save:
        plt.savefig('figs/time_complexity_fastcut.png',dpi=200)
    plt.show()

def plot_success_probability_fast(dfs:list[pd.DataFrame], graph_families:list[str], save=False):
    for i, df in enumerate(dfs):
        #calculate average time for each size
        df = df.groupby('size').mean(numeric_only=True)
        df.reset_index(inplace=True)
        plt.plot(df['size'], df['fastcut_success'], label=graph_families[i])

    # generate x and y values for 1/log n
    x_values = np.linspace(min(df['size']), max(df['size']), 100)
    y_values = 1/np.log(x_values)
    plt.plot(x_values, y_values, label=r'$\frac{1}{\log{n}}$ ', color='red', linestyle="--")

    plt.xlabel('Number of vertices (n)')
    plt.ylabel('Success probability')
    plt.title(f'Success probability with FastCut')
    plt.grid(True)
    plt.legend()
    if save:
        plt.savefig(f'figs/success_probability_fastcut.png',dpi=200)
    plt.show()

def plot_success_probability_contract(dfs:list[pd.DataFrame], graph_families:list[str], save=False):
    for i, df in enumerate(dfs):
        #calculate average time for each size
        df = df.groupby('size').mean(numeric_only=True)
        df.reset_index(inplace=True)
        plt.plot(df['size'], df['contract_success'], label=graph_families[i])

    # generate x and y values for n^2
    x_values = np.linspace(min(df['size']), max(df['size']), 100)
    y_values = 1/x_values**2
    plt.plot(x_values, y_values, label=r'$\frac{1}{n^2}$ ', color='black', linestyle="--")

    plt.xlabel('Number of vertices (n)')
    plt.ylabel('Success probability')
    plt.title(f'Success probability with Contract')
    plt.grid(True)
    plt.legend()
    if save:
        plt.savefig(f'figs/success_probability_contract.png',dpi=200)
    plt.show()

def plot_success_probability_budget_time(df:pd.DataFrame, graph_family:str, save=False):
    #TODO: make a plot for all success probabilities of all graphs for fastcut then another plot for contract
    df = df.groupby('size').mean(numeric_only=True)
    df.reset_index(inplace=True)

    # generate x and y values for 1/log n
    x_values = np.linspace(min(df['size']), max(df['size']), 100)
    y_values = 1/np.log(x_values)
    x2_values = x_values
    y2_values = 1/x2_values**2

    # plot the time complexity
    plt.plot(df['size'], df['fastcut_success'], label="Fastcut")
    plt.plot(df['size'], df['contract_success'], label="Contract")
    plt.plot(x_values, y_values, label=r'$\frac{1}{\log{n}}$ ', color='red', linestyle="--")
    plt.plot(x2_values, y2_values, label=r'$\frac{1}{n^2}$ ', color='black', linestyle="--")

    plt.xlabel('Number of vertices (n)')
    plt.ylabel('Success probability')
    plt.title(f'Success probability on {graph_family}')
    plt.grid(True)
    plt.legend()
    if save:
        plt.savefig(f'figs/success_probability_{graph_family.replace(" ","_")}.png',dpi=200)
    plt.show()

def plot_graphs(n=10):
    G = nx.barbell_graph(int(n/2), 0)
    visualize_graph(G, "barbell_graph", save=True)
    G3 = nx.complete_graph(n)
    visualize_graph(G3, "complete_graph", save=True)
    G4 = nx.fast_gnp_random_graph(n, 0.8, seed=42)
    visualize_graph(G4, "random_graph", save=True)
    G5 = nx.fast_gnp_random_graph(n, 0.8, seed=42)
    for (u, v) in G5.edges():
        G5.edges[u, v]['weight'] = random.randint(1, 10)
    visualize_graph(G5, "random_weighted_graph", save=True)

if __name__ == '__main__':
    results_filename = ["results/barbell_graph.csv", "results/complete_graph.csv", "results/random_graph.csv", "results/random_weighted_graph.csv"]
    graph_families = ['Barbell', 'Complete', 'Random', 'Random Weighted']
    dataframes = [pd.read_csv(filename) for filename in results_filename]
    save = True

    plot_time_complexity(dataframes, graph_families, save)
    plot_success_probability_contract(dataframes, graph_families, save)
    plot_success_probability_fast(dataframes, graph_families, save)
    # plot_graphs(10)

    #part with the budget time
    
