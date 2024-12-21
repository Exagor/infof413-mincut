import csv

def create_csv_file(file_name, column_names):
    with open(file_name, mode='w', newline='\n') as file:
        writer = csv.writer(file)
        writer.writerow(column_names)

# init test with fixed iteration
file_names = ["random_graph",
            "random_weighted_graph",
            "barbell_graph",
            "complete_graph",
            "barabasi_albert_graph",
            "watts_strogatz_graph"]
column_names = ['family','size','mincut','contract','fastcut','contract_time','fastcut_time','contract_success','fastcut_success']
for name in file_names:
    create_csv_file(f"results/{name}.csv", column_names)

# init test with fixed time budget
time_budgets = [500, 1000, 2000]
column_names = ['family','size','algo','mincut','time','success']
for budget in time_budgets:
    for name in file_names:
        create_csv_file(f"results/{name}_{budget}.csv", column_names)