clear

rm graph.dot
rm graph.png 
mv main .bin_backup

gcc -c ./src/g0.c ./src/test.c ./src/force.c ./src/tools.c main.c -lm 
gcc -o main g0.o test.o force.o tools.o main.o -lm
rm *.o
echo "Compilation terminée"

time ./main
dot -Tpng graph.dot -o ./output/graph.png
feh ./output/graph.png
