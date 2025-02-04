
public class Main {

    public static void main(String[] args) {

        System.out.print("Entrée dans le Main\n");
        Insee test1 = new Insee(1630125388055L, 29);
        Insee test2 = new Insee(16301253880552L, 64);
        Insee test3 = new Insee(12345, 12345);

        if (test1.check()) System.out.print("Test succesfull\n");
        else System.out.print("Test failed\n");
        if (test2.check()) System.out.print("Test succesfull\n");
        else System.out.print("Test failed\n");
        if (test3.check()) System.out.print("Test succesfull\n");
        else System.out.print("Test failed\n");

    }
}

