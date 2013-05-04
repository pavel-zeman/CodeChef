package y2013.m04.challenge;

import java.io.BufferedInputStream;
import java.util.Scanner;

public class Levy {

	private static int MAX = 10002;
	
	public static void main(String[] args) {
		boolean primes[] = new boolean[MAX];
		int primeList[] = new int[MAX];
		int totals[] = new int[MAX];
		int totalPrimes = 0;
		primes[0] = primes[1] = false;
		for(int i=2;i<MAX;i++) primes[i] = true;
		for(int i=2;i<MAX;i++) {
			if (primes[i]) {
				primeList[totalPrimes++] = i;
				for(int j = i + i;j<MAX;j += i) primes[j] = false;
			}
		}
		for(int i=0;i<MAX;i++) totals[i] = 0;
		for(int i=0;i<totalPrimes;i++) {
			for(int j=0;j < totalPrimes && 2 * primeList[i] + primeList[j] < MAX;j++) {
				totals[2 * primeList[i] + primeList[j]]++;
			}
		}
			
		
		Scanner sc = new Scanner(new BufferedInputStream(System.in));
		int t = sc.nextInt();
		for(int i=0;i<t;i++) {
			int n = sc.nextInt();
			System.out.println("" + totals[n]);
		}
		sc.close();
	}

}
