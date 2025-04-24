import pulp
import sys
import time

def solve_transportation_problemlem(capacity, segments, requests):

    problem = pulp.LpProblem("Transportation problem", pulp.LpMaximize)

    # Decision variables: binary variable for each request
    request_variables = pulp.LpVariable.dicts("Request", range(len(requests)), 0, 1, pulp.LpBinary)

    # Objective function: Maximize total benefit = passengers * (arrival - departure)
    problem += pulp.lpSum([r['passengers'] * (r['arrival_station_index'] - r['departure_station_index']) * request_variables[i] for i, r in enumerate(requests)]), "Total Benefit"

    # Constraints: capacity per segment
    for s in range(segments):
        problem += pulp.lpSum([r['passengers'] * request_variables[i] for i, r in enumerate(requests) if r['departure_station_index'] <= s < r['arrival_station_index']]) <= capacity, f"Segment Capacity {s}"

    problem.solve()

    if pulp.LpStatus[problem.status] == "Optimal":
        best_benefit = pulp.value(problem.objective)
        return best_benefit
    else:
        return None

if __name__ == "__main__":

    if len(sys.argv) != 3:
        print("Uso: python your_script_name.py <pruebas.txt> <resultados.txt>")
        sys.exit(1)

    test_file = sys.argv[1]
    results_file = sys.argv[2]

    try:
        with open(test_file, 'r') as fin, open(results_file, 'w') as fout:
            while True:
                header_line = fin.readline().split()
                if not header_line:
                    break

                capacity = int(header_line[0])
                stations = int(header_line[1])
                orders = int(header_line[2])

                requests = []
                for _ in range(orders):
                    request_line = fin.readline().split()
                    departure = int(request_line[0])
                    arrival = int(request_line[1])
                    passengers = int(request_line[2])
                    requests.append({
                        'departure_station_index': departure,
                        'arrival_station_index': arrival,
                        'passengers': passengers
                    })

                start_time = time.perf_counter()
                max_benefit = solve_transportation_problemlem(capacity, stations, requests)
                end_time = time.perf_counter()

                duration_ms = (end_time - start_time) * 1000

                if max_benefit is not None:
                    fout.write(f"{max_benefit:.0f} {duration_ms:.3f}\n")

    except Exception as e:
        print(f"Ha ocurrido un error: {e}")
        sys.exit(1)
