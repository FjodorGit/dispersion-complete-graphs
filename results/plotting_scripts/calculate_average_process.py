import numpy as np
import os

# This script calculates the average process from the 1000 files  

data_dir_name = "/home/fjk/Uni/Bachelorarbeit/graph-dispersion/results/average_process/fully_connected/capacity_1/data"

file_count = 0
summed_processes = np.zeros(5001)
for file in os.listdir(data_dir_name):
    if file.endswith(".dat"):
        with open(data_dir_name + "/" + file, "r") as file:
            array = np.array([float(line.strip()) for line in file.readlines()], dtype=float)
            try:
                summed_processes += array
                file_count += 1
            except ValueError:
                print(f"Could not broadcast together of file {file.name}")
                continue

print(f"Average over {file_count} files")
average_process = summed_processes / file_count

output_file = "/home/fjk/Uni/Bachelorarbeit/graph-dispersion/results/average_process/fully_connected/capacity_1/average_process_calculated.dat"
with open(output_file, "w+") as result_file:
    for value in average_process:
        result_file.write(str(value) + "\n")


        
data_dir_name = "/home/fjk/Uni/Bachelorarbeit/graph-dispersion/results/average_process/fully_connected/capacity_2/data"

file_count = 0
summed_processes = np.zeros(5001)
for file in os.listdir(data_dir_name):
    if file.endswith(".dat"):
        with open(data_dir_name + "/" + file, "r") as file:
            array = np.array([float(line.strip()) for line in file.readlines()], dtype=float)
            try:
                summed_processes += array
                file_count += 1
            except ValueError:
                print(f"Could not broadcast together of file {file.name}")
                continue

print(f"Average over {file_count} files")
average_process = summed_processes / file_count

output_file = "/home/fjk/Uni/Bachelorarbeit/graph-dispersion/results/average_process/fully_connected/capacity_2/average_process_calculated.dat"
with open(output_file, "w+") as result_file:
    for value in average_process:
        result_file.write(str(value) + "\n")
