import java.util.*;

public class 2021_12 {
    static TreeMap<String, TreeSet<String>> graph = new TreeMap<String, TreeSet<String>>();
    static int n;
    
    static void push(String a, String b) {
        if (!graph.containsKey(a)) graph.put(a, new TreeSet<String>());
        graph.get(a).add(b);
    }
    
    static boolean small(String s) {
        char c = s.charAt(0);
        return (c >= 'a' && c <= 'z');
    }
    
    static HashSet<ArrayList<String>> paths = new HashSet<ArrayList<String>>();
    static ArrayList<String> temp = new ArrayList<String>();
    static HashSet<String> visited = new HashSet<String>();
    static HashMap<String, Integer> count = new HashMap<String, Integer>();
    
    static void inc(String s) {
        if (!count.containsKey(s)) count.put(s, 0);
        count.put(s, count.get(s) + 1);
    }
    
    static void dec(String s) {
        count.put(s, count.get(s) - 1);
        if (count.get(s) <= 0) count.remove(s);
    }
    
    static void dfs(String src) {
        temp.add(src);
        visited.add(src);
//        System.out.println(src + " " + temp + " " + visited);
        if (src.equals("end")) {
//            System.out.println("PATH FOUND " + temp);
            ArrayList<String> path = new ArrayList<String>();
            for (String s : temp) path.add(s);
            paths.add(path);
            temp.remove(temp.size() - 1);
            return;
        }
        int index = temp.size() - 1;
        for (String s : graph.get(src)) {
            if (small(s) && visited.contains(s)) continue;
            visited.add(s);
            dfs(s);
            visited.remove(s);
        }
        temp.remove(index);
        visited.remove(src);
    }
    
    static boolean badcheck(String s) {
        boolean has2 = false;
        for (String i : count.keySet()) {
            if (small(i) && count.get(i) >= 2) has2 = true;
        }
        if (has2) {
            if (!count.containsKey(s)) return true;
            else return false;
        }
        else return true;
    }
    
    static void protogen(String src) {
        temp.add(src);
        inc(src);
//        System.out.println(src + " " + temp + " " + count);
        if (src.equals("end")) {
//            System.out.println("PATH FOUND " + temp);
            ArrayList<String> path = new ArrayList<String>();
            for (String s : temp) path.add(s);
            paths.add(path);
            temp.remove(temp.size() - 1);
            dec(src);
            return;
        }
        int index = temp.size() - 1;
        for (String s : graph.get(src)) {
            boolean bc = badcheck(s);
//            System.out.println("BAD CHECK " + s + " " + bc);
            if (small(s) && !bc) continue;
            if (s.equals("start")) continue;
            protogen(s);
        }
        temp.remove(index);
        dec(src);
    }
    
    static boolean DEBUG = false;
    
    public static void main(String[] args) {
        ArrayList<String> input = new ArrayList<String>();
        Scanner x = new Scanner(System.in); // read in strings
        
        if (!DEBUG) {
            while (x.hasNextLine()) input.add(x.nextLine());
            n = input.size();
        }
        else {
            n = 7;
            for (int i = 0; i < n; i++) input.add(x.nextLine());
        }
        
        for (String s : input) {
            int partition = s.indexOf('-');
            String a = s.substring(0, partition);
            String b = s.substring(partition + 1);
            push(a, b);
            push(b, a);
        }
        
        System.out.println(graph);
        
        dfs("start");
        System.out.println(paths.size());
        
        paths.clear();
        temp.clear();
        protogen("start");
        System.out.println(paths.size());
    }
}
