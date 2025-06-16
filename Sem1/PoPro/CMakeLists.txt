cmake_minimum_required(VERSION 3.29)
project(PoPro)

set(CMAKE_CXX_STANDARD 14)

include_directories(LAB10)

add_executable(PoPro
    LAB10/veccalc.c
    LAB10/veccalc.h
    LAB10/veccommon.h
    LAB10/vecin.c
    LAB10/vecin.h
    LAB10/vecout.c
    LAB10/vecout.h
    LAB10/vectors.c
    LAB4/bow_tie.c
    LAB4/shuffle.c
    LAB4/tempCodeRunnerFile.c
    LAB4/zadanie3_liczbaWyst.c
    LAB5/zad1_ImplementoiwanieWlasnychFunkcji.c
    LAB5/zad2.c
    LAB5/zad3_pierwiastki.c
    LAB6/lab_6__zadanie_3.c
    LAB6/zad1.c
    LAB6/zad2.c
    LAB7/zad1.c
    LAB7/zad2.c
    LAB7/zad3.c
    LAB8/zad1.c
    LAB8/zad2.c
    LAB9/zad2.c
    LAB9/zapisywanie.c
    VS/001/Project1/001.c
    VS/001/Project1/002.c
    VS/001/001.cpp
    VS/1.c
    czyPierwsza.c
    decToBin.c
    kalkulator.c
    KC1_Jan_Czechowski.c
    lab2.c
    laczenieJednaFunkcja.c
    laczenieSortowanie.c
    laczenieTablicSortowanie.c
    simple.c
    simple2.c
    testowanie.c
    wyk3.c
    wyk4_gra.c
    zamianaLiczb.c)
