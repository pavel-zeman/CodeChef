package y2013.m03.challenge;

public class KingdomGenerator {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		System.out.println("1");
		int size = 3000;
		System.out.println("" + size + " " + (size * (size - 1) / 2) + " 1000");
		for(int i=0;i<size;i++)
			for(int j=i+1;j<size;j++)
				System.out.println("" + i + " " + j);
	}

}
