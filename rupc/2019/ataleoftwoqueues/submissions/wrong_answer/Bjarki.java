import java.util.*;
import java.math.*;
import java.io.*;

public class Bjarki {
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(System.in);
        PrintWriter out = new PrintWriter(System.out, false);

        int n = in.nextInt(),
            m = in.nextInt();

        int l = 0, r = 0;
        for (int i = 0; i < n; i++) l += in.nextInt();
        for (int i = 0; i < m; i++) r += in.nextInt();

        if (l == r) {
            out.println("equal");
        } else if (l < r) {
            out.println("left");
        } else {
            out.println("right");
        }

        out.flush();
    }
}

