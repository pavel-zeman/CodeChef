package y2013.m03.cookoff;

import java.util.Scanner;

public class MeatBalls2 {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		for(int i=0;i<t;i++) {
			int n = sc.nextInt();
			int k = sc.nextInt();
			StringBuilder result = new StringBuilder();
			if (k <= n/2) {
				for(int j=0;j<k;j++) {
					if (result.length() > 0) result.append(' ');
					result.append(j * 2 + 2);
				}
			} else if (k == 1) {
				result.append("1");
			} else {
				result.append("-1");
			}
			System.out.println(result.toString());
		}
		sc.close();
	}

}
