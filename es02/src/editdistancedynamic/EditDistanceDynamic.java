package editdistancedynamic;

public class EditDistanceDynamic {

    public static int editDistanceDynamic (String string1, String string2) {
        if (string1 == null || string2 == null) {
            return -1;
        }
        else {
            int [][] mem = new int[string1.length() + 1][string2.length() + 1];

            for (int i = 0; i <= string1.length(); i++)
                for (int j = 0; j <= string2.length(); j++)
                    mem[i][j] = -1;

            return editDistanceDynRecursive(string1, string2, 0, 0, mem);
        }
    }

    private static int editDistanceDynRecursive(String s1, String s2, int i, int j, int[][] mem) {
        int d_canc, d_ins, d_noop, min;

        if (mem[i][j] > -1)
            return mem[i][j];
        else {
            if (s1.length() == 0)   return s2.length();
            if (s2.length() == 0)   return s1.length();

            // no-op
            d_noop = calculateNoOp(s1, s2, i, j, mem);

            // canc
            if (mem[i][j+1] == -1)
                d_canc = 1 + editDistanceDynRecursive(s1, rest(s2), i, j+1, mem);
            else
                d_canc = 1 + mem[i][j+1];

            // ins
            if (mem[i+1][j] == -1)
                d_ins = 1 + editDistanceDynRecursive(rest(s1), s2, i+1, j, mem);
            else
                d_ins = 1 + mem[i+1][j];

            min = getMin(d_noop, d_canc, d_ins);
            mem[i][j] = min;
            return min;
        }
    }

    private static int calculateNoOp(String s1, String s2, int i, int j, int [][] mem) {
        if (s1.charAt(0) == s2.charAt(0)) {
            if (mem[i + 1][j + 1] == -1)
                return editDistanceDynRecursive(rest(s1), rest(s2), i + 1, j + 1,mem);
            else
                return mem[i + 1][j + 1];
        } else
            return Integer.MAX_VALUE;
    }

    /**
     * Given a string s, returns the substring of s ignoring the first character
     */
    private static String rest (String s) {
        return s.substring(1);
    }

    /**
     * Get minimum between three values
     */
    private static int getMin(int v1, int v2, int v3) {
        return Math.min(Math.min(v1, v2), v3);
    }

    /**
     * Print memoization matrix in console
     * @param grid: 2d matrix (memoization)
     */
    static void printMatrix(int[][] grid) {
        for (int[] ints : grid) {
            for (int anInt : ints)
                System.out.print(anInt + "\t");
            System.out.println();
        }
        System.out.println();
    }
}
