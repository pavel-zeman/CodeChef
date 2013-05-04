package y2013.m04.cookoff;

import java.util.Scanner;

public class StringsFaster {

	private static int n, k, total;
	private static char aa[], bb[];
	
	private static void check(int ai, int bi) {
		int start = 0;
		int index = 0;
		int maxLength = Math.min(n - ai, n - bi);
		int diffs = 0;
		int lastIndex = 0;
		while (index < maxLength) {
			if (aa[ai + index] != bb[bi + index]) {
				diffs++;
				if (diffs > k) {
					int i2 = index - start;
					int i1 = lastIndex - start + 1;
					int add = (i1 + i2) * (i2 - i1 + 1) / 2; 
					total += add;
					//System.out.println("Adding: " + add);

					lastIndex = index;
					while (aa[ai + start] == bb[bi + start]) start++;
					diffs--;
					start++;
				}
			}
			index++;
		}
		int i2 = index - start;
		int i1 = lastIndex - start + 1;
		int add = (i1 + i2) * (i2 - i1 + 1) / 2;
		total += add;
		//System.out.println("Adding: " + add);
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		for(int i=0;i<t;i++) {
			n = sc.nextInt();
			k = sc.nextInt();
			String a = sc.next();
			String b = sc.next();
			aa = a.toCharArray();
			bb = b.toCharArray();
			total = 0;
			for(int j=0;j<n;j++) check(0, j);
			for(int j=1;j<n;j++) check(j, 0);
			
			System.out.println("" + total);
		}
		sc.close();
	}

}
