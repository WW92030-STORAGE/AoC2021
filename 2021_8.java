import java.util.*;

public class Main
{
    static int[][] disp = 
        {{1, 1, 1, 0, 1, 1, 1}, {0, 0, 1, 0, 0, 0, 1}, 
        {0, 1, 1, 1, 1, 1, 0}, {0, 1, 1, 1, 0, 1, 1},
        {1, 0, 1, 1, 0, 0, 1}, {1, 1, 0, 1, 0, 1, 1},
        {1, 1, 0, 1, 1, 1, 1}, {0, 1, 1, 0, 0, 0, 1}, 
        {1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 0, 1, 1}};
	public static void main(String[] args) {
	    ArrayList<String> list = new ArrayList<String>();
	    Scanner x = new Scanner(System.in);
		while (x.hasNextLine()) list.add(x.nextLine());
		int n = list.size();
		
		int[] freq = new int[10];
		for (int sk = 0; sk < n; sk++) {
		    String[] stuff = list.get(sk).split(" ");
		    for (int i = 10; i < stuff.length; i++) {
		        if (stuff[i].charAt(0) == '|') continue;
		        switch(stuff[i].length()) {
		            case 2:
		                freq[1]++;
		                break;
		            case 3:
		                freq[7]++;
		                break;
		            case 4:
		                freq[4]++;
		                break;
		            case 7:
		                freq[7]++;
		                break;
		        }
		    }
		}
		
		long res = 0;
		for (int i = 0; i < freq.length; i++) res += freq[i];
		System.out.println(res);
		
		res = 0;
		for (int sk = 0; sk < n; sk++) {
		    String[] stuff = list.get(sk).split(" ");
//		    System.out.println(Arrays.toString(stuff) + " \\ " + stuff.length);
		    char[] segments = new char[7]; // UL TOP UR MID BL BOT BR
		    
		    boolean found = false;
		    
		    for (int a = 0; a < 7 && !found; a++) {
		        for (int b = 0; b < 7 && !found; b++) {
		            if (a == b) continue;
		            for (int c = 0; c < 7 && !found; c++) {
		                if (b == c) continue;
		                for (int d = 0; d < 7 && !found; d++) {
		                    if (c == d) continue;
		                    for (int e = 0; e < 7 && !found; e++) {
		                        if (d == e) continue;
		                        for (int f = 0; f < 7 && !found; f++) {
		                            if (e == f) continue;
		                            for (int g = 0; g < 7 && !found; g++) {
		                                TreeSet<Integer> set = new TreeSet<Integer>();
		                                set.add(a); set.add(b); set.add(c); set.add(d); set.add(e); set.add(f); set.add(g);
		                                if (set.size() != 7) continue;
		                                
		                                // now for the good stuff
		                                char[] temp = {(char)(a + 'a'), (char)(b + 'a'), (char)(c + 'a'), (char)(d + 'a'), (char)(e + 'a'), (char)(f + 'a'), (char)(g + 'a')};
		                                boolean[] taken = new boolean[10];
		                                Arrays.fill(taken, false);
		                                for (int i = 0; i < 10; i++) {
		                                    int[] used = new int[7];
		                                    String s = stuff[i];
		                                    for (int j = 0; j < s.length(); j++) {
		                                        for (int k = 0; k < 7; k++) {
		                                            if (s.charAt(j) == temp[k] && used[k] == 0) used[k] = 1; 
		                                        }
		                                    }
		                                    
		                                    int matchcount = 0;
		                                    int expected = 0;
		                                //    System.out.println(s + " " + Arrays.toString(used));
		                                    
		                                    for (int look = 0; look < 10; look++) {
		                                        if (taken[look]) continue;
		                                        matchcount = 0;
		                                        for (int k = 0; k < 7; k++) matchcount += used[k] * (1<<k);
		                                        expected = 0;
		                                        for (int k = 0; k < 7; k++) expected += disp[look][k] * (1<<k);
		                                        if (matchcount == expected) {
		                                            taken[look] = true;
		                                        //    System.out.println(look + " " + matchcount + " " + expected);
		                                        }
		                                    }
		                                }
		                                
		                            //    System.out.println("MATCHES " + Arrays.toString(taken));
		                                boolean good = true;
		                                for (int i = 0; i < 10; i++) good = good && taken[i];
		                                
		                                if (good) {
//		                                    System.out.println(Arrays.toString(temp));
		                                    for (int i = 0; i < 7; i++) segments[i] = temp[i];
		                                    found = true;
		                                }
		                            }
		                        }
		                    }
		                }
		            }
		        }
		    }
		    
//		    System.out.println(Arrays.toString(segments));
		    
		    long sum = 0;
		    int digits[] = new int[4];
		    for (int index = 11; index < 15; index++) {
//		        System.out.println(index);
		        int occ[] = new int[7];
		        String s = stuff[index];
//		        System.out.println(s);
		        for (int i = 0; i < s.length(); i++) {
		            for (int j = 0; j < 7; j++) {
//		                System.out.println(i + " " + j + " " + s.charAt(i) + " " + segments[j]);
		                if (s.charAt(i) == segments[j]) occ[j] = 1;
		            }
		        }
		        
//		        System.out.println(Arrays.toString(occ));
		        
		        for (int i = 0; i < 10; i++) {
		            int matchcount = 0;
		            int expected = 0;
		            for (int j = 0; j < 7; j++) {
		                matchcount += occ[j] * (1<<j);
		                expected += disp[i][j] * (1<<j);
		            }
//		            System.out.println(i + " " + matchcount + " " + expected);
		            if (matchcount == expected) digits[index - 11] = i;
		        }
		    }
		    
		    System.out.println(Arrays.toString(digits));
		    for (int i = 0; i < 4; i++) {
		        sum *= 10;
		        sum += digits[i];
		    }
		    
		    res += sum;
		    System.out.println(sum + " " + res);
		}
	}
}




