import java.util.*;
import java.io.*;
import java.math.*;
 
public class Main {
    public static void main(String[] args) throws IOException {
        PrintWriter out = new PrintWriter(System.out);
        //Scanner sc = new Scanner();
        Reader in = new Reader();
        Main solver = new Main();
        solver.solve(out, in);
        out.flush();
        out.close();
 
    }
 
    static int INF = (int)1e9;
    static int maxn = 2*(int)1e5+5;
    static int mod = 998244353 ;
    static int n,m,t,q,d,k;
    
    static int[][] arr;
    static PriorityQueue<Node> pq;
    
    void solve(PrintWriter out, Reader in) throws IOException{
        n = in.nextInt();
        k = in.nextInt();
        
        arr = new int[n][];
        for (int i = 0; i < n; i++) {
            m = in.nextInt();
            arr[i] = new int[m];
            for (int j = 0; j < m; j++) {
                arr[i][j] = in.nextInt();
            }
        }
        
        pq = new PriorityQueue<Node>();
        for (int i = 0; i < n; i++) {
            pq.add(new Node(arr[i][0], i, 0));
        }
        
        long ans = 0;
        Node e;
        while (k --> 0) {
            e = pq.remove();
            update(e);
            ans += e.val;
        }
        
        out.println(ans);
    }
    
    //<>
    
    static void update(Node e) {
        if (e.j+1 < arr[e.i].length) {
            pq.add(new Node(arr[e.i][e.j+1], e.i, e.j+1));
        }
    }
    
    static class Node implements Comparable<Node> {
        int val, i, j;
        
        Node(int val, int i, int j) {
            this.val = val;
            this.i = i;
            this.j = j;
        }
        
        public int compareTo(Node o) {
            return this.val - o.val;
        }
    }
    
    static class Reader {
 
    private InputStream mIs;
    private byte[] buf = new byte[1024];
    private int curChar;
    private int numChars;
 
    public Reader() {
        this(System.in);
    }
 
    public Reader(InputStream is) {
        mIs = is;
    }
 
    public int read() {
        if (numChars == -1) {
            throw new InputMismatchException();
 
    }
        if (curChar >= numChars) {
            curChar = 0;
            try {
                numChars = mIs.read(buf);
            } catch (IOException e) {
                throw new InputMismatchException();
            }
            if (numChars <= 0) {
                return -1;
            }
        }
        return buf[curChar++];
    }
 
    public String nextLine() {
        int c = read();
        while (isSpaceChar(c)) {
            c = read();
        }
        StringBuilder res = new StringBuilder();
        do {
            res.appendCodePoint(c);
            c = read();
        } while (!isEndOfLine(c));
        return res.toString();
    }
 
    public String next() {
        int c = read();
        while (isSpaceChar(c)) {
            c = read();
        }
        StringBuilder res = new StringBuilder();
        do {
            res.appendCodePoint(c);
            c = read();
        } while (!isSpaceChar(c));
        return res.toString();
    }
 
    double nextDouble()
    {
        return Double.parseDouble(next());
    }
 
    public long nextLong() {
        int c = read();
        while (isSpaceChar(c)) {
            c = read();
        }
        int sgn = 1;
        if (c == '-') {
            sgn = -1;
            c = read();
        }
        long res = 0;
        do {
            if (c < '0' || c > '9') {
                throw new InputMismatchException();
            }
            res *= 10;
            res += c - '0';
            c = read();
        } while (!isSpaceChar(c));
        return res * sgn;
    }
 
    public int nextInt() {
        int c = read();
        while (isSpaceChar(c)) {
            c = read();
        }
        int sgn = 1;
        if (c == '-') {
            sgn = -1;
            c = read();
        }
        int res = 0;
        do {
            if (c < '0' || c > '9') {
                throw new InputMismatchException();
            }
            res *= 10;
            res += c - '0';
            c = read();
        } while (!isSpaceChar(c));
        return res * sgn;
    }
 
    public boolean isSpaceChar(int c) {
        return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
    }
 
    public boolean isEndOfLine(int c) {
        return c == '\n' || c == '\r' || c == -1;
    }
 
    }
}


