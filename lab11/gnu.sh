set terminal post enhanced colour solid font 20  # wybor formatu, w jakim chcemy utworzyc wynikowy rysunek

set output "wniki.eps" # nazwa pliku wynikowego
set xlabel "t " # etykieta osi OX
set ylabel "f(t)" # etykieta osi OY
set grid


set title "k = 8" # tytul wykresu
plot [0 to 3] [-3 to 3] "wynik8.dat" u 1:2 w l lc 5 t "f_o(t)", "wynik8.dat" u 1:3 w l lc 3 t "f(t) * g(t)"

set title "k = 10" # tytul wykresu
plot [0 to 3] [-3 to 3] "wynik10.dat" u 1:2 w l lc 5 t "f_o(t)", "wynik10.dat" u 1:3 w l lc 3 t "f(t) * g(t)"

set title "k = 12" # tytul wykresu
plot [0 to 3] [-3 to 3] "wynik12.dat" u 1:2 w l lc 5 t "f_o(t)", "wynik12.dat" u 1:3 w l lc 3 t "f(t) * g(t)"
