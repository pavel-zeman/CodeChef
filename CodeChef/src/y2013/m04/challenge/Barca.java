package y2013.m04.challenge;

import java.util.Scanner;

public class Barca {

	private static final int MOD = 1000000007;
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		for(int i=0;i<t;i++) {
			int n = sc.nextInt();
			int k = sc.nextInt();
			
			long prev = 0;
			long others = k;
			for(int current = 1; current < n - 1; current++) {
				long temp = prev;
				prev = others;
				others = temp * k + others * (k - 1);
				others %= MOD;
			}
			System.out.println("" + others);
		}
		sc.close();

	}

}
