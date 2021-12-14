import java.util.*;
import java.io.*;

public class 2021_13 {
    static class pair implements Comparable<pair> {
        private int x, y;
        
        public pair(int a, int b) {
            x = a;
            y = b;
        }
        
        public void set(int a, int b) {
            x = a;
            y = b;
        }
        
        public pair clone() {
            return new pair(x + 0, y + 0);
        }
        
        public int compareTo(pair other) {
            int px = this.x;
			int py = this.y;
			int ox = other.x;
			int oy = other.y;
			if (px != ox) return px - ox;
			if (py != oy) return py - oy;
			return 0;
        }
        
        public boolean equals(pair other) {
			return this.compareTo(other) == 0;
		}
		
		public String toString() {
			return "[" + x + " " + y + "]";
		}
    }
    
    static int n, m, points, folds;
    
    static TreeSet<pair> grid = new TreeSet<pair>();
    static ArrayList<pair> moves = new ArrayList<pair>(); // reflect across (coordinate != 0) = (value != 0).
    
    static TreeSet<pair> nubert(TreeSet<pair> set, pair line) {
        TreeSet<pair> res = new TreeSet<pair>();
        if (line.x == 0) {
            for (pair p : set) {
                pair q = p.clone();
                if (p.y > line.y) q.set(q.x, line.y - (p.y - line.y));
                res.add(q);
            }
        }
        else {
            for (pair p : set) {
                pair q = p.clone();
                if (p.x > line.x) q.set(line.x - (p.x - line.x), q.y);
                res.add(q);
            }
        }
        return res;
    }
    
    public static void main(String[] args) throws IOException {
        Scanner x = new Scanner(System.in);
        points = x.nextInt();
        folds = x.nextInt();
        x.nextLine();
        
        for (int i = 0; i < points; i++) {
            String s = x.nextLine();
            int index = s.indexOf(',');
            int a = Integer.parseInt(s.substring(0, index));
            int b = Integer.parseInt(s.substring(index + 1));
            grid.add(new pair(a, b));
        }
        
        for (int i = 0; i < folds; i++) {
            String line = x.nextLine().split(" ")[2];
            int valhalla = Integer.parseInt(line.substring(2));
            if (line.charAt(0) == 'x') moves.add(new pair(valhalla, 0));
            else moves.add(new pair(0, valhalla));
        }
        
//        System.out.println(grid);
//        System.out.println(moves);
        
        TreeSet<pair> grid1 = nubert(grid, moves.get(0));
        System.out.println(grid1.size());
        
        TreeSet<pair> res = new TreeSet<pair>();
        for (pair p : grid) res.add(p);
        for (pair p : moves) res = nubert(res, p);
        
        int minx, miny, maxx, maxy;
        minx = miny = Integer.MAX_VALUE;
        maxx = maxy = Integer.MIN_VALUE;
        for (pair p : res) {
            minx = Math.min(p.x, minx);
            maxx = Math.max(p.x, maxx);
            miny = Math.min(p.y, miny);
            maxy = Math.max(p.y, maxy);
        }
        
        System.out.println(minx + " " + miny + " " + maxx + " " + maxy);
        
//        PrintWriter pp = new PrintWriter(new BufferedWriter(new FileWriter("Thing.out")));
        
        for (int i = miny - 1; i <= maxy + 1; i++) {
            for (int j = minx - 1; j <= maxx + 1; j++) {
                System.out.print(res.contains(new pair(j, i)) ? "#" : ".");
            }
            System.out.println();
        }
//        pp.close();
    }
}
