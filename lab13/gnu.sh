set terminal post enhanced colour solid font 20  # wybor formatu, w jakim chcemy utworzyc wynikowy rysunek

set output "wniki.eps" # nazwa pliku wynikowego
set xlabel "x_{20} " # etykieta osi OX
set ylabel "|(V_{dok} - V_n )/V_{dok}|" # etykieta osi OY
set grid


set title "n = 5" # tytul wykresu
plot [0 to 6] [0 to 0.2] "wyn5.dat" w p pt 7 ps 0.7 t "|(V_{dok} - V_n )/V_{dok}|"

set title "n = 10" # tytul wykresu
plot [0 to 6] [0 to 0.14] "wyn10.dat" w p pt 7 ps 0.7 t "|(V_{dok} - V_n )/V_{dok}|"

set title "n = 15" # tytul wykresu
plot [0 to 6] [0 to 0.12] "wyn15.dat" w p pt 7 ps 0.7 t "|(V_{dok} - V_n )/V_{dok}|"

set title "n = 20" # tytul wykresu
plot [0 to 6] [0 to 0.1] "wyn20.dat" w p pt 7 ps 0.7 t "|(V_{dok} - V_n )/V_{dok}|"

set title "n = 25" # tytul wykresu
plot [0 to 6] [0 to 0.09] "wyn25.dat" w p pt 7 ps 0.7 t "|(V_{dok} - V_n )/V_{dok}|"

set title "n = 30" # tytul wykresu
plot [0 to 6] [0 to 0.08] "wyn30.dat" w p pt 7 ps 0.7 t "|(V_{dok} - V_n )/V_{dok}|"

set title "n = 35" # tytul wykresu
plot [0 to 6] [0 to 0.08] "wyn35.dat" w p pt 7 ps 0.7 t "|(V_{dok} - V_n )/V_{dok}|"
