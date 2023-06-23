set terminal png # Specify the output terminal (e.g., png, svg, pdf)
set output 'plot.png'    # Specify the output file name

set title 'Runtime evaluation'      # Set the plot title
set xlabel 'Graphsize'        # Set the x-axis label
set ylabel 'Timesteps'        # Set the y-axis label

plot "data/half_graph_size.txt" with lines linewidth 2 title "M = Graphsize/2", \
     "data/smaller_half_graph_size.txt" with lines linewidth 2 title "M < Graphsize/2", \
     "data/bigger_half_graph_size.txt" with lines linewidth 2 title "M > Graphsize/2"
