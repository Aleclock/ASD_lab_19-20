package editdistancestatic;

import org.junit.Test;
import static org.junit.Assert.assertEquals;

public class EditDistanceStaticTest {

    @Test
    public void editDistanceNull() {
        assertEquals(-1, EditDistanceStatic.editDistance(null, null));
    }

    @Test
    public void editDistanceBothEmpty() {
        assertEquals(0, EditDistanceStatic.editDistance("",""));
    }

    @Test
    public void editDistanceOneEmpty() {
        assertEquals(6, EditDistanceStatic.editDistance("baobab", ""));
    }

    @Test
    public void editDistanceOneCanc() {
        assertEquals(1, EditDistanceStatic.editDistance("casa", "cassa"));
    }

    @Test
    public void editDistanceCancIns() {
        assertEquals(2, EditDistanceStatic.editDistance("casa", "cara"));
    }

    @Test
    public void editDistanceTwoIns() {
        assertEquals(2, EditDistanceStatic.editDistance("vinaio", "vino"));
    }

    @Test
    public void editDistanceThreeCancOneIns() {
        assertEquals(4, EditDistanceStatic.editDistance("tassa", "passato"));
    }

    @Test
    public void editDistanceEqual() {
        assertEquals(0, EditDistanceStatic.editDistance("pioppo", "pioppo"));
    }
}
