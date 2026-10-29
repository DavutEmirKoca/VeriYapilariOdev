hepsi: derle calistir

derle:
	g++ -I ./include/ -o ./lib/Node.o -c ./src/Node.cpp
	g++ -I ./include/ -o ./lib/Matris.o -c ./src/Matris.cpp
	g++ -I ./include/ -o ./lib/MatrisList.o -c ./src/MatrisList.cpp
	g++ -I ./include/ -o ./bin/main ./lib/Node.o ./lib/Matris.o ./lib/MatrisList.o ./src/main.cpp
	
calistir:
	./bin/main