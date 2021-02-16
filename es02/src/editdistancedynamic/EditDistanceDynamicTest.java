package editdistancedynamic;

import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class EditDistanceDynamicTest {

    @Test
    public void editDistanceDynNull() {
        assertEquals(-1, EditDistanceDynamic.editDistanceDynamic(null, null));
    }

    @Test
    public void editDistanceDynBothEmpty() {
        assertEquals(0, EditDistanceDynamic.editDistanceDynamic("",""));
    }

    @Test
    public void editDistanceDynOneEmpty() {
        assertEquals(6, EditDistanceDynamic.editDistanceDynamic("baobab", ""));
    }

    @Test
    public void editDistanceDynOneCanc() {
        assertEquals(1, EditDistanceDynamic.editDistanceDynamic("casa", "cassa"));
    }

    @Test
    public void editDistanceDynCancIns() {
        assertEquals(2, EditDistanceDynamic.editDistanceDynamic("casa", "cara"));
    }

    @Test
    public void editDistanceDynTwoIns() {
        assertEquals(2, EditDistanceDynamic.editDistanceDynamic("vinaio", "vino"));
    }

    @Test
    public void editDistanceDynThreeCancOneIns() {
        assertEquals(4, EditDistanceDynamic.editDistanceDynamic("tassa", "passato"));
    }

    @Test
    public void editDistanceDynEqual() {
        assertEquals(0, EditDistanceDynamic.editDistanceDynamic("pioppo", "pioppo"));
    }

    @Test
    public void editDistanceDynDifferent() {
        assertEquals(7, EditDistanceDynamic.editDistanceDynamic("ora", "bici"));
    }

    @Test
    public void editDistanceDynDifferents() {
        assertEquals(1, EditDistanceDynamic.editDistanceDynamic("pippo", "pioppo"));
    }
}
