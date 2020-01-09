package edu.osu.cs362;

/**
 * Created by Nick on 4/30/2017.
 */

import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.LinkedList;
import java.util.List;
import org.junit.Test;
import static org.junit.Assert.*;
import edu.osu.cs362.Appt;
import java.util.EmptyStackException;


public class TestTimeTable {

    @Test
    public void test0() throws Throwable {
        try{

        }catch(Exception e){}
    }

    @Test
    public void test01() throws Throwable  {
        CalDay ApptsOnDay = new CalDay(new GregorianCalendar(10, 10, 10));
        Appt appt = new Appt(1, 2, 3, 4, 5, "Its Party Time", "Excellent!");
        ApptsOnDay.addAppt(appt);
        ApptsOnDay.addAppt(new Appt(5, 4, 3, 2, 1, "Its Party Time 2.0", "Excellent! 2.0"));
        TimeTable t = new TimeTable();
        assertTrue(t.getApptRange(ApptsOnDay.getAppts(), new GregorianCalendar(1, 2, 4), new GregorianCalendar(1, 2, 4)).size() > 0);
        assertTrue(t.deleteAppt(ApptsOnDay.getAppts(), appt).size() > 0);
    }


}
