set terminal pdfcairo enhanced color dashed font "Alegreya, 14" rounded size 16 cm, 9.6 cm

set grid
set ylabel 'Frequency'        # Set the x-axis label
set xlabel 'Timesteps/√n'        # Set the y-axis label
set yr [0:1000]
binwidth = 0.04
binstart = -1
load 'hist.fct'

set title 'Distribution with n=10000 and M=5100'      # Set the plot title
set output '../distribution_M>half_graphsize.pdf'
plot [0:60] '../data/distribution_bigger.txt' i 0 @hist ls 3 notitle

set title 'Distribution with n=10000 and M=5000'      # Set the plot title
set output '../distribution_M=half_graphsize.pdf'
plot [0:60] '../data/distribution_equal.txt' i 0 @hist ls 1 notitle

set title 'Distribution with n=10000 and M=4750'      # Set the plot title
set output '../distribution_M<half_graphsize.pdf'
plot [0:60] '../data/distribution_smaller.txt' i 0 @hist ls 2 notitle
