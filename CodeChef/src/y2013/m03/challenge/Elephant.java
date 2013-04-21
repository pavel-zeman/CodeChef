package y2013.m03.challenge;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Scanner;

public class Elephant {

	private static class Song implements Comparable<Song> {
		public Integer b;
		public int l;

		@Override
		public int compareTo(Song o) {
			return this.l - o.l;
		}
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		for(int i=0;i<t;i++) {
			int n = sc.nextInt();
			Song [] songs = new Song[n];
			for(int j=0;j<n;j++) {
				Song s = new Song();
				s.b = Integer.valueOf(sc.nextInt());
				s.l = sc.nextInt();
				songs[j] = s;
			}
			Arrays.sort(songs);
			
			HashSet<Integer> set = new HashSet<Integer>();
			int totalBands = 0;
			long totalValue = 0;
			long buffer = 0;
			for(int j=0;j<n;j++) {
				Song song = songs[j];
				int l = song.l;
				int newBands = 0;
				int chainLength = 0;
				while (j < n && songs[j].l == l) {
					if (!set.contains(songs[j].b)) {
						newBands++;
						set.add(songs[j].b);
					}
					chainLength++;
					j++;
				}
				j--;
				//System.out.println("New bands: " + newBands + " Chaing:" + chainLength);
				for(int k=0;k<newBands;k++) {
					totalBands++;
					totalValue += ((long)l) * totalBands;
					chainLength--;
				}
				buffer += ((long)chainLength) * l;
			}
			totalValue += buffer * totalBands;
			System.out.println("" + totalValue);
		}
		sc.close();
	}
}
