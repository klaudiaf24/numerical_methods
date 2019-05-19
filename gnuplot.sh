set terminal post enhanced colour solid font 20  # wybor formatu, w jakim chcemy utworzyc wynikowy rysunek

set output "x_t.eps" # nazwa pliku wynikowego
set title "Wychylenie oscylatora x(t)" # tytul wykresu
set xlabel "t " # etykieta osi OX
set ylabel "x(t)" # etykieta osi OY
set grid # wlaczenie widoczności siatki pomocniczej
plot "out.dat" w p pt 7 ps 0.7 t "x(t), dt = 0.1", cos(x) w l lc 4 t "Acos(t)" #w p pt 7 ps 0.7 t
# plot - polecenie rysowania pliku o podanej nazwie "out.dat"d
# w p == with points
# w l == with line
# t "dt = 0.1" == title "dt = 0.1"