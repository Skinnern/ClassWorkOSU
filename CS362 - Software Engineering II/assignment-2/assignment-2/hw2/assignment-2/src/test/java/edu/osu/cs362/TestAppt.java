package edu.osu.cs362;

import edu.osu.cs362.Appt;
import org.junit.Test;
import static org.junit.Assert.*; 
import java.util.EmptyStackException;


public class TestAppt {

    @Test
    public void test0() throws Throwable {
    	try{

    	}catch(Exception e){}
    }
    //*******************************************************************
    //get asset
    //*******************************************************************
    @Test
    public void TestApptMethodgetStartHour() throws Throwable{
        Appt appt = new Appt();
        int actual = Appt.getStartHour();
        assertTrue(0 <= actual && actual <= 23);
    }
    @Test
    public void TestApptMethodgetStartDay() throws Throwable{
        Appt appt = new Appt();
        int actual = Appt.getStartDay();
        assertTrue(1 <= actual && actual <= 31);
    }
    @Test
    public void TestApptMethodgetStartMonth() throws Throwable{
        Appt appt = new Appt();
        int actual = Appt.getStartMonth();
        assertTrue(1 <= actual && actual <= 12);
    }
    @Test
    public void TestApptMethodgetStartMinute() throws Throwable{
        Appt appt = new Appt();
        int actual = Appt.getStartMinute();
        assertTrue(0 <= actual && actual <= 59);
    }
    //*******************************************************************
    //set asset
    //*******************************************************************
    @Test
    public void TestApptMethodsetStartHour() throws Throwable{
        Appt appt = new Appt();
        int actual = Appt.setStartHour(Appt.getStartHour());
        assertTrue(0 <= actual && actual <= 23);
    }
    @Test
    public void TestApptMethodsetStartDay() throws Throwable{
        Appt appt = new Appt();
        int actual = Appt.setStartDay(Appt.getStartDay());
        assertTrue(1 <= actual && actual <= 31);
    }
    @Test
    public void TestApptMethodsetStartMonth() throws Throwable{
        Appt appt = new Appt();
        int actual = Appt.setStartMonth(Appt.getStartMonth());
        assertTrue(1 <= actual && actual <= 12);
    }
    @Test
    public void TestApptMethodsetStartMinute() throws Throwable{
        Appt appt = new Appt();
        int actual = Appt.setStartMinute(Appt.getStartMinute());
        assertTrue(0 <= actual && actual <= 59);
    }
    //*******************************************************************
    //create event
    //*******************************************************************
    @Test
    public void TestMakeAppt() throws Throwable{
        int startHour=5;
        int startMinute=25;
        int startDay=11;
        int startMonth=6;
        int startYear=2017;
        String title="Party";
        String description="Party time! Excellent!";
        Appt appt = new Appt(startHour, startMinute , startDay , startMonth , startYear , title, description);
        assertTrue(appt.getValid());
        assertEquals(5, appt.getStartHour());
        assertEquals(25, appt.getStartMinute());
        assertEquals(11, appt.getStartDay());
        assertEquals(6, appt.getStartMonth());
        assertEquals(2017, appt.getStartYear());
        assertEquals("Party", appt.getTitle());
        assertEquals("Party time! Excellent!", appt.getDescription());
    }

        //test inputs as false

        @Test
        public void getValidTest() throws Throwable {
            Appt appt = new Appt(-1, 2, 3, 4, 5, "getValid", "test");
            assertTrue(!appt.getValid());
            Appt appt2 = new Appt(1, -2, 3, 4, 5, "getValid", "test");
            assertTrue(!appt.getValid());
        }

    }


}