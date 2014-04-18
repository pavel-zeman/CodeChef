// Hackenbush game and the algorithm to calculate game value as described at http://www.geometer.org/mathcircles/hackenbush.pdf (chapter 10) - the game value must be calculated precisely, therfore I use arbitrary precision number (BigInteger)
// http://www.codechef.com/APRIL14/problems/GERALD08
package y2014.m04.challenge;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class ChefAndTreeGame implements Runnable {
	
	private static class Neighbor {
		public int node;
		public boolean red;
		
		public Neighbor(int node, boolean red) {
			this.node = node;
			this.red = red;
		}
	}
	
	private static class Value {
		public BigInteger number;
		public int shift;
		
		public static Value ONE = new Value(BigInteger.ONE, 0);
		
		public Value(BigInteger number, int shift) {
			this.number = number;
			this.shift = shift;
		}
		
		public Value(Value source) {
			this.number = source.number;
			this.shift = source.shift;
		}
		
		private void convertToCommonBase(Value v) {
			if (this.shift > v.shift) {
				v.number = v.number.shiftLeft(this.shift - v.shift);
				v.shift = this.shift;
			} else if (this.shift < v.shift) {
				this.number = this.number.shiftLeft(v.shift - this.shift);
				this.shift = v.shift;
			}
		}
		
		public void add(Value v) {
			convertToCommonBase(v);
			this.number = this.number.add(v.number);
		}

		public void subtract(Value v) {
			convertToCommonBase(v);
			this.number = this.number.subtract(v.number);
		}
		
		public void floor() {
			number = number.shiftRight(shift);
			shift = 0;
		}

		@Override
		public String toString() {
			return "" + shift + ": " + number;
		}

	}
	
	public static Value calcValue(int node, boolean red) {
		used[node] = true;
		Value total = new Value(BigInteger.ZERO, 0);
		for(Neighbor item : neighbor[node]) {
			if (!used[item.node]) {
				total.add(calcValue(item.node, item.red));
			}
		}
		
		if (red) {
			if (total.number.signum() == -1) {
				total.subtract(new Value(Value.ONE));
				return total;
			} else {
				Value temp = new Value(total);
				temp.add(new Value(Value.ONE));
				temp.floor();
				temp.add(new Value(Value.ONE));
				int s = temp.number.intValue();
				total.subtract(temp);
				total.shift += s - 1;
				return total;
			}
		} else {
			if (total.number.signum() == 1) {
				total.add(new Value(Value.ONE));
				return total;
			} else {
				Value temp = new Value(total);
				temp.number = temp.number.abs();
				temp.add(new Value(Value.ONE));
				temp.floor();
				temp.add(new Value(Value.ONE));
				int s = temp.number.intValue();
				total.add(temp);
				total.shift += s - 1;
				return total;
			}
		}
	}

	private static List<Neighbor> neighbor[];
	private static boolean used[];
	
	public static void main(String[] args) throws InterruptedException {
		// must be run in thread to be able to set its stack size (the default stack size is not sufficient)
		Thread t = new Thread(Thread.currentThread().getThreadGroup(), new ChefAndTreeGame(), "Test", 30000000);
		t.start();
		t.join();
	}

	@Override
	@SuppressWarnings("unchecked")
	public void run() {
		try {
			BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
			int t = Integer.parseInt(reader.readLine());
			for(int tt = 0;tt<t;tt++) {
				int n = Integer.parseInt(reader.readLine());
				neighbor = new List[n];
				used = new boolean[n];
				for (int i=0;i<n;i++) {
					used[i] = false;
					neighbor[i] = new ArrayList<ChefAndTreeGame.Neighbor>();
				}
				used[0] = true;
				
				n--;
				for(int i=0;i<n;i++) {
					String line = reader.readLine();
					StringTokenizer tokenizer = new StringTokenizer(line, " ");
					int u = Integer.parseInt(tokenizer.nextToken()) - 1;
					int v = Integer.parseInt(tokenizer.nextToken()) - 1;
					int c = Integer.parseInt(tokenizer.nextToken());
					neighbor[u].add(new Neighbor(v, c == 1));
					neighbor[v].add(new Neighbor(u, c == 1));
				}
				Value total = new Value(BigInteger.ZERO, 0);
				for (Neighbor item : neighbor[0]) {
					total.add(calcValue(item.node, item.red));
				}
				switch (total.number.signum()) {
					case 0:
						System.out.println("Ksen Chef");
						break;
					case -1:
						System.out.println("Ksen Ksen");
						break;
					case 1:
						System.out.println("Chef Chef");
						break;
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}
