set terminal pdfcairo enhanced color dashed font "Alegreya, 14" rounded size 16 cm, 9.6 cm

set grid
set datafile missing '0'
set key right top
set title 'Process of unhappy particles n=1000000'      # Set the plot title
set ylabel 'Unhappy count'        # Set the x-axis label
set xlabel 'Time'        # Set the y-axis label

# Process of particles on fully_connected graph
set output '../unhappy_process/fully_connected/capacity_1/unhappy_particles_process.pdf'
plot "../unhappy_process/fully_connected/capacity_1/data/unhappy_process_n=1000000_M=500000.dat" ls 1 title "M = 500000" with lines, \
"../unhappy_process/fully_connected/capacity_1/data/unhappy_process_n=1000000_M=495000.dat" ls 2 title "M = 495000" with lines, \
"../unhappy_process/fully_connected/capacity_1/data/unhappy_process_n=1000000_M=501500.dat" ls 3 title "M = 501500" with lines

set yr [0:5000]
set output '../unhappy_process/fully_connected/capacity_1/unhappy_particles_process_zoomed.pdf'
plot "../unhappy_process/fully_connected/capacity_1/data/unhappy_process_n=1000000_M=500000.dat" ls 1 title "M = 500000" with lines, \
"../unhappy_process/fully_connected/capacity_1/data/unhappy_process_n=1000000_M=495000.dat" ls 2 title "M = 495000" w l, \
"../unhappy_process/fully_connected/capacity_1/data/unhappy_process_n=1000000_M=501500.dat" ls 3 title "M = 501500" w l

set title 'Process of unhappy particles n=1000000 and capacity 2' 
set yr [0:1010000]
set output '../unhappy_process/fully_connected/capacity_2/unhappy_particles_process_c2.pdf'
plot "../unhappy_process/fully_connected/capacity_2/data/unhappy_process_n=1000000_M=1000000.dat" w l ls 1 title "M = 1000000", \
"../unhappy_process/fully_connected/capacity_2/data/unhappy_process_n=1000000_M=990000.dat" w l ls 2 title "M = 990000", \
"../unhappy_process/fully_connected/capacity_2/data/unhappy_process_n=1000000_M=1002500.dat" w l ls 3 title "M = 1002500"

set yr [0:6000]
set output '../unhappy_process/fully_connected/capacity_2/unhappy_particles_process_c2_zoomed.pdf'
plot "../unhappy_process/fully_connected/capacity_2/data/unhappy_process_n=1000000_M=1000000.dat" w l ls 1 title "M = 1000000", \
"../unhappy_process/fully_connected/capacity_2/data/unhappy_process_n=1000000_M=990000.dat" w l ls 2 title "M = 990000", \
"../unhappy_process/fully_connected/capacity_2/data/unhappy_process_n=1000000_M=1002500.dat" w l ls 3 title "M = 1002500"

# set title 'Process of unhappy particles circle graph' 
# set yr [0:1000]
# set output '../unhappy_process/circle/capacity_1/unhappy_particles_process_circle.pdf'
# plot "../unhappy_process/circle/capacity_1/data/unhappy_process_n=10000.dat" using 1:2 w l ls 1 title "M = 500000", \
# "../unhappy_process/circle/capacity_1/data/unhappy_process_n=10000.dat" using 0:3 w l ls 2 title "M = 495000", \
# "../unhappy_process/circle/capacity_1/data/unhappy_process_n=10000.dat" using 0:4 w l ls 3 title "M = 501500"

# set title 'Process of unhappy particles on a grid n=99856' 
# set yr [0:54000]
# set output '../unhappy_process/grid/capacity_1/unhappy_particles_process_grid.pdf'
# plot "../unhappy_process/grid/capacity_1/data/unhappy_process_n=99856.dat" using 1:2 w l ls 1 title "M = 500000", \
# "../unhappy_process/grid/capacity_1/data/unhappy_process_n=99856.dat" using 0:3 w l ls 2 title "M = 495000", \
# "../unhappy_process/grid/capacity_1/data/unhappy_process_n=99856.dat" using 0:4 w l ls 3 title "M = 500125"
