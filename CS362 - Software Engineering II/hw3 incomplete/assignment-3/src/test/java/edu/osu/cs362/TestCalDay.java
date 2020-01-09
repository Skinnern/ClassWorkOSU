package edu.osu.cs362;

/**
 * Created by Nick on 4/30/2017.
 */

import edu.osu.cs362.Appt;
import org.junit.Test;
import static org.junit.Assert.*;
import java.util.EmptyStackException;
import java.util.Iterator;
import java.util.GregorianCalendar;


public class TestCalDay {

    @Test
    public void test0() throws Throwable {
        try{

        }catch(Exception e){}
    }

    //to test default constructor,
    @Test
    public void nullTest()  throws Throwable {
        //assign day to refer to calday
        CalDay day = new CalDay();
        //asserting that calday should be invalid
        assertFalse(day.isValid());
        //asserting that the value should be null, as we put nothing into it
        assertNull(day.iterator());
        //check if the tostring is blank
        assertEquals("", day.toString());

    }

    @Test
    public void printTest() throws Throwable  {
        //instance some variables to use
        int startHour=13;
        int startMinute=10;
        int startDay=10;
        int startMonth=6;
        int startYear=2017;
        String title="Party Time";
        String description="Excellent!";
        //creating an appointment, with the data we have made
        Appt appt = new Appt(startHour, startMinute , startDay , startMonth , startYear , title, description);
        //instanciate the gregorian calender
        GregorianCalendar cal= new GregorianCalendar();
        //create a new day with the cal date
        CalDay day = new CalDay(cal);
        //asserting to check that we do not have a value yet
        assertEquals(0,day.getSizeAppts());
        //add the day to appointments
        day.addAppt(appt);
        //asserting that day will return a value
        assertEquals(1,day.getSizeAppts());
        //ensure asset is not equal to null
        assertNotEquals("",day.toString());
    }

    @Test
    public void TestSetGet() throws Throwable  {
        //instance greg calendar
        GregorianCalendar cal= new GregorianCalendar();
        //instance CalDay
        CalDay day = new CalDay(cal);
        //assert that cal and day have the same day
        assertEquals(cal.get(cal.DAY_OF_MONTH),day.getDay());
        //assert that cal and day have the same month
        assertEquals(cal.get(cal.MONTH),day.getMonth());
        //assert that cal and day have the same year
        assertEquals(cal.get(cal.YEAR),day.getYear());

    }


}
