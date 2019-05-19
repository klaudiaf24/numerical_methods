set terminal post enhanced colour solid font 20  # wybor formatu, w jakim chcemy utworzyc wynikowy rysunek

set output "wnik.eps" # nazwa pliku wynikowego

#3
set xlabel "x" # etykieta osi OX
set ylabel "{/Symbol j}_j (x)" # etykieta osi OY
set grid
plot [-4 to 4] [-1.1 to 1.1] "wynik.dat" u 1:2 w l lc 1 t "{/Symbol j}_0 (x)", "wynik.dat" u 1:3 w l lc 2 t "{/Symbol j}_1 (x)","wynik.dat" u 1:4 w l lc 3 t "{/Symbol j}_2 (x)","wynik.dat" u 1:5 w l lc 4 t "{/Symbol j}_3 (x)","wynik.dat" u 1:6 w l lc 5 t "{/Symbol j}_4 (x)","wynik.dat" u 1:7 w l lc 7 t "{/Symbol j}_5 (x)","wynik.dat" u 1:8 w l lc 8 t "{/Symbol j}_6 (x)"

#4
set xlabel "x" # etykieta osi OX
set ylabel "f(x)" # etykieta osi OY
set grid
plot [-4 to 4] [-1.5 to 1.5] "wynik10.dat" u 1:2 w l lc 1 t "f(x)", "wynik10.dat" u 1:3 w p pt 7 ps 0.5 t "f_{szum}(x)","wynik10.dat" u 1:4 w l lc 3 t "F(x)"
plot [-4 to 4] [-1.5 to 1.5] "wynik30.dat" u 1:2 w l lc 1 t "f(x)", "wynik30.dat" u 1:3 w p pt 7 ps 0.5 t "f_{szum}(x)","wynik30.dat" u 1:4 w l lc 3 t "F(x)"
plot [-4 to 4] [-1.5 to 1.5] "wynik50.dat" u 1:2 w l lc 1 t "f(x)", "wynik50.dat" u 1:3 w p pt 7 ps 0.5 t "f_{szum}(x)","wynik50.dat" u 1:4 w l lc 3 t "F(x)"
