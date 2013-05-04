package y2013.m04.challenge;

import java.util.ArrayList;
import java.util.Scanner;

public class FaultTolerance {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int s = sc.nextInt();
		int chunkCount [] = new int[n];
		ArrayList<Integer> servers[] = new ArrayList[s]; 
		for(int i=0;i<n;i++) chunkCount[i] = 0;
		for(int i=0;i<s;i++) servers[i] = new ArrayList<Integer>();
		
		for(int i=0;i<s;i++) {
			int c = sc.nextInt();
			for(int j=0;j<c;j++) {
				int chunk = sc.nextInt();
				servers[i].add(Integer.valueOf(chunk));
				chunkCount[chunk]++;
			}
		}
		sc.close();
		
		int min = s + 1;
		int pos = -1;
		for(int i=0;i<n;i++) {
			if (chunkCount[i] < min) {
				min = chunkCount[i];
				pos = i;
			}
		}
		
		System.out.println("" + min);
		String result = "";
		for(int i=0;i<s;i++) {
			if (servers[i].contains(Integer.valueOf(pos))) {
				result += String.valueOf(i) + " ";
			}
		}
		System.out.println(result);
	}

}
