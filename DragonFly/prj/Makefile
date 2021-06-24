TASKNO=5
APP=sterowanie-dronem
TASKDIR=${HOME}/edu/po/zad/z${TASKNO}

#
#  To sa opcje dla kompilacji
#
CXXFLAGS=-g -Iinc -W -Wall -pedantic -std=c++17 

__start__: obj dat ./${APP}
	rm -f core.* core; ./${APP}

# Tworzy katalog "obj" gdy go nie ma
# 
obj:
	mkdir obj

dat:
	mkdir dat


./${APP}: obj/main.o obj/lacze_do_gnuplota.o obj/InterfejsUzytkownika.o obj/Scena.o obj/Dron.o  obj/Graniastoslup6.o obj/Prostopadloscian.o obj/GoraZDlugaGrania.o obj/GoraZOstrymSzczytem.o obj/Plaskowyz.o obj/BrylaGeometryczna.o obj/ElementSceny.o
	g++ -o ./${APP} obj/main.o obj/lacze_do_gnuplota.o obj/InterfejsUzytkownika.o  obj/Scena.o obj/Dron.o obj/Graniastoslup6.o obj/Prostopadloscian.o obj/GoraZDlugaGrania.o obj/GoraZOstrymSzczytem.o obj/Plaskowyz.o obj/BrylaGeometryczna.o obj/ElementSceny.o


ext: ./${APP}_rozszerzony
	rm -f core.* core; echo "2i 1+3.1i 2 ? / + ?" | ./${APP}_rozszerzony


obj/main.o: src/main.cpp inc/InterfejsUzytkownika.hh
	g++ -c ${CXXFLAGS} -o obj/main.o src/main.cpp

obj/GoraZDlugaGrania.o: src/GoraZDlugaGrania.cpp inc/GoraZDlugaGrania.hh inc/BrylaGeometryczna.hh
	g++ -c ${CXXFLAGS} -o obj/GoraZDlugaGrania.o src/GoraZDlugaGrania.cpp	

obj/GoraZOstrymSzczytem.o: src/GoraZOstrymSzczytem.cpp inc/GoraZOstrymSzczytem.hh inc/BrylaGeometryczna.hh
	g++ -c ${CXXFLAGS} -o obj/GoraZOstrymSzczytem.o src/GoraZOstrymSzczytem.cpp		

obj/Plaskowyz.o: src/Plaskowyz.cpp inc/Plaskowyz.hh inc/BrylaGeometryczna.hh
	g++ -c ${CXXFLAGS} -o obj/Plaskowyz.o src/Plaskowyz.cpp			

obj/InterfejsUzytkownika.o: src/InterfejsUzytkownika.cpp inc/InterfejsUzytkownika.hh 	
	g++ -c ${CXXFLAGS} -o obj/InterfejsUzytkownika.o src/InterfejsUzytkownika.cpp	

obj/Scena.o: src/Scena.cpp inc/Scena.hh inc/Dron.hh	
	g++ -c ${CXXFLAGS} -o obj/Scena.o src/Scena.cpp

obj/Dron.o: src/Dron.cpp inc/Dron.hh inc/Prostopadloscian.hh inc/Graniastoslup6.hh inc/lacze_do_gnuplota.hh
	g++ -c ${CXXFLAGS} -o obj/Dron.o src/Dron.cpp	

obj/lacze_do_gnuplota.o: src/lacze_do_gnuplota.cpp inc/lacze_do_gnuplota.hh
	g++ -c ${CXXFLAGS} -o obj/lacze_do_gnuplota.o src/lacze_do_gnuplota.cpp	

obj/Prostopadloscian.o: src/Prostopadloscian.cpp inc/Prostopadloscian.hh inc/BrylaGeometryczna.hh
	g++ -c ${CXXFLAGS} -o obj/Prostopadloscian.o src/Prostopadloscian.cpp

obj/Graniastoslup6.o: src/Graniastoslup6.cpp inc/Graniastoslup6.hh inc/BrylaGeometryczna.hh
	g++ -c ${CXXFLAGS} -o obj/Graniastoslup6.o src/Graniastoslup6.cpp	

obj/BrylaGeometryczna.o: src/BrylaGeometryczna.cpp inc/BrylaGeometryczna.hh inc/Wektor3D.hh inc/Wektor.hh inc/ElementSceny.hh	
	g++ -c ${CXXFLAGS} -o obj/BrylaGeometryczna.o src/BrylaGeometryczna.cpp

obj/ElementSceny.o: src/ElementSceny.cpp inc/ElementSceny.hh 
	g++ -c ${CXXFLAGS} -o obj/ElementSceny.o src/ElementSceny.cpp	

obj/Wektor3D.o: src/Wektor3D.cpp inc/Wektor3D.hh inc/Wektor.hh
	g++ -c ${CXXFLAGS} -o obj/Wektor3D.o src/Wektor3D.cpp

obj/Macierz3x3.o: src/Macierz3x3.cpp inc/Macierz3x3.hh inc/Macierz.hh inc/Wektor3D.hh inc/Wektor.hh
	g++ -c ${CXXFLAGS} -o obj/Macierz3x3.o src/Macierz3x3.cpp

obj/Wektor2D.o: src/Wektor2D.cpp inc/Wektor2D.hh inc/Wektor.hh
	g++ -c ${CXXFLAGS} -o obj/Wektor2D.o src/Wektor2D.cpp	

obj/Macierz2x2.o: src/Macierz2x2.cpp inc/Macierz2x2.hh inc/Macierz.hh inc/Wektor.hh
	g++ -c ${CXXFLAGS} -o obj/Macierz2x2.o src/Macierz2x2.cpp	

clean:
	rm -f obj/* ./${APP} core.* core

${TASKDIR}:
	mkdir -p ${TASKDIR}/bin.diablo ${TASKDIR}/bin.panamint

__TARGET__:
	if [ ! "${HOST}" = "diablo" ] && [ ! "${HOST}" = "panamint" ]; then exit 1; fi

export: __TARGET__ ./${APP}  ./${APP}_rozszerzony ${TASKDIR}
	mv ${APP} ${APP}_rozszerzony ${HOME}/edu/po/zad/z${TASKNO}/bin.${HOST}/

help:
	@echo
	@echo " make        - tworzenie i uruchomienie aplikacji"
	@echo " make ext    - tworzenie i uruchomienie aplikacji w wersji rozszerzonej"
	@echo " make clean  - usuniecie produktow kompilacji i konsolidacji"
	@echo " make help   - wyswietla niniejsza informacje"
	@echo
