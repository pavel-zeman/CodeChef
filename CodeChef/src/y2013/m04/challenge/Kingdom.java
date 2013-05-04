package y2013.m04.challenge;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class Kingdom {

	
	private static ArrayList<Integer> edges[];
	private static int f[];
	private static int fStar[];
	private static int counter;
	private static boolean processing[];
	private static boolean processed[];
	private static boolean cuts[];
	
	private static void dfs(int vertex) {
		int t = 0;
		fStar[vertex] = f[vertex] = ++counter;
		processing[vertex] = true;
		for(Integer neighbour : edges[vertex]) {
			if (!processing[neighbour]) {
				if (++t > 1 && vertex == 0) {
					cuts[vertex] = true;
				}
				dfs(neighbour);
				fStar[vertex] = Math.min(fStar[vertex], fStar[neighbour]);
				if (fStar[neighbour] >= f[vertex] && vertex != 0) cuts[vertex] = true;
			} else { 
				fStar[vertex] = Math.min(fStar[vertex], f[neighbour]);
			}
		}
		processed[vertex] = true;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader bis = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(bis.readLine());
		
		for(int i=0;i<t;i++) {
			String line = bis.readLine();
			StringTokenizer tokenizer = new StringTokenizer(line, " ");
			int n = Integer.parseInt(tokenizer.nextToken());
			int m = Integer.parseInt(tokenizer.nextToken());
			int k = Integer.parseInt(tokenizer.nextToken());
			
			long start = System.currentTimeMillis();
			edges = new ArrayList[n];
			for(int j=0;j<n;j++) edges[j] = new ArrayList<Integer>(n * 2);
			for(int j=0;j<n;j++) edges[j].ensureCapacity(3000);
			
			for(int j=0;j<m;j++) {
				line = bis.readLine();
				int pos = line.indexOf(' ');
				Integer a = Integer.valueOf(line.substring(0, pos));
				Integer b = Integer.valueOf(line.substring(pos + 1));
				edges[a.intValue()].add(b);
				edges[b.intValue()].add(a);
			}
			//System.out.println("Time to read: " + (System.currentTimeMillis() - start));
			counter = 0;
			
			
			f = new int[n];
			fStar = new int[n];
			processing = new boolean[n];
			processed = new boolean[n];
			cuts = new boolean[n];
			for(int j=0;j<n;j++) cuts[j] = processing[j] = processed[j] = false;
			
			dfs(0);
			
			int totalCuts = 0;
			for(int j=0;j<n;j++) {
				if (cuts[j]) {
					//System.out.println("Cut: " + j);
					totalCuts++;
				}
			}
			System.out.println("" + (totalCuts * k));
		}
		//sc.close();
	}

}
