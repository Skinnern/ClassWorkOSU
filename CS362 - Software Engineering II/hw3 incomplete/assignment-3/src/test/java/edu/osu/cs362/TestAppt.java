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

    @Test
    public void TestMakeAppt() throws Throwable{
        //initalize variables
        int startHour=4;
        int startMinute=20;
        int startDay=6;
        int startMonth=9;
        int startYear=2017;
        String title="Party time!";
        String description="Excellent!";
        //create appointment with the given data
        Appt appt = new Appt(startHour, startMinute , startDay , startMonth , startYear , title, description);
        //assert that value is true
        assertTrue(appt.getValid());
        //check each value to ensure that it is correct
        //check start hour
        assertEquals(4, appt.getStartHour());
        //check start min
        assertEquals(20, appt.getStartMinute());
        //check start day
        assertEquals(6, appt.getStartDay());
        //check start month
        assertEquals(9, appt.getStartMonth());
        //check start year
        assertEquals(2017, appt.getStartYear());
        //check title
        assertEquals("Party time!", appt.getTitle());
        //check desc
        assertEquals("Excellent!", appt.getDescription());
    }

        //test inputs as false

        @Test
        public void getValidTest() throws Throwable {
        //create appointment 1
            Appt appt = new Appt(-9, 2, 3, 4, 25, "This should not", "give an error");
            //assert that this first appointment is false
            assertTrue(!appt.getValid());
            //create appointment 2
            Appt appt2 = new Appt(1, -20, 3, 4, 25, "This should not", "give an error");
            //assert that this second appointment is false
            assertTrue(!appt.getValid());
        }




        @Test
	    public void toStringTest() throws Throwable {
        //initalize variables
    	 int startHour=23;
    	 int startMinute=30;
    	 int startDay=30;
    	 int startMonth=3;
    	 int startYear=9999;
    	 String title="Party Time";
         String description="Party Time, Excellent!";
        //Construct a new Appointment object with the initial data
        	 Appt appt = new Appt(startHour, startMinute , startDay , startMonth , startYear , title, description);
        	 // assertions
             assertTrue(appt.getValid());
             assertEquals("	3/30/9999 at 11:30pm ,Party Time, Party Time, Excellent!\n", appt.toString());
             // Test with invalid appointment
             appt.setStartHour(99);
             //ensure that it does not take the hour value as true
             assertFalse(appt.getValid());
             //assert that the null is correct
             assertEquals(null, appt.toString());

        }

    //test case provided by instructor
    @Test
    public void test01()  throws Throwable  {
        int startHour=13;
        int startMinute=30;
        int startDay=10;
        int startMonth=4;
        int startYear=2017;
        String title="Birthday Party";
        String description="This is my birthday party.";
        //Construct a new Appointment object with the initial data
        Appt appt = new Appt(startHour,
                startMinute ,
                startDay ,
                startMonth ,
                startYear ,
                title,
                description);
        // assertions
        assertTrue(appt.getValid());
        assertEquals(13, appt.getStartHour());
        assertEquals(30, appt.getStartMinute());
        assertEquals(10, appt.getStartDay());
        assertEquals(04, appt.getStartMonth());
        assertEquals(2017, appt.getStartYear());
        assertEquals("Birthday Party", appt.getTitle());
        assertEquals("This is my birthday party.", appt.getDescription());
    }

}
