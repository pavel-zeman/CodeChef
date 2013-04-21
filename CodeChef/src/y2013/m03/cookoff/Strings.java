package y2013.m03.cookoff;

import java.util.Scanner;

public class Strings {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		for(int i=0;i<t;i++) {
			int n = sc.nextInt();
			int k = sc.nextInt();
			String a = sc.next();
			String b = sc.next();
			char [] aa = a.toCharArray();
			char [] bb = b.toCharArray();
			int total = 0;
			for(int ai = 0;ai<n;ai++) {
				for(int bi=0;bi<n;bi++) {
					int maxLength = Math.min(n - ai, n - bi);
					if (maxLength <= k) {
						total += maxLength;
					} else {
						int diffs = 0;
						int index = 0;
						while (index < maxLength) {
							if (aa[ai + index] != bb[bi + index]) {
								if (++diffs > k) break;
							}
							index++;
						}
						total += index;
					}
				}
			}
			System.out.println("" + total);
		}
		sc.close();
	}

}
