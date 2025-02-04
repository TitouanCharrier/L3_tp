import java.util.Random;
import java.util.ArrayList;

public class Main {

    static Random rand = new Random();
    static int max = 49;

    public static void main(String[] args) {
      ArrayList<Integer> main_list = new ArrayList<>();
      for (int i=0; i<=48; ++i) {
        main_list.add(i+1);
      }
      //System.out.print(main_list);
      int[][] number_list = new int[8][6]; 

      for (int i=0; i<8; ++i) {
        for (int j=0; j<6; ++j) {
          int index = rand.nextInt(max);
          number_list[i][j] = main_list.get(index);
          main_list.remove(index);
          max --;
          System.out.print(number_list[i][j] + " \t ");
        }
        System.out.print("\n");
      }
      System.out.print( "numéro manquant " + main_list + "\n");
    }
}
