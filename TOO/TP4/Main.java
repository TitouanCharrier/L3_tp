import java.util.HashMap;
import java.util.Map;
import java.util.*;

public class Main {
    public static void main(String[] args) {

    // Création d'une HashMap (non triée)
      Map<Integer, Integer> treemap = new TreeMap<Integer, Integer>(Collections.reverseOrder());
      treemap.put(0, 35);
      treemap.put(4, 20);
      treemap.put(12, 25);
      treemap.put(25, 30);
      
      x = 5

      for (int i=0; i<= treemap.size(); ++i) {
        System.out.println("TreeMap : " + i + " " + treemap.get(i));
        
      }
    
     
    }


}
