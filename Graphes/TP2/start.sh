clear

# Tente de compiler le programme
gcc main.c -o main -lgvc -lcgraph -lm

# Vérifie si la commande gcc a réussi
if [ $? -eq 0 ]; then
    # Exécute le programme si la compilation a réussi
    ./main
    #feh graph.png &
else
    echo "La compilation a échoué."
fi
