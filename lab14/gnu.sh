set terminal post enhanced colour solid font 20  # wybor formatu, w jakim chcemy utworzyc wynikowy rysunek

set output "wniki.eps" # nazwa pliku wynikowego
set xlabel "x_i " # etykieta osi OX
set grid

#Generetor 1
set ylabel "x_{i+1}" # etykieta osi OY
plot [0 to 1] [0 to 1] "generator1.dat" u 1:2 w p pt 7 ps 0.7 t "U_1(0,1), x_{i+1}(x_i)"

set ylabel "x_{i+2}" # etykieta osi OY
plot [0 to 1] [0 to 1] "generator1.dat" u 1:3 w p pt 7 ps 0.7 t "U_1(0,1), x_{i+2}(x_i)"

set ylabel "x_{i+3}" # etykieta osi OY
plot [0 to 1] [0 to 1] "generator1.dat" u 1:4 w p pt 7 ps 0.7 t "U_1(0,1), x_{i+3}(x_i)"

#Generetor 2
set ylabel "x_{i+1}" # etykieta osi OY
plot [0 to 1] [0 to 1] "generator2.dat" u 1:2 w p pt 7 ps 0.7 lc 5 t "U_1(0,1), x_{i+1}(x_i)"

set ylabel "x_{i+2}" # etykieta osi OY
plot [0 to 1] [0 to 1] "generator2.dat" u 1:3 w p pt 7 ps 0.7 lc 5 t "U_1(0,1), x_{i+2}(x_i)"

set ylabel "x_{i+3}" # etykieta osi OY
plot [0 to 1] [0 to 1] "generator2.dat" u 1:4 w p pt 7 ps 0.7 lc 5 t "U_1(0,1), x_{i+3}(x_i)"

#Generetor 3
set ylabel "x_{i+1}" # etykieta osi OY
plot [0 to 1] [0 to 1] "generator3.dat" u 1:2 w p pt 7 ps 0.7 lc 2 t "U_1(0,1), x_{i+1}(x_i)"

set ylabel "x_{i+2}" # etykieta osi OY
plot [0 to 1] [0 to 1] "generator3.dat" u 1:3 w p pt 7 ps 0.7 lc 2 t "U_1(0,1), x_{i+2}(x_i)"

set ylabel "x_{i+3}" # etykieta osi OY
plot [0 to 1] [0 to 1] "generator3.dat" u 1:4 w p pt 7 ps 0.7 lc 2 t "U_1(0,1), x_{i+3}(x_i)"

##
set xlabel "x"
set ylabel "y"
set zlabel "z"
set xtics 0.5
set ytics 0.5
set ztics 0.5
set view equal
set ticslevel 0
set border 895
splot "sfera.dat" u 1:2:3 pt 7 ps 0.5 lc rgb "red"

##
unset colorbox
set palette defined (0 '#000000', 1 '#ff0000')
splot "kula.dat" u 1:2:3:(sqrt($1**2 + $2**2 + $3**2)) pt 7 ps 0.5 lc palette 
