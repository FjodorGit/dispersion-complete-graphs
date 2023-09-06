set terminal cairolatex

set grid
set datafile missing '0'
set key right top
set title 'Process of unhappy particles n=1000000'      # Set the plot title
set ylabel 'Unhappy count'        # Set the x-axis label
set xlabel 'Steps'        # Set the y-axis label


# Process of particles on fully_connected graph
set output '/home/fjk/Uni/Bachelorarbeit/Arbeit/bilder/unhappy_capacity_1/unhappy_particles_process.tex'
plot "../unhappy_process/fully_connected/capacity_1/data/unhappy_process_n=1000000_M=500000.dat" ls 1 title "M = 500000" with lines, \
"../unhappy_process/fully_connected/capacity_1/data/unhappy_process_n=1000000_M=495000.dat" ls 2 title "M = 495000" with lines, \
"../unhappy_process/fully_connected/capacity_1/data/unhappy_process_n=1000000_M=501500.dat" ls 3 title "M = 501500" with lines

set yr [0:5000]
set output '/home/fjk/Uni/Bachelorarbeit/Arbeit/bilder/unhappy_capacity_1/unhappy_particles_process_zoomed.tex'
plot "../unhappy_process/fully_connected/capacity_1/data/unhappy_process_n=1000000_M=500000.dat" ls 1 title "M = 500000" with lines, \
"../unhappy_process/fully_connected/capacity_1/data/unhappy_process_n=1000000_M=495000.dat" ls 2 title "M = 495000" w l, \
"../unhappy_process/fully_connected/capacity_1/data/unhappy_process_n=1000000_M=501500.dat" ls 3 title "M = 501500" w l

set yr [0:5000]
set output '/home/fjk/Uni/Bachelorarbeit/Arbeit/bilder/unhappy_capacity_1/unhappy_particles_long_running.tex'
set arrow from 0,1712  to 35000, 1712 nohead dashtype 1 lc rgb "#FF7800" lw 4 front
plot 1/0 t "threshold" dashtype 1 lc rgb "#FF7800" lw 4, \
"../unhappy_process/fully_connected/capacity_1/data/unhappy_process_n=1000000_M=501500.dat" ls 3 title "M = 501500" with lines
unset arrow

set title 'Process of unhappy particles n=1000000 and capacity 2' 
set yr [0:1010000]
set output '/home/fjk/Uni/Bachelorarbeit/Arbeit/bilder/cap2/unhappy_process.tex'
plot "../unhappy_process/fully_connected/capacity_2/data/unhappy_process_n=1000000_M=1000000.dat" w l ls 1 title "M = 1000000", \
"../unhappy_process/fully_connected/capacity_2/data/unhappy_process_n=1000000_M=990000.dat" w l ls 2 title "M = 990000", \
"../unhappy_process/fully_connected/capacity_2/data/unhappy_process_n=1000000_M=1002500.dat" w l ls 3 title "M = 1002500"

set yr [0:7000]
set output '/home/fjk/Uni/Bachelorarbeit/Arbeit/bilder/cap2/unhappy_process_zoomed.tex'
plot "../unhappy_process/fully_connected/capacity_2/data/unhappy_process_n=1000000_M=1000000.dat" w l ls 1 title "M = 1000000", \
"../unhappy_process/fully_connected/capacity_2/data/unhappy_process_n=1000000_M=990000.dat" w l ls 2 title "M = 990000", \
"../unhappy_process/fully_connected/capacity_2/data/unhappy_process_n=1000000_M=1002500.dat" w l ls 3 title "M = 1002500"

# Never finishing process
set yr [0:11000]
set title 'Process of unhappy particles n=1000000 and M=505000 (not finished)' 
set output '/home/fjk/Uni/Bachelorarbeit/Arbeit/bilder/unhappy_capacity_1/never_finishing_unhappy_particles_process.tex'
set arrow from 0,5689  to 200000, 5689 nohead dashtype 1 lc rgb "#FF7800" lw 4 front
set xtics ("20k" 20000, "40k" 40000, "60k" 60000, "80k" 80000, "100k" 100000, "120k" 120000, "140k" 140000, "160k" 160000, "180k" 180000, "200k" 200000, "220k" 220000)
plot 1/0 t "threshold" dashtype 1 lc rgb "#FF7800" lw 4, \
"../unhappy_process/fully_connected/capacity_1/data/unhappy_process_n=1000000_M=505000.dat" ls 3 notitle with lines
unset arrow

# Never finishing process capacity_2
set yr [0:10000]
set title 'Process of unhappy particles n=1000000 and M=1003000 with capacity 2 (not finished)' 
set output '/home/fjk/Uni/Bachelorarbeit/Arbeit/bilder/cap2/never_finishing_unhappy_particles_process.tex'
# set arrow from 0,5689  to 200000, 5689 nohead dashtype 1 lc rgb "#FF7800" lw 4 front
set xtics ("20k" 20000, "40k" 40000, "60k" 60000, "80k" 80000, "100k" 100000, "120k" 120000, "140k" 140000, "160k" 160000, "180k" 180000, "200k" 200000, "220k" 220000)
# plot 1/0 t "threshold" dashtype 1 lc rgb "#FF7800" lw 4
plot "../unhappy_process/fully_connected/capacity_2/data/unhappy_process_n=1000000_M=1003000.dat" ls 3 notitle with lines

# average process capacity_2
set yr [0:10000]
set title 'Average process of unhappy particles n=1000000 and M=1005000 with capacity 2 (not finished)' 
set output '/home/fjk/Uni/Bachelorarbeit/Arbeit/bilder/cap2/average_process.tex'
# set arrow from 0,5689  to 200000, 5689 nohead dashtype 1 lc rgb "#FF7800" lw 4 front
unset xtics
set xtics
plot "../average_process/fully_connected/capacity_2/average_process_calculated.dat" ls 3 notitle with lines

# Plot variance
# set yr [0:18000]
# set title 'Variance for n=100000 and M=50500' 
# set output '/home/fjk/Uni/Bachelorarbeit/Arbeit/bilder/unhappy_capacity_1/with_variance.tex'
# plot "../unhappy_process/fully_connected/capacity_1/data/variance_process_n=100000_M=50500.dat" using 1:2 w l ls 4 notitle, \

#Line process
set yr [0:1000]
set xtics ("50k" 50000, "100k" 100000, "150k" 150000, "200k" 200000, "250k" 250000, "300k" 300000, "350k" 350000, "400k" 400000, "450k" 450000)
set output '/home/fjk/Uni/Bachelorarbeit/Arbeit/bilder/unhappy_capacity_1/line_process.tex'
set title 'Processes on a line graph'
plot "../unhappy_process/line/capacity_1/data/unhappy_process_n=1_M=200.dat" w l ls 1 title "M = 200", \
"../unhappy_process/line/capacity_1/data/unhappy_process_n=1_M=400.dat" w l ls 2 title "M = 400" ,\
"../unhappy_process/line/capacity_1/data/unhappy_process_n=1_M=600.dat" w l ls 3 title "M = 600", \
"../unhappy_process/line/capacity_1/data/unhappy_process_n=1_M=800.dat" w l ls 4 title "M = 800", \
"../unhappy_process/line/capacity_1/data/unhappy_process_n=1_M=1000.dat" w l ls 5 title "M = 1000" 

#grid process
set yr [0:250000]
set xtics ("20k" 20000, "40k" 40000, "60k" 60000, "80k" 80000, "100k" 100000, "120k" 120000, "140k" 140000, "160k" 160000, "180k" 180000, "200k" 200000, "220k" 220000)
set output '/home/fjk/Uni/Bachelorarbeit/Arbeit/bilder/unhappy_capacity_1/grid_process.tex'
set title 'Processes on a grid graph'
plot "../unhappy_process/grid/capacity_1/data/unhappy_process_n=1_M=50000.dat" w l ls 1 title "M = 50000", \
"../unhappy_process/grid/capacity_1/data/unhappy_process_n=1_M=100000.dat" w l ls 2 title "M = 100000", \
"../unhappy_process/grid/capacity_1/data/unhappy_process_n=1_M=150000.dat" w l ls 3 title "M = 150000", \
"../unhappy_process/grid/capacity_1/data/unhappy_process_n=1_M=200000.dat" w l ls 4 title "M = 200000", \
"../unhappy_process/grid/capacity_1/data/unhappy_process_n=1_M=250000.dat" w l ls 5 title "M = 250000"

# set title 'Process of unhappy particles circle graph' 
# set yr [0:1000]
# set output '../unhappy_process/circle/capacity_1/unhappy_particles_process_circle.tex'
# plot "../unhappy_process/circle/capacity_1/data/unhappy_process_n=10000.dat" using 1:2 w l ls 1 title "M = 500000", \
# "../unhappy_process/circle/capacity_1/data/unhappy_process_n=10000.dat" using 0:3 w l ls 2 title "M = 495000", \
# "../unhappy_process/circle/capacity_1/data/unhappy_process_n=10000.dat" using 0:4 w l ls 3 title "M = 501500"

# set title 'Process of unhappy particles on a grid n=99856' 
# set yr [0:54000]
# set output '../unhappy_process/grid/capacity_1/unhappy_particles_process_grid.tex'
# plot "../unhappy_process/grid/capacity_1/data/unhappy_process_n=99856.dat" using 1:2 w l ls 1 title "M = 500000", \
# "../unhappy_process/grid/capacity_1/data/unhappy_process_n=99856.dat" using 0:3 w l ls 2 title "M = 495000", \
# "../unhappy_process/grid/capacity_1/data/unhappy_process_n=99856.dat" using 0:4 w l ls 3 title "M = 500125"
