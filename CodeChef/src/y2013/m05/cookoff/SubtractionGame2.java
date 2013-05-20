package y2013.m05.cookoff;

import java.util.Scanner;

public class SubtractionGame2 {

	private static int [] primes = {2, 3, 5, 7, 11, 13, 17, 19,     23,     29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};
	
	private static int gcd(int big, int small) {
		while (small != 0) {
			int temp = big % small;
			big = small;
			small = temp;
		}
		return big;
	}
	
	private static int n;
	private static int []a = new int[100];
	
	private static boolean test(int first, int level, int product) {
		if (level == 0) return product == 1;
		for(int i=first;i<n;i++) {
			int g = gcd(a[i], product);
			if (g < product) {
				if (test(i + 1, level - 1, g)) return true;
			}
		}
		return false;
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		
		for(int tt = 0;tt<t;tt++) {
			n = sc.nextInt();
			for(int i=0;i<n;i++) {
				a[i] = sc.nextInt();
			}
			long total = 0;
			for(int i=0;i<n;i++) {
				int gcdres = a[i];
				for(int j=i+1;j<n;j++) {
					gcdres = gcd(gcdres, a[j]);
				}
				//System.out.println("" + i + " " + gcdres);
				if (gcdres > 1) break;
				if (a[i] == 1) {
					total += (1L << (n - i - 1));
				} else {
					int product = 1;
					for(int prime: primes) {
						if (a[i] % prime == 0) product *= prime;
					}
					
					for(int j=1;j<10;j++) {
						if (test(i + 1, j, product)) {
							total += (1L << (n - i - j - 1));
							System.out.println("A:" + total);
							break;
						}
					}
				}
				
			}
			System.out.println("" + total);
		}
		sc.close();
	}

}
