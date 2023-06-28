set terminal pdfcairo enhanced color dashed font "Alegreya, 14" rounded size 16 cm, 9.6 cm

set grid
set key right top
set title 'Runtime evaluation'      # Set the plot title
set xlabel 'Graphsize'        # Set the x-axis label
set ylabel 'Timesteps'        # Set the y-axis label
set output 'plot.pdf'

plot "data/half_graph_size.txt" w l ls 1 title "Graphsize/2", \
     "data/smaller_half_graph_size.txt" w l ls 2 title "(1 - epsilon) * Graphsize/2", \
     "data/bigger_half_graph_size.txt" w l ls 3 title "(1 + epsilon) * Graphsize/2"
