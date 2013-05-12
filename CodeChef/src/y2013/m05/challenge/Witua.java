package y2013.m05.challenge;

import java.math.BigInteger;
import java.util.Scanner;

public class Witua {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		BigInteger one = new BigInteger("1");
		BigInteger two = new BigInteger("2");
		int t= sc.nextInt();
		for(int i=0;i<t;i++) {
			String n = sc.next();
			BigInteger b = new BigInteger(n);
			
			// make sure it's odd
			if (!b.testBit(0) && !b.equals(two)) {
				b = b.subtract(one);
			}
			while (!b.isProbablePrime(5)) {
				b = b.subtract(two);
			}
			System.out.println(b);
		}
	}

}
