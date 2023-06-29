set terminal pdfcairo enhanced color dashed font "Alegreya, 14" rounded size 16 cm, 9.6 cm

set grid
set ylabel 'Frequency'        # Set the x-axis label
set xlabel 'Timesteps/√n'        # Set the y-axis label
binwidth = 0.04
binstart = -1
load 'hist.fct'

set title 'Distribution with n=100000 and M=51000'      # Set the plot title
set output '../distribution_M>half_graphsize.pdf'
plot '../data/distribution_bigger.txt' i 0 @hist ls 3 notitle

set title 'Distribution with n=100000 and M=50000'      # Set the plot title
set output '../distribution_M=half_graphsize.pdf'
plot '../data/distribution_equal.txt' i 0 @hist ls 1 notitle

set title 'Distribution with n=100000 and M=48000'      # Set the plot title
set output '../distribution_M<half_graphsize.pdf'
plot '../data/distribution_smaller.txt' i 0 @hist ls 2 notitle

set title 'Distribution comparison n=100000'      # Set the plot title
set output '../distribution_comparison.pdf'
plot '../data/distribution_smaller.txt' i 0 @hist ls 2 title "M=48000", \
'../data/distribution_equal.txt' i 0 @hist ls 1 title "M=50000",\
'../data/distribution_bigger.txt' i 0 @hist ls 3 title "M=51000"
