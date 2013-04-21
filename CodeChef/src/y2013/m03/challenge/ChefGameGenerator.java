package y2013.m03.challenge;

import java.util.Random;

public class ChefGameGenerator {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		int size = 6666;
		System.out.println("1 " + size + " 5");
		Random r = new Random();
		for(int i=0;i<size;i++) {
			String res = "";
			for(int j=0;j<5;j++) res += " " + (r.nextInt(200000000) - 100000000);
			System.out.println(res);
		}
		
		/*System.out.println("1 " + size + " 1");
		Random r = new Random();
		for(int i=0;i<size;i++) {
			System.out.println("-" + i);
		}*/

	}

}
