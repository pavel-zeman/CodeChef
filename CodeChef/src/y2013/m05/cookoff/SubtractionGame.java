package y2013.m05.cookoff;

import java.util.Scanner;

public class SubtractionGame {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int t = sc.nextInt();
		
		for(int tt = 0;tt<t;tt++) {
			int n = sc.nextInt();
			if (n == 1) {
				System.out.println(sc.nextInt());
			} else {
				int mod = sc.nextInt();
				for(int i=1;i<n;i++) {
					int big = sc.nextInt();
					while (mod != 0) {
						int temp = big % mod;
						big = mod;
						mod = temp;
					}
					mod = big;
				}
				System.out.println("" + mod);
			}
		}
		sc.close();
	}

}
