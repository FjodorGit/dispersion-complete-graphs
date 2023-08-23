set terminal cairolatex

set style arrow 1 head filled size screen 0.03,15,45 ls 4
set grid
set ylabel 'Frequency'        # Set the y-axis label
set xlabel "Timesteps/$\\sqrt{n}$"        # Set the x-axis label
binwidth = 0.04
binstart = -1
load 'hist.fct'

set title 'Distribution of $T_{1000000, 500000}$'      # Set the plot title
set output '/home/fjk/Uni/Bachelorarbeit/Arbeit/bilder/distribution_cap1/distribution_for_n=1000000_M=500000.tex'
stats '../distribution/fully_connected/capacity_1/data/distribution_for_n=1000000_M=500000.dat' nooutput
mean_value = STATS_mean
set label sprintf("%f", mean_value) at mean_value, graph -0.2 center
set arrow from mean_value, graph -0.17 to mean_value, graph 0 lc "blue" as 1
plot '../distribution/fully_connected/capacity_1/data/distribution_for_n=1000000_M=500000.dat' i 0 @hist ls 1 notitle
unset label
unset arrow

# set title 'Distribution with n=100000 and M=49000'      # Set the plot title
# set output '../distribution/fully_connected/capacity_1/M<half_graphsize.pdf'
# plot '../distribution/fully_connected/capacity_1/data/distribution_for_n=100000_M=49000.dat' i 0 @hist ls 2 notitle

# Distribution line graph
set title 'Distribution of $T_{\mathcal{L}, 500}$'      # Set the plot title
set xrange [0:150000]
set xlabel "Timesteps"
binwidth = 1000
binstart = 0
load 'hist.fct'
set output '/home/fjk/Uni/Bachelorarbeit/Arbeit/bilder/distribution_cap1/distribution_line.tex'
plot '../distribution/line/capacity_1/data/distribution_for_n=1_M=500.dat' i 0 @hist ls 1 title "M=500"

# Distribution grid graph
set title 'Distribution of $T_{\mathcal{G}, 10000}$'      # Set the plot title
set xrange [0:15000]
set xlabel "Timesteps"
binwidth = 100
binstart = 0
load 'hist.fct'
set output '/home/fjk/Uni/Bachelorarbeit/Arbeit/bilder/distribution_cap1/distribution_grid.tex'
plot '../distribution/grid/capacity_1/data/distribution_for_n=1_M=10000.dat' i 0 @hist ls 1 title "M=10000"

# set title 'Distribution comparison n=1000000'      # Set the plot title
# set output '../distribution/fully_connected/capacity_1/comparison_n=1000000.pdf'
# plot '../distribution/fully_connected/capacity_1/data/distribution_for_n=1000000_M=495000.dat' i 0 @hist ls 2 title "M=495000", \
# '../distribution/fully_connected/capacity_1/data/distribution_for_n=1000000_M=500000.dat' i 0 @hist ls 1 title "M=500000",\
# '../distribution/fully_connected/capacity_1/data/distribution_for_n=1000000_M=501000.dat' i 0 @hist ls 3 title "M=501000"
 
set title 'Distribution of $T_{1000000, 1000000}$ with capacity 2'
unset xrange
binwidth = 0.04
binstart = 0
load 'hist.fct'
set output '/home/fjk/Uni/Bachelorarbeit/Arbeit/bilder/cap2/distribution.tex'
plot '../distribution/fully_connected/capacity_2/data/distribution_for_n=1000000_M=1000000.dat' i 0 @hist ls 1 title "M=1000000"
