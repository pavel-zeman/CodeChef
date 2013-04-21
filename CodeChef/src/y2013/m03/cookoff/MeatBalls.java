package y2013.m03.cookoff;

import java.util.Arrays;
import java.util.Scanner;

public class MeatBalls {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		for(int i=0;i<t;i++) {
			int n = sc.nextInt();
			long m = sc.nextLong();
			long [] data = new long[n];
			for(int j=0;j<n;j++) {
				data[j] = sc.nextLong();
			}
			Arrays.sort(data);
			long total = 0;
			int index = n - 1;
			while (index >= 0 && total < m) {
				total += data[index];
				index--;
			}
			System.out.println("" + (total >= m ? n - index - 1 : -1));
		}
		sc.close();
	}
}
