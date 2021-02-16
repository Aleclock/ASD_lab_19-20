package editdistancestatic;

public class EditDistanceStatic {

    public static int editDistance(String string1, String string2) {
        if (string1 == null || string2 == null) {
            return -1;
        }
        else {
            return editDistanceRecursive(string1, string2);
        }
    }

    private static int editDistanceRecursive(String s1, String s2) {
        int d_canc, d_ins, d_noop;

        if (s1.isEmpty())
            return s2.length();
        else if (s2.isEmpty())
            return s1.length();
        else {
            d_noop = calculateNoOp(s1,s2);
            d_canc = 1 + editDistanceRecursive(s1, rest(s2));
            d_ins = 1 + editDistanceRecursive(rest(s1), s2);
        }
        return getMin(d_noop, d_canc, d_ins);
    }

    private static String rest (String s) {
        return s.substring(1);
    }

    private static int calculateNoOp(String s1, String s2) {
        if (s1.charAt(0) == s2.charAt(0))
            return editDistanceRecursive(rest(s1), rest(s2));
        else
            return Integer.MAX_VALUE;
    }

    private static int getMin(int v1, int v2, int v3) {
        return Math.min(Math.min(v1, v2), v3);
    }
}
