set terminal post enhanced colour solid font 20  # wybor formatu, w jakim chcemy utworzyc wynikowy rysunek

#set terminal post enhanced colour

set output "wnik.eps" # nazwa pliku wynikowego

#wartosc alfa

set title "Czestosc wlasna drgan" # tytul wykresu
set xlabel "{/Symbol a}" # etykieta osi OX
set ylabel "{/Symbol w} = f({/Symbol a})" # etykieta osi OY
set grid
plot [0 to 100] [0 to 0.5] "wart_alfa.dat" u 1:2 w l lc 1 t "{/Symbol w}_1", "wart_alfa.dat" u 1:3 w l lc 2 t "{/Symbol w}_2", "wart_alfa.dat" u 1:4 w l lc 3 t "{/Symbol w}_3", "wart_alfa.dat" u 1:5 w l lc 4 t "{/Symbol w}_4", "wart_alfa.dat" u 1:6 w l lc 5 t "{/Symbol w}_5", "wart_alfa.dat" u 1:7 w l lc 6 t "{/Symbol w}_6"

#wektor wlasny dla alfa 0

set title "Wektory wlasne {/Symbol a} = 0" # tytul wykresu
set xlabel "x" # etykieta osi OX
set ylabel "u(x)" # etykieta osi OY
set grid
plot [-5 to 5] [-0.15 to 0.15] "wektory_wlasne_0.dat" u 1:2 w l lc 1 t "vec_1", "wektory_wlasne_0.dat"  u 1:3 w l lc 2 t "vec_2", "wektory_wlasne_0.dat"  u 1:4 w l lc 3 t "vec_3", "wektory_wlasne_0.dat"  u 1:5 w l lc 4 t "vec_4", "wektory_wlasne_0.dat"  u 1:6 w l lc 5 t "vec_5", "wektory_wlasne_0.dat"  u 1:7 w l lc 6 t "vec_6"



set title "Wektory wlasne {/Symbol a} = 100" # tytul wykresu
set xlabel "x" # etykieta osi OX
set ylabel "u(x)" # etykieta osi OY
set grid
plot [-5 to 5] [-0.15 to 0.15] "wektory_wlasne_100.dat" u 1:2 w l lc 1 t "vec_1", "wektory_wlasne_100.dat"  u 1:3 w l lc 2 t "vec_2", "wektory_wlasne_100.dat"  u 1:4 w l lc 3 t "vec_3", "wektory_wlasne_100.dat"  u 1:5 w l lc 4 t "vec_4", "wektory_wlasne_100.dat"  u 1:6 w l lc 5 t "vec_5", "wektory_wlasne_100.dat"  u 1:7 w l lc 6 t "vec_6"
