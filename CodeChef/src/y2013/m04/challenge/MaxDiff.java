package y2013.m04.challenge;

import java.util.Arrays;
import java.util.Scanner;

public class MaxDiff {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		for(int i=0;i<t;i++) {
			int n = sc.nextInt();
			int k = sc.nextInt();
			int [] w = new int[n];
			for(int j=0;j<n;j++) w[j] = sc.nextInt();
			if (k > n - k) k = n - k;
			Arrays.sort(w);
			int s1 = 0, s2 = 0;
			for(int j=0;j<k;j++) s1 += w[j];
			for(int j=k;j<n;j++) s2 += w[j];
			System.out.println("" + (s2 - s1));
		}
		sc.close();
	}

}
