set terminal pdfcairo enhanced color dashed font "Alegreya, 14" rounded size 16 cm, 9.6 cm

set grid
set datafile missing '0'
set key right top
set title 'Process of unhappy particles'      # Set the plot title
set ylabel 'Unhappy count'        # Set the x-axis label
set xlabel 'Time'        # Set the y-axis label

set output 'unhappy_particles_process.pdf'
plot "data/unhappy_particles_process.txt" using 0:2 w l ls 1 title "n = 100000, M = 50000", \
"data/unhappy_particles_process.txt" using 0:3 w l ls 2 title "n = 100000, M = 49000", \
"data/unhappy_particles_process.txt" using 0:4 w l ls 3 title "n = 100000, M = 50500"

set yr [0:2000]
set output 'unhappy_particles_process_zoomed.pdf'
plot "data/unhappy_particles_process.txt" using 0:2 w l ls 1 title "n = 100000, M = 50000", \
"data/unhappy_particles_process.txt" using 0:3 w l ls 2 title "n = 100000, M = 49000", \
"data/unhappy_particles_process.txt" using 0:4 w l ls 3 title "n = 100000, M = 50500"
