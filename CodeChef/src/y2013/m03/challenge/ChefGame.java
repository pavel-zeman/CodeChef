package y2013.m03.challenge;

import java.util.Scanner;

// Kruskal
public class ChefGame {

	private static final int MOD = 747474747;
	private static int[][] points;
	private static long[] distances;
	private static int[] positions;
	private static int totalPos;
	
	private static int[] set;
	private static int[] depths;
	
	private static long sqr(long input) {
		return input * input;
	}
	
	private static int root(int a) {
		while (set[a] != -1) a = set[a];
		return a;
	}
	
	private static boolean check(int a, int b) {
		return root(a) != root(b);
	}
	
	private static void join(int a, int b) {
		a = root(a);
		b = root(b);
		if (depths[a] > depths[b]) {
			set[b] = a;
		} else {
			set[a] = b;
			if (depths[a] == depths[b]) {
				depths[b]++;
			}
		}
	}
	
	private static void swap(int a, int b) {
		int temp1 = positions[a];
		positions[a] = positions[b];
		positions[b] = temp1;
		long temp2 = distances[a];
		distances[a] = distances[b];
		distances[b] = temp2;
	}
	
	private static int parent(int a) {
		return (a - 1) >> 1; 
	}
	
	private static int child(int a) {
		return (a << 1) + 1;
	}
	
	private static void up(int a) {
		while (a > 0 && distances[a] > distances[parent(a)]) {
			swap(a, parent(a));
			a = parent(a);
		}
	}
	
	private static void down() {
		int origPosition = positions[0];
		long origDistance = distances[0];
		int temp = 0;
		int c = child(temp);
		while (c < totalPos && origDistance < distances[c] || c + 1 < totalPos && origDistance < distances[c + 1]) {
			if (c + 1 < totalPos && distances[c + 1] > distances[c]) c++;
			positions[temp] = positions[c];
			distances[temp] = distances[c];
			temp = c;
			c = child(temp);
		}
		positions[temp] = origPosition;
		distances[temp] = origDistance;
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int t = sc.nextInt();
		for(int i=0;i<t;i++) {
			int n = sc.nextInt();
			int d = sc.nextInt();
			points = new int[n][d];
			for(int j=0;j<n;j++) for(int k=0;k<d;k++) points[j][k] = sc.nextInt();
			distances = new long[n * n / 2];
			positions = new int[n * n / 2];
			
			int pos = 0;
			for(int j=0;j<n;j++) {
				for(int k=j+1;k<n;k++) {
					long total = 0;
					for(int l=0;l<d;l++) {
						total += sqr(points[j][l] - points[k][l]); 
					}
					distances[pos] = total;
					positions[pos++] = j | (k << 16);
				}
			}
			totalPos = pos;
			
			long start = System.currentTimeMillis();
			// build heap
			for(int j=0;j<totalPos;j++) {
				up(j);
			}
			//sort(0, totalPos - 1);
			System.out.println("Time to build: " + (System.currentTimeMillis() - start));
			
			
			long result = 1;
			set = new int[n];
			depths = new int[n];
			for(int c=0;c<n;c++) {
				set[c] = -1;
				depths[c] = 0;
			}
			
			start = System.currentTimeMillis();
			if (n > 1 && distances[0] > 0) {
				for(int c=0;c<n-1;c++) {
					while (true) { 
						int a = positions[0] & ((1 << 14) - 1);
						int b = positions[0] >> 16;
						long value = distances[0];
						
						swap(--totalPos, 0);
						down();
						
						if (check(a, b)) {
							result *= (value % MOD);
							result %= MOD;
							join(a, b);
							break;
						}
					}
				}
			}
			//System.out.println("Time to destroy: " + (System.currentTimeMillis() - start));
			System.out.println("" + result);
		}
		sc.close();
	}
}