set terminal post enhanced colour solid font 20  # wybor formatu, w jakim chcemy utworzyc wynikowy rysunek

#set terminal post enhanced colour

set output "wynik.eps" # nazwa pliku wynikowego

set title "Interpolacja Newtona z rownoleglymi wezlami" # tytul wykresu
set xlabel "x" # etykieta osi OX
set ylabel "f(x)" # etykieta osi OY
set grid



# n=5
plot [-5 to 5] [-0.2 to 1.1] "Newton1.dat" u 1:2 w l lc 3 t "f(x) = 1/(1+x^2)", "Newton1.dat" u 1:3 w l lc 7 t "W_{5}(x)"

# n= 10
plot [-5 to 5] [-0.5 to 2]   "Newton2.dat" u 1:2 w l lc 3 t "f(x) = 1/(1+x^2)", "Newton2.dat" u 1:3 w l lc 7 t "W_{10}(x)"

# n = 15
plot [-5 to 5] [-0.5 to 2.5] "Newton3.dat" u 1:2 w l lc 3 t "f(x) = 1/(1+x^2)", "Newton3.dat" u 1:3 w l lc 7 t "W_{15}(x)"

# n = 20
plot [-5 to 5] [-60 to 10]   "Newton4.dat" u 1:2 w l lc 3 t "f(x) = 1/(1+x^2)", "Newton4.dat" u 1:3 w l lc 7 t "W_{20}(x)"




set title "Interpolacja Newtona z wezlami Czybyszewa" # tytul wykresu

# n=5
plot [-5 to 5] [0 to 1] "Ch1.dat" u 1:2 w l lc 3 t "f(x) = 1/(1+x^2)", "Ch1.dat" u 1:3 w l lc 7 t "W_{5}(x)"

# n= 10
plot [-5 to 5] [0 to 1] "Ch2.dat" u 1:2 w l lc 3 t "f(x) = 1/(1+x^2)", "Ch2.dat" u 1:3 w l lc 7 t "W_{10}(x)"

# n = 15
plot [-5 to 5] [0 to 1] "Ch3.dat" u 1:2 w l lc 3 t "f(x) = 1/(1+x^2)", "Ch3.dat" u 1:3 w l lc 7 t "W_{15}(x)"

# n = 20
plot [-5 to 5] [0 to 1] "Ch4.dat" u 1:2 w l lc 3 t "f(x) = 1/(1+x^2)", "Ch4.dat" u 1:3 w l lc 7 t "W_{20}(x)"
