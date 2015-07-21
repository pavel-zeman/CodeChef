// Thanks to the number of sets (10^(10^(10^(10^(10^10))))), this is a sum of an infinite geometric sequence. To provide sufficient precision, the BigDecimal data type is used.
// http://www.codechef.com/JULY15/problems/SEAGM2
package y2015.m07.challenge;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.StringTokenizer;

/**
 * @author Pavel Zeman
 */
public class SerejaAndGame2 {

  public static void main(String [] args) throws IOException {
    BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    String line = reader.readLine();
    int t = Integer.parseInt(line);
    for(int tt = 0; tt < t; tt++) {
      StringTokenizer tokenizer = new StringTokenizer(reader.readLine());
      int n = Integer.parseInt(tokenizer.nextToken());
      int m = Integer.parseInt(tokenizer.nextToken());
      BigDecimal pwin[] = new BigDecimal[n];
      BigDecimal pWinTotal = BigDecimal.ZERO;
      for(int i=0;i<n;i++) {
        tokenizer = new StringTokenizer(reader.readLine());
        BigDecimal win = BigDecimal.ONE;
        for(int j=0;j<m;j++) {
          win = win.multiply(new BigDecimal(tokenizer.nextToken()));
        }
        pwin[i] = win;
        pWinTotal = pWinTotal.add(win);
      }
      if (pWinTotal.compareTo(BigDecimal.ZERO) == 0) {
        System.out.println("0.000000");
      } else {
        BigDecimal result = pwin[0].divide(pWinTotal, 6, RoundingMode.HALF_UP);
        System.out.println(result);
      }
    }
  }
}
