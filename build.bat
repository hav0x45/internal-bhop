cd cs2-dumper
cs2-dumper.exe -o ../include/offsets/ -p cs2.exe -f hpp -v -n
cd ..
g++ -o ./build/bhops.dll bhops.cpp -I./include/ -DBUILD_LIB -static --std=c++20 -mdll