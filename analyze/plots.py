import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from graph_generator import visualize_graph
import networkx as nx
import random

def plot_time_complexity_fast(dfs:list[pd.DataFrame], graph_families:list[str], save=False):
    plt.figure(figsize=(10, 6))
    for i, df in enumerate(dfs):
        #calculate average time for each size
        df = df.groupby('size').mean(numeric_only=True)
        df.reset_index(inplace=True)
        plt.plot(df['size'], df['fastcut_time'], label=graph_families[i], linestyle="-", marker='o')

    # generate x and y values for n^2 log n
    x_values = np.linspace(min(df['size']), max(df['size']), 100)
    y_values = x_values**2 * np.log(x_values)
    plt.plot(x_values, y_values/50, label=r'$\frac{1}{50}n^2 \log{n}$', color='red', linestyle="--")

    plt.xlabel('Number of vertices (n)')
    plt.ylabel('Time (ms)')
    plt.title('FastCut time complexity')
    plt.grid(True)
    plt.legend()
    if save:
        plt.savefig('figs/time_fastcut.png',dpi=200)
    plt.show()

def plot_time_complexity_contract(dfs:list[pd.DataFrame], graph_families:list[str], save=False):
    plt.figure(figsize=(10, 6))
    for i, df in enumerate(dfs):
        #calculate average time for each size
        df = df.groupby('size').mean(numeric_only=True)
        df.reset_index(inplace=True)
        plt.plot(df['size'], df['contract_time'], label=graph_families[i], linestyle="-", marker='o')

    # generate x and y values for n^2
    x_values = np.linspace(min(df['size']), max(df['size']), 100)
    y_values = x_values**2
    plt.plot(x_values, y_values/500, label=r'$\frac{1}{500}n^2$', color='red', linestyle="--")

    plt.xlabel('Number of vertices (n)')
    plt.ylabel('Time (ms)')
    plt.title('Contract time complexity')
    plt.grid(True)
    plt.legend()
    if save:
        plt.savefig('figs/time_contract.png',dpi=200)
    plt.show()

def plot_success_probability_fast(dfs:list[pd.DataFrame], graph_families:list[str], save=False):
    plt.figure(figsize=(10, 6))
    for i, df in enumerate(dfs):
        #calculate average time for each size
        df = df.groupby('size').mean(numeric_only=True)
        df.reset_index(inplace=True)
        plt.plot(df['size'], df['fastcut_success'], label=graph_families[i], linestyle="-", marker='o')

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
        plt.savefig(f'figs/success_prob_fastcut.png',dpi=200)
    plt.show()

def plot_success_probability_contract(dfs:list[pd.DataFrame], graph_families:list[str], save=False):
    plt.figure(figsize=(10, 6))
    for i, df in enumerate(dfs):
        #calculate average time for each size
        df = df.groupby('size').mean(numeric_only=True)
        df.reset_index(inplace=True)
        plt.plot(df['size'], df['contract_success'], label=graph_families[i], linestyle="-", marker='o')

    # generate x and y values for n^2
    x_values = np.linspace(min(df['size']), max(df['size']), 100)
    y_values = 1/x_values**2
    plt.plot(x_values, y_values, label=r'$\frac{1}{n^2}$ ', color='red', linestyle="--")

    plt.xlabel('Number of vertices (n)')
    plt.ylabel('Success probability')
    plt.title(f'Success probability with Contract')
    plt.grid(True)
    plt.legend()
    if save:
        plt.savefig(f'figs/success_prob_contract.png',dpi=200)
    plt.show()

def plot_success_probability_budget_time(dfs:list[pd.DataFrame], graph_families:list[str], save=False):
    for algo in ['fast', 'contract']:
        plt.figure(figsize=(10, 6))
        for i, df in enumerate(dfs):
            #calculate average time for each size
            df = df.groupby(['size', 'algo']).mean(numeric_only=True)
            df.reset_index(inplace=True)
            # Filter to include only rows where algo is 'algo'
            df = df[df['algo'] == algo]
            plt.plot(df['size'], df['success'], label=graph_families[i], linestyle="-", marker='o')

        if algo == 'fast':
            # generate x and y values for 1/log n
            x_values = np.linspace(min(df['size']), max(df['size']), 100)
            y_values = 1/np.log(x_values)
            plt.plot(x_values, y_values, label=r'$\frac{1}{\log{n}}$ ', color='red', linestyle="--")
            
        if algo == 'contract':
            # generate x and y values for 1/n^2
            x_values = np.linspace(min(df['size']), max(df['size']), 100)
            y_values = 1/x_values**2
            plt.plot(x_values, y_values, label=r'$\frac{1}{n^2}$ ', color='red', linestyle="--")

        plt.xlabel('Number of vertices (n)')
        plt.ylabel('Success probability')
        plt.title(f'Success probability with {algo} and t={time_budget} ms')
        plt.grid(True)
        plt.legend()
        if save:
            plt.savefig(f'figs/success_probability_budget_{algo}_{time_budget}.png',dpi=200)
        plt.show()

def plot_graphs(n=10):
    G = nx.barbell_graph(int(n/2), 0)
    visualize_graph(G, "barbell_graph", save=True)
    G2 = nx.watts_strogatz_graph(n, 4, 0.5)
    visualize_graph(G2, "watts_strogatz_graph", save=True)
    G3 = nx.complete_graph(n)
    visualize_graph(G3, "complete_graph", save=True)
    G4 = nx.fast_gnp_random_graph(n, 0.8, seed=42)
    visualize_graph(G4, "random_graph", save=True)
    G5 = nx.fast_gnp_random_graph(n, 0.8, seed=42)
    for (u, v) in G5.edges():
        G5.edges[u, v]['weight'] = random.randint(1, 10)
    visualize_graph(G5, "random_weighted_graph", save=True)
    G6 = nx.barabasi_albert_graph(n, 3)
    visualize_graph(G6, "barabasi_albert_graph", save=True)

if __name__ == '__main__':
    results_filename = ["results/barbell_graph.csv",
                        "results/complete_graph.csv",
                        "results/random_graph.csv",
                        "results/random_weighted_graph.csv",
                        "results/barabasi_albert_graph.csv",
                        "results/watts_strogatz_graph.csv"]
    graph_families = ['Barbell',
                    'Complete',
                    'Erdos Renyi',
                    'Erdos Renyi Weighted',
                    'Barabasi Albert',
                    'Watts Strogatz']
    dataframes = [pd.read_csv(filename) for filename in results_filename]
    save = True

    plot_time_complexity_fast(dataframes, graph_families, save)
    plot_time_complexity_contract(dataframes, graph_families, save)
    plot_success_probability_contract(dataframes, graph_families, save)
    plot_success_probability_fast(dataframes, graph_families, save)
    # plot_graphs(10)

    #part with the budget time
    time_budget = 2000 #in milliseconds
    results_filename = [f"results/barbell_graph_{time_budget}.csv",
                        f"results/complete_graph_{time_budget}.csv",
                        f"results/random_graph_{time_budget}.csv",
                        f"results/random_weighted_graph_{time_budget}.csv",
                        f"results/barabasi_albert_graph_{time_budget}.csv",
                        f"results/watts_strogatz_graph_{time_budget}.csv"]
    dataframes = [pd.read_csv(filename) for filename in results_filename]
    plot_success_probability_budget_time(dataframes, graph_families, save)
    