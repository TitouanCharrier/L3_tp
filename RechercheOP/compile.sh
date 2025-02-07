clear
# Tente de compiler le programme
gcc tp1.c -o tp1 -lgvc -lcgraph

# Vérifie si la commande gcc a réussi
if [ $? -eq 0 ]; then
    # Exécute le programme si la compilation a réussi
    rm graph.png
    ./tp1
    dot -Tpng graph.dot -o graph.png
    feh graph.png
else
    echo "La compilation a échoué."
fi
