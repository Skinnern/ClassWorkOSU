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


    //the default test case
    @Test
    public void test0() throws Throwable {
        try{
        }catch(Exception e){}
    }

    @Test
    public void test01()  throws Throwable  {
        //import Time to be used to get dates
        TimeTable Time = new TimeTable();
        //import the appt linked list
        LinkedList<Appt> appta = new LinkedList<Appt>();
        //create first day
        GregorianCalendar greg1 = new GregorianCalendar(2017,5,18);
        //create second day
        GregorianCalendar greg2 = new GregorianCalendar(2017,5,19);
        //getting range between first and second date
        Time.getApptRange(appta,greg1,greg2);
        //assert that value between these is not null
        assertNotNull(Time.getApptRange(appta, greg1, greg2));
    }

    @Test
    public void test06()  throws Throwable  {
        //import timetable as time
        TimeTable Time = new TimeTable();
        //import gregorian with two dates
        GregorianCalendar greg = new GregorianCalendar();
        //first date
        GregorianCalendar greg1 = new GregorianCalendar(2017,6,18);
        //second date
        GregorianCalendar greg2 = new GregorianCalendar(2017,6,19);
        //import calday as day
        CalDay day = new CalDay(greg);
        //new appointment on
        Appt appt = new Appt(5,5,5,5,5,"this should not","cause a failure");
        //create linkedlist as appta
        LinkedList<Appt> appta = new LinkedList<Appt>();
        //set appts to null
        appta = null;
        //delete data in appts
        Time.deleteAppt(appta,appt);
        //assert this is not null
        assertNotNull(Time.getApptRange(day.getAppts(), greg1, greg2));
    }

    @Test
    public void test08()  throws Throwable  {
        //import timetable as time
        TimeTable Time = new TimeTable();
        //create first day
        GregorianCalendar Greg1 = new GregorianCalendar(2016, 2, 16);
        //create second day
        GregorianCalendar Greg2 = new GregorianCalendar(2018, 2, 16);
        //import calday as day
        CalDay day = new CalDay(Greg1);
        //check for appointments within range
        Time.getApptRange(day.appts, Greg1, Greg2);
        //delete appointment
        Time.deleteAppt(null, null);
        //adding appointment to appt
        Appt new_appt = new Appt(15, 37, 17, 10, 2017,"this should not","cause a failure");
        //adding appointment through day
        day.addAppt(new_appt);
        //delete the appointment
        Time.deleteAppt(day.appts, new_appt);
        //assert that time is not null
        assertNotNull(Time);
    }


    @Test
    public void test04()  throws Throwable  {
        //import timetable as time
        TimeTable Time = new TimeTable();
        //import gregorian calander and dates
        GregorianCalendar greg = new GregorianCalendar();
        //create first date
        GregorianCalendar greg1 = new GregorianCalendar(2017,6,10);
        //create second date
        GregorianCalendar greg2 = new GregorianCalendar(2017,6,20);
        //set calday as day
        CalDay day = new CalDay(greg);
        //set variables for an invalid month
        int startHour=4;
        int startMinute= 20;
        int startDay=66;
        int startMonth=-22;
        int startYear=2017;
        String title="Party Time";
        String description="Excellent";
        //Construct a new Appointment object with the initial data
        Appt appt = new Appt(startHour,startMinute ,startDay ,startMonth ,startYear ,title, description);
        //create second appointment
        Appt appt2 = new Appt(2,2,15,6,2017,"this should not","cause an error");
        //add appointment 1
        day.addAppt(appt);
        //add appointment 2
        day.addAppt(appt2);
        //get the appointments for these dates
        Time.getApptRange(day.getAppts(),greg1,greg2);
        //assert that the inforamtion is not null
        assertNotNull(Time.getApptRange(day.getAppts(), greg1, greg2));
    }


}
