#!/bin/bash

##Borro el directorio si ya existiera
if [ -d "./bin" ];
	then rm -r ./bin;
fi
##Creo los directorios para el binario y las bibliotecas
mkdir ./bin/
mkdir ./bin/lib/

##compilo el binario
g++ -Wall -std=c++11 -ldl -I./include/ application.cpp -o ./bin/application.exe

##compilo las bibliotecas
g++ -shared -Wall -std=c++11 -fPIC -I./lib/application/include/ ./lib/application/libapplication.cpp -o ./bin/lib/libapplication.so

g++ -shared -Wall -std=c++11 -fPIC -I./lib/httprequesthandler/include/ ./lib/httprequesthandler/libhttprequesthandler.cpp -o ./bin/lib/librequesthandler.so

g++ -shared -Wall -std=c++11 -fPIC -I./lib/potentialfunction/include/ ./lib/potentialfunction/libpotentialfunction.cpp -o ./bin/lib/libpotential.so
g++ -shared -Wall -std=c++11 -fPIC -I./lib/quadraticfunction/include/ ./lib/quadraticfunction/libquadraticfunction.cpp -o ./bin/lib/libquadratic.so 
g++ -shared -Wall -std=c++11 -fPIC -I./lib/sinusoidalfunction/include/ ./lib/sinusoidalfunction/libsinusoidalfunction.cpp -o ./bin/lib/libsinusoidal.so
g++ -shared -Wall -std=c++11 -fPIC -I./lib/trapezoidsolver/include/ ./lib/trapezoidsolver/libtrapezoidsolver.cpp -o ./bin/lib/libtrapezoidsolver.so
g++ -shared -Wall -std=c++11 -fPIC -I./lib/simpsonsolver/include/ ./lib/simpsonsolver/libsimpsonsolver.cpp -o ./bin/lib/libsimpsonsolver.so

##copio la biblioteca fltk componente que yo no compilo
cp ./resources/index.html ./bin/
cp ./resources/favicon.ico ./bin/
cp ./resources/LICENSE ./bin/

##otorgo permisos de escritura a los ejecutables
chmod +x ./bin/application.exe

##creo un readme para entender como probar la aplicación
echo -e "Esto es un Test de una integral de una función cuadrática:" > ./bin/readme.txt
echo -e "\t ingresar tipo de resolvedor: trapezoid" >> ./bin/readme.txt
echo -e "\t ingresar tipo de funcion: quadratic" >> ./bin/readme.txt
echo -e "\t ingresar x0: -2" >> ./bin/readme.txt
echo -e "\t ingresar x1: 2" >> ./bin/readme.txt
echo -e "\t ingresar n: 100" >> ./bin/readme.txt
echo -e "\t ingresar a: 1" >> ./bin/readme.txt
echo -e "\t ingresar b: -2" >> ./bin/readme.txt
echo -e "\t ingresar c: 0 \n" >> ./bin/readme.txt
echo -e "\t resultado: 8" >> ./bin/readme.txt
