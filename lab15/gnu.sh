set terminal post enhanced colour solid font 20  # wybor formatu, w jakim chcemy utworzyc wynikowy rysunek

set output "wniki.eps" # nazwa pliku wynikowego
set xlabel "N " # etykieta osi OX
set grid

#1
set ylabel "I_N" # etykieta osi OY
plot "zad1.dat"  u 1:2 w l lc 5 t "I_N"

set ylabel "%sigma (I_N)" # etykieta osi OY
plot "zad1.dat"  u 1:3 w l lc 5 t "%sigma (I_N)" 

#2
set ylabel "I_N" # etykieta osi OY
plot "zad2.dat"  u 1:2 w l lc 5 t "I_N"

set ylabel "%sigma (I_N)" # etykieta osi OY
plot "zad2.dat"  u 1:3 w l lc 5 t "%sigma (I_N)" 