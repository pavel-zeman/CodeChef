// It is only necessary to count up to sqrt(n). 
// http://www.codechef.com/SEPT14/problems/FLOORI4
package y2014.m09.challenge;

import java.math.BigInteger;
import java.util.Scanner;

public class Flooring {

	private static int m;
	private static long n;
	
	private static BigInteger mm;
	
	private static final BigInteger SIX = BigInteger.valueOf(6);
	private static final BigInteger FIFTEEN = BigInteger.valueOf(15);
	private static final BigInteger THIRTY = BigInteger.valueOf(30);
	
	private static final int MAX_N = 200001;
	
	private static BigInteger cache [];
	
	private static long pow4(long a) {
		long result = a * a % m;
		return result * result % m;
	}
	
	// calculates sum of i^4 from a to b, which is (-6 a^5+15 a^4-10 a^3+a+6 b^5+15 b^4+10 b^3-b) / 30
	private static long pow5(long a, long b) {
		if (a > b) return 0;
		if (a < MAX_N && b < MAX_N && a > 0) {
			BigInteger temp = cache[(int)b].subtract(cache[(int)a - 1]);
			return temp.mod(mm).longValue();
		}
		BigInteger result = BigInteger.ZERO;
		BigInteger aa = BigInteger.valueOf(a);
		BigInteger temp = aa;
		result = result.add(aa);
		temp = aa.multiply(aa).multiply(aa);
		result = result.subtract(BigInteger.TEN.multiply(temp));
		
		temp = temp.multiply(aa);
		result = result.add(FIFTEEN.multiply(temp));

		temp = temp.multiply(aa);
		result = result.subtract(SIX.multiply(temp));
		
		BigInteger bb = BigInteger.valueOf(b);
		temp = bb;
		result = result.subtract(bb);
		temp = bb.multiply(bb).multiply(bb);
		result = result.add(BigInteger.TEN.multiply(temp));

		temp = temp.multiply(bb);
		result = result.add(FIFTEEN.multiply(temp));

		temp = temp.multiply(bb);
		result = result.add(SIX.multiply(temp));
		
		result = result.divide(THIRTY).mod(mm);
		
		return result.longValue();
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		//long ss = System.currentTimeMillis();
		cache = new BigInteger[MAX_N];
		cache[0] = BigInteger.ZERO;
		for (int i=1;i<MAX_N;i++) {
			BigInteger aa = BigInteger.valueOf(i);
			aa = aa.multiply(aa);
			cache[i] = cache[i - 1].add(aa.multiply(aa));
		}

		for (int tt = 0; tt < t; tt++) {
			n = sc.nextLong();
			m = sc.nextInt();
			mm = BigInteger.valueOf(m);
			
			long result = 0;
			long c = 1;
			while (c * c < n) {
				result = (result + pow4(c) * (n / c)) % m;
				long start = n / (c + 1) + 1;
				if (start <= c) start = c + 1;
				long end = n / c;
				result = (result + c * pow5(start, end)) % m;
				c++;
			}
			if (c * c == n) result = (result + pow4(c) * (n / c)) % m;
			System.out.println("" + result);
		}
		//System.out.println("AA: " + (System.currentTimeMillis() - ss));
	}
}
