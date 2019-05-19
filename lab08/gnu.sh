set terminal post enhanced colour solid font 20  # wybor formatu, w jakim chcemy utworzyc wynikowy rysunek

#set terminal post enhanced colour

set output "wynik.eps" # nazwa pliku wynikowego

set title "Interpolacja funkcjami sklejanymi" # tytul wykresu
set xlabel "x" # etykieta osi OX
set ylabel "f(x)" # etykieta osi OY
set grid

#to pierwsze

# n = 10
plot [-5 to 5] [-2 to 1] "fun1_10.dat" u 1:2 w l lc 3 t "f''(x) - analitycznie", "fun2_10.dat" u 1:2 w p pt 0 t "m_i", "fun2_10.dat" u 1:3 w p pt 7 lc 1 t "f''(x) - numerycznie"


#funkcja 1

# n=5
plot [-5 to 5] [-0.2 to 1] "fun1_5.dat" u 1:2 w l lc 3 t "f(x) = 1/(1+x^2)", "fun1_5.dat" u 1:3 w l lc 7 t "s(x)"

# n= 8
plot [-5 to 5] [0 to 1]   "fun1_8.dat" u 1:2 w l lc 3 t "f(x) = 1/(1+x^2)", "fun1_8.dat" u 1:3 w l lc 7 t "s(x)"

# n = 21
plot [-5 to 5] [0 to 1]   "fun1_21.dat" u 1:2 w l lc 3 t "f(x) = 1/(1+x^2)", "fun1_21.dat" u 1:3 w l lc 7 t "s(x)"


#funkcja 2

# n=5
plot [-5 to 5] [-1 to 1] "fun2_5.dat" u 1:2 w l lc 3 t "f(x) = cos(2x)", "fun2_5.dat" u 1:3 w l lc 7 t "s(x)"

# n =8
plot [-5 to 5] [-1 to 1] "fun2_8.dat" u 1:2 w l lc 3 t "f(x) = cos(2x)", "fun2_8.dat" u 1:3 w l lc 7 t "s(x)"

# n = 21
plot [-5 to 5] [-1 to 1] "fun2_21.dat" u 1:2 w l lc 3 t "f(x) = cos(2x)", "fun2_21.dat" u 1:3 w l lc 7 t "s(x)"
