package com.franckbarbier.bar_code;

enum Result {
    Correct,
    Incorrect,
    Invalid_format
}

public class Bar_code {

    private final java.util.ArrayList<Integer> _bar_code = new java.util.ArrayList<>();
    public final Result correct;
    private final String buff;


    Bar_code(final String bar_code) throws NumberFormatException {
        for (String s : bar_code.split("")) { // 'bar_code' est découpé en éléments...
            try {
                int element = Integer.valueOf(s); // Conversion en entier pour les calculs...
                _bar_code.add(element);
            } catch (NumberFormatException nfe) {
                correct = Result.Invalid_format;
                throw nfe;
            }
        }
        correct = _alternative_check_sum() ? Result.Correct : Result.Incorrect;
        buff = bar_code;
    }

    private boolean _check_sum() { // Méthode de calcul du "check sum" :

        int odd = 0;  
        int even = 0;  
        int sum = 0;

        for (int i = 0; i < _bar_code.size()-1; i+=2) {
            System.out.println(" Rang impair Index " + i + ": " + _bar_code.get(i));
            odd += _bar_code.get(i);
        }

        for (int i = 1; i < _bar_code.size(); i+=2) {
            System.out.println(" Rang pair Index " + i + ": " + _bar_code.get(i));
            even += _bar_code.get(i);
        }

        sum = (3 * even + odd) %10;
        if (sum != 0) sum = 10 - sum;
        System.out.println(" Rang pair Index " + sum + " check sum " + _bar_code.get(12));


        if (sum == _bar_code.get(12)) return true;
        else return false;
        
        // https://barcode-coder.com/fr/specification-ean-13-102.html
        // Example: 2 1 0 9 8 7 6 5 4 3 2 1 0
        // Step 1: ajouter les chiffres de rang impair en partant de la droite (ne pas compter le dernier chiffre de contrôle, i.e., '0')
        // Step 2: ajouter au résultat trois fois la somme des chiffres de rang pair toujours en partant de la droite
        // Check sum: (10 - [ (3 * "impairs" + "pairs") modulo 10 ]) modulo 10
    }

    private boolean _alternative_check_sum() { // Autre méthode de calcul du "check sum" :
        // Autre méthode : https://fr.wikipedia.org/wiki/EAN_13
        int sum = 0;
        boolean eo = false;
        for (int i = 0; i < _bar_code.size()-1; i+=1) {
            System.out.println(" Index " + i + ": " + _bar_code.get(i));
            if (eo) {
             sum += _bar_code.get(i)*3;
             eo = false;
            }
            else {
             sum += _bar_code.get(i);
             eo = true;
            }
            
        }
        
        sum = sum % 10;
        if (sum != 0) sum = 10 - sum;
        System.out.println(" Rang pair Index " + sum + " check sum " + _bar_code.get(12));


        return (sum == _bar_code.get(12));

    }

    @Override
public String toString() {
        return B=buff; // A remplacer
    }
}
