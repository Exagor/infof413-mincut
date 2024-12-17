import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

def plot_time_complexity(dfs:list[pd.DataFrame], graph_families:list[str], save=False):
    for i, df in enumerate(dfs):
        #calculate average time for each size
        df = df.groupby('size').mean(numeric_only=True)
        df.reset_index(inplace=True)
        plt.plot(df['size'], df['fastcut_time'], label=graph_families[i])

    # generate x and y values for n^2 log n
    x_values = np.linspace(min(df['size']), max(df['size']), 500)
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

def plot_sucess_probability(df:pd.DataFrame, graph_family:str, save=False):
    df = df.groupby('size').mean(numeric_only=True)
    df.reset_index(inplace=True)

    # generate x and y values for 1/log n
    x_values = np.linspace(min(df['size']), max(df['size']), 500)
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


results_filename = ["results/barbell_graph.csv", "results/complete_graph.csv", "results/random_graph.csv", "results/random_weighted_graph.csv"]
graph_families = ['Barbell', 'Complete', 'Random', 'Random Weighted']
dataframes = [pd.read_csv(filename) for filename in results_filename]
save = True

plot_time_complexity(dataframes, graph_families,save)

plot_sucess_probability(dataframes[0], 'barbell graph', save)
plot_sucess_probability(dataframes[1], 'complete graph', save)
plot_sucess_probability(dataframes[2], 'random graph', save)
plot_sucess_probability(dataframes[3], 'random weighted graph', save)
