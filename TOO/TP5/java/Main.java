import java.util.*;

public class Main {

	public static void main(String[] args) {

		char[][] main tableau = {
			{ k, a, y, a, k},
			{ r, a, d, a, r},
			{ s, p, u, r, i, o, u, s}
		};
		boolean pal = false;
		for (int i=0; i<=3; ++i) {
			int size = tableau[i].length; 
			for (int j=0; i<=size/2; ++j) {
				if (tableau[i][j] != tableau[i][size-j]) {
					system.out.print("C'est pas un palindrome");
					pal = false;
					break;
				}
			}
			if (pal) system.out.print("C'est un palidniroejkbrMQLIEUG");
		}

		
	}
}
