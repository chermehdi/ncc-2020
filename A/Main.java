import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.HashSet;
import java.util.InputMismatchException;
import java.io.IOException;
import java.io.InputStream;

public class Main {
  public static void main(String[] args) {
    InputStream inputStream = System.in;
    OutputStream outputStream = System.out;
    InputReader in = new InputReader(inputStream);
    PrintWriter out = new PrintWriter(outputStream);
    Ncc20hicham solver = new Ncc20hicham();
    solver.solve(1, in, out);
    out.close();
  }

  static class Ncc20hicham {
    public final void solve(int testNumber, InputReader in, PrintWriter out) {
      int x = in.nextInt();
      int a = in.nextInt();
      int b = in.nextInt();
      char[] whitelist = in.nextCharArray();
      HashSet<Integer> good = new HashSet<>();
      for (char c : whitelist) {
        good.add(c - '0');
      }

      int ans = 0;
      for (int i = x; i <= b; i += x) {
        if (i >= a && isOk(good, i)) {
          ++ans;
        }
      }
      out.println(ans);
    }

    private boolean isOk(HashSet<Integer> good, long v) {
      while (v > 0) {
        int d = (int) (v % 10);
        if (!good.contains(d)) {
          return false;
        }
        v /= 10;
      }
      return true;
    }
  }

  static final class InputReader {
    private final InputStream stream;
    private final byte[] buf = new byte[1 << 16];
    private int curChar;
    private int numChars;

    public InputReader() {
      this.stream = System.in;
    }

    public InputReader(final InputStream stream) {
      this.stream = stream;
    }

    private final int read() {
      if (this.numChars == -1) {
        throw new UnknownError();
      } else {
        if (this.curChar >= this.numChars) {
          this.curChar = 0;

          try {
            this.numChars = this.stream.read(this.buf);
          } catch (IOException ex) {
            throw new InputMismatchException();
          }

          if (this.numChars <= 0) {
            return -1;
          }
        }

        return this.buf[this.curChar++];
      }
    }

    public final int nextInt() {
      int c;
      for (c = this.read(); isSpaceChar(c); c = this.read()) {}

      byte sgn = 1;
      if (c == 45) { // 45 == '-'
        sgn = -1;
        c = this.read();
      }

      int res = 0;

      while (c >= 48 && c <= 57) { // 48 == '0', 57 == '9'
        res *= 10;
        res += c - 48; // 48 == '0'
        c = this.read();
        if (isSpaceChar(c)) {
          return res * sgn;
        }
      }

      throw new InputMismatchException();
    }

    public final String next() {
      int c;
      while (isSpaceChar(c = this.read())) {}

      StringBuilder result = new StringBuilder();
      result.appendCodePoint(c);

      while (!isSpaceChar(c = this.read())) {
        result.appendCodePoint(c);
      }

      return result.toString();
    }

    private static final boolean isSpaceChar(final int c) {
      return c == 32 || c == 10 || c == 13 || c == 9
          || c == -1; // 32 == ' ', 10 == '\n', 13 == '\r', 9 == '\t'
    }

    public final char[] nextCharArray() {
      return next().toCharArray();
    }
  }
}
