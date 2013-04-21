package y2013.m03.challenge;

import java.util.Scanner;

// Prim
public class ChefGame2 {

	private static final int MOD = 747474747;
	private static int[][] points;
	private static long[] distances;
	private static int[] positions;
	private static int totalPos;
	private static int d;
	
	private static long sqr(long input) {
		return input * input;
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
	
	private static long getDistance(int a, int b) {
		long total = 0;
		for(int l=0;l<d;l++) {
			total += sqr(points[a][l] - points[b][l]); 
		}
		return total;
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int t = sc.nextInt();
		for(int i=0;i<t;i++) {
			int n = sc.nextInt();
			d = sc.nextInt();
			points = new int[n][d];
			for(int j=0;j<n;j++) for(int k=0;k<d;k++) points[j][k] = sc.nextInt();
			distances = new long[n];
			positions = new int[n];
			

			int p = 0;
			for(int j=1;j<n;j++) {
				distances[p] = getDistance(j, 0);
				positions[p++] = j;
			}
			totalPos = p;
			
			long start = System.currentTimeMillis();
			// build heap
			for(int j=0;j<totalPos;j++) {
				up(j);
			}
			//System.out.println("Time to build: " + (System.currentTimeMillis() - start));
			
			
			long result = 1;
			
			start = System.currentTimeMillis();
			while (totalPos > 0) {
				if (distances[0] == 0) break;
				
				result *= (distances[0] % MOD);
				result %= MOD;
				
				int vertex = positions[0];
				swap(--totalPos, 0);
				down();
				
				for(int j=0;j<totalPos;j++) {
					long d = getDistance(positions[j], vertex);
					if (d > distances[j]) {
						distances[j] = d;
						up(j);
					}
				}
			}
			System.out.println("Time to destroy: " + (System.currentTimeMillis() - start));
			System.out.println("" + result);
		}
		sc.close();
	}
}