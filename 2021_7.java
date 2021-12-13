import java.util.*;

public class 2021_7 {
    public static void main(String[] args) {
        Scanner x = new Scanner(System.in);
        String[] stuff = x.nextLine().split(",");
        int n = stuff.length;
        int[] arr = new int[n];
        for (int i = 0; i < n; i++) arr[i] = Integer.parseInt(stuff[i]);
        Arrays.sort(arr);
        
        System.out.println(n);
        
        int median = arr[n / 2];
        long devsum = 0;
        for (int i = 0; i < n; i++) devsum += Math.abs(arr[i] - median);
        System.out.println(devsum);
        
        long res = Integer.MAX_VALUE;
        
        for (int i = arr[0] - 1; i <= arr[n - 1] + 1; i++) {
            long now = 0;
            for (int j = 0; j < n; j++) {
                long deviation = Math.abs(arr[j] - i);
                now += (deviation * deviation + deviation) / 2;
            }
            res = Math.min(res, now);
        }
        
        System.out.println(res);
    }
}



