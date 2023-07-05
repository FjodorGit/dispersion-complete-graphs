set terminal pdfcairo enhanced color dashed font "Alegreya, 14" rounded size 16 cm, 9.6 cm

set grid
set datafile missing '0'
set key right top
set title 'Process of unhappy particles'      # Set the plot title
set ylabel 'Unhappy count'        # Set the x-axis label
set xlabel 'Time'        # Set the y-axis label

set output '../unhappy_process/fully_connected/capacity_1/unhappy_particles_process.pdf'
plot "../unhappy_process/fully_connected/capacity_1/data/unhappy_process_n=1000000.dat" using 1:2 w l ls 1 title "n = 1000000, M = 500000", \
"../unhappy_process/fully_connected/capacity_1/data/unhappy_process_n=1000000.dat" using 0:3 w l ls 2 title "n = 1000000, M = 495000", \
"../unhappy_process/fully_connected/capacity_1/data/unhappy_process_n=1000000.dat" using 0:4 w l ls 3 title "n = 1000000, M = 501500"

set yr [0:5000]
set output '../unhappy_process/fully_connected/capacity_1/unhappy_particles_process_zoomed.pdf'
plot "../unhappy_process/fully_connected/capacity_1/data/unhappy_process_n=1000000.dat" using 1:2 w l ls 1 title "n = 1000000, M = 500000", \
"../unhappy_process/fully_connected/capacity_1/data/unhappy_process_n=1000000.dat" using 0:3 w l ls 2 title "n = 1000000, M = 495000", \
"../unhappy_process/fully_connected/capacity_1/data/unhappy_process_n=1000000.dat" using 0:4 w l ls 3 title "n = 1000000, M = 501500"

set yr [0:550000]
set output '../unhappy_process/fully_connected/capacity_2/unhappy_particles_process_c2.pdf'
plot "../unhappy_process/fully_connected/capacity_2/data/unhappy_process_n=1000000.dat" using 1:2 w l ls 1 title "n = 1000000, M = 500000", \
"../unhappy_process/fully_connected/capacity_2/data/unhappy_process_n=1000000.dat" using 0:3 w l ls 2 title "n = 1000000, M = 495000", \
"../unhappy_process/fully_connected/capacity_2/data/unhappy_process_n=1000000.dat" using 0:4 w l ls 3 title "n = 1000000, M = 501500"
