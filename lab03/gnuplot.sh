set terminal post enhanced colour solid font 20  # wybor formatu, w jakim chcemy utworzyc wynikowy rysunek

set output "wnik.eps" # nazwa pliku wynikowego
set title "Metoda sprezonych gradientow dla macierzy wstegowej" # tytul wykresu
set xlabel "k (numer iteracji) " # etykieta osi OX

set ylabel "||x||" # etykieta osi OY
set grid
plot "wynik.dat" u 1:5 w l lc 4 t "||x||" #w p pt 7 ps 0.7 t

set ylabel "||r||" # etykieta osi OY
set logscale y
set grid # wlaczenie widoczności siatki pomocniczej
plot "wynik.dat" u 1:2 w l lc 7 t "||r||"
