set terminal pdfcairo enhanced color dashed font "Alegreya, 14" rounded size 16 cm, 9.6 cm

set grid
set ylabel 'Frequency'        # Set the x-axis label
set xlabel 'Timesteps/√n'        # Set the y-axis label
binwidth = 0.04
binstart = -1
load 'hist.fct'

set title 'Distribution with n=1000000 and M=501000'      # Set the plot title
set output '../distribution/fully_connected/capacity_1/M>half_graphsize.pdf'
plot '../distribution/fully_connected/capacity_1/data/distribution_for_n=1000000_M=501000.dat' i 0 @hist ls 3 notitle

set title 'Distribution with n=1000000 and M=500000'      # Set the plot title
set output '../distribution/fully_connected/capacity_1/M=half_graphsize.pdf'
plot '../distribution/fully_connected/capacity_1/data/distribution_for_n=1000000_M=500000.dat' i 0 @hist ls 1 notitle

set title 'Distribution with n=100000 and M=49000'      # Set the plot title
set output '../distribution/fully_connected/capacity_1/M<half_graphsize.pdf'
plot '../distribution/fully_connected/capacity_1/data/distribution_for_n=100000_M=49000.dat' i 0 @hist ls 2 notitle

set title 'Distribution comparison n=1000000'      # Set the plot title
set output '../distribution/fully_connected/capacity_1/comparison_n=1000000.pdf'
plot '../distribution/fully_connected/capacity_1/data/distribution_for_n=1000000_M=495000.dat' i 0 @hist ls 2 title "M=495000", \
'../distribution/fully_connected/capacity_1/data/distribution_for_n=1000000_M=500000.dat' i 0 @hist ls 1 title "M=500000",\
'../distribution/fully_connected/capacity_1/data/distribution_for_n=1000000_M=501000.dat' i 0 @hist ls 3 title "M=501000"

set title 'Distribution with n=10000 and M=10000 and capacity 2'
set output '../distribution/fully_connected/capacity_2/M=graphsize.pdf'
plot '../distribution/fully_connected/capacity_2/data/distribution_for_n=10000_M=10000.dat' i 0 @hist ls 1 notitle

set title 'Distribution with n=10000 and M=10100 and capacity 2'
set output '../distribution/fully_connected/capacity_2/M>graphsize.pdf'
plot '../distribution/fully_connected/capacity_2/data/distribution_for_n=10000_M=10100.dat' i 0 @hist ls 3 notitle

set title 'Distribution with n=10000 and M=9900 and capacity 2'
set output '../distribution/fully_connected/capacity_2/M<graphsize.pdf'
plot '../distribution/fully_connected/capacity_2/data/distribution_for_n=10000_M=9900.dat' i 0 @hist ls 2 notitle

set title 'Distribution comparison n=10000 and capacity 2'
set output '../distribution/fully_connected/capacity_2/comparison_n=10000.pdf'
plot '../distribution/fully_connected/capacity_2/data/distribution_for_n=10000_M=9900.dat' i 0 @hist ls 2 title "M=9900", \
'../distribution/fully_connected/capacity_2/data/distribution_for_n=10000_M=10000.dat' i 0 @hist ls 1 title "M=10000",\
'../distribution/fully_connected/capacity_2/data/distribution_for_n=10000_M=10100.dat' i 0 @hist ls 3 title "M=10100"
