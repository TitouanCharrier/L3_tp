clear

rm *.dot
rm graph.png 
mv main .bin_backup

gcc -c ./src/g1.c ./src/g0.c ./src/test.c ./src/force.c ./src/tools.c main.c -lm 
gcc -o main g1.o g0.o test.o force.o tools.o main.o -lm
rm *.o
echo "Compilation terminée"

time ./main
dot -Tpng graph_greedy0.dot -o ./output/graph_greedy0.png
dot -Tpng graph_greedy1.dot -o ./output/graph_greedy1.png
feh ./output/*.png
