/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package finalprojectB;

import junit.framework.TestCase;

/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.
    UrlValidator testVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

   public UrlValidatorTest(String testName) {
      super(testName);
   }

    //Manually testing isvalid
    public void testManualTest()
    {
        //for our manual tests, we are feeding the program a manually created group of URLs, and making sure that they are valid
        //urls that are supposed to be resolvable by our url structure rules
        String[] testValidUrl= {
                "http://121.133.145.254",
                "ftp://192.168.100.002",
                "http://www.americarules.us",
                "http://www.ukrules.uk",
                "http://www.amazon.com",
                "http://www.amazon.com:65535",
                "http://www.amazon.com:80",
                "http://www.amazon.com/test1",
                "http://www.amazon.com/test1/file",
                "http://www.amazon.com?action=edit&mode=up",
                "http://www.amazon.com?action=edit&mode=up",
                "http://www.google.com",
                "http://www.go.com",
                "ftp://www.workingwebsite.com",
                "http://yahoo.com",
                "http://www.yahoo.co.uk"};

        //urls that are not supposed to be resolvable by our url structure rules
        String[] testInvalidUrl= {"",
                "http://256.256.256.256",
                "ftp://192.256.256.256",
                "http://www.amazšn.com",
                "www.amazon.comhttp://",
                "http://www.amazon.com:65d",
                "http://www.amazon.com:-9",
                "http://www.amazon.com//",
                "http://www.amazon.com/test1/..",
                "http://www.amazon.com&34",
                "http://www.amazon.com>action",
                "h2p:/www.go.com",
                "http://google.4a",
                "http://go.33",
                "ftp://www.workingwebsite",
                "http://yah oo.com",
                "http://yahoo.arr"};


        //initiate variables
        int i;
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        boolean result;


        //URL Validation
        //for loop to test valid urls
        for (i=0; i<testValidUrl.length;i++){
            System.out.println("Testing a valid URL address:"+testValidUrl[i]);
            //find if true or false
            result= urlVal.isValid(testValidUrl[i]);
            if (result)
            {
                //if valid, give pass
                System.out.println("Valid URL:"+testValidUrl[i]+" Pass");
            }
            else {
                //if invalid, give fail
                System.out.println("Valid URL:"+testValidUrl[i]+" Fail");
            }

        }
        System.out.println();

        //for loop to test invalid urls
        for (i=0; i<testInvalidUrl.length;i++){
            System.out.println("Testing an invalid URL address:"+testInvalidUrl[i]);
            //find if true or false
            result= urlVal.isValid(testInvalidUrl[i]);
            if (!result){
                //if invalid, we passed
                System.out.println("Invalid URL:"+testInvalidUrl[i]+" Pass");
            }
            else {
                //if valid, testing has failed
                System.out.println("Invalid URL:"+testInvalidUrl[i]+" Fail");
            }

        }
        System.out.println("Test Finished");
    }

   
   
   public void testYourFirstPartition(){
       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

       //first partition
       //ip address validation
       //normal ip check
       assertTrue(urlVal.isValid("http://101.111.121.131"));
       //low end check
       assertTrue(urlVal.isValid("http://0.0.0.0"));
       //maximum number that should be allowed for ip
       assertTrue(urlVal.isValid("http://255.255.255.255"));

       //check column within minimum range
       //check first column negative
       assertFalse(urlVal.isValid("http://-101.111.121.131"));
       //check all for negative
       assertFalse(urlVal.isValid("http://-101.-111.-121.-131"));

       //check column value within maximum range
       //check one for too many chars in ip field
       assertFalse(urlVal.isValid("http://1101.111.121.131"));
       //check all for too many chars in ip field
       assertFalse(urlVal.isValid("http://1101.1111.1121.1131"));
       //check one for value just above out max
       assertFalse(urlVal.isValid("http://256.111.121.131"));
       //check all for value just above our max
       assertFalse(urlVal.isValid("http://256.256.256.256"));
   }
   
   public void testYourSecondPartition(){
       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

       //second partition testing
       //check that valid cases pass
       //check port
       assertTrue(urlVal.isValid("http://www.google.com:42"));
       //check port
       //check directory
       assertTrue(urlVal.isValid("https://www.google.com:0/q/w/e/r/t/y/u"));
       //check ip with port extension
       assertTrue(urlVal.isValid("http://8.6.7.5:309/?h=j"));

       //second partition testing
       //check that negative numbers do not pass for port
       //check port
       assertFalse(urlVal.isValid("http://www.google.com:-82"));
       //check port
       //check directory
       assertFalse(urlVal.isValid("http://www.google.com:-1/q/w/e/r/t/y/u"));
       //ip port extension
       assertFalse(urlVal.isValid("http://8.6.7.5:-309/?h=j"));
   }
   
   
   public void testIsValid(){
       portTest("http://www.google.com:@@@");
       for(int i = 0;i<10000;i++){
           //Port tests
           portTest("http://www.google.com:@@@");
           //Single segment IP tests
           ipTest("http://255.255.255.@@@");
           ipTest("http://255.255.@@@.255");
           ipTest("http://255.@@@.255.255");
           ipTest("http://@@@.255.255.255");
	   }
   }

   /*Generates random values into a passed string
   and asserts if that URL should be correct
    */
   private void ipTest(String test) {
       int MIN_VALUE = -256;
       int MAX_VALUE = 500;
       String url, ip;
       boolean valid = false;

       //Generate a random number
       int rand = (int)(Math.random() * MAX_VALUE * 2 + MIN_VALUE);
       ip = Integer.toString(rand);
       System.out.println("Random number is "+ip);

       //Determine if valid
       if( (rand<256) && (rand>=0) ) {
           valid = true;
       }
       else
           valid = false;

       //Replace part of string
       url = test.replaceAll("@@@",ip);
       //System.out.println(url);

       //Determine assertion
       if(valid==true) {
           System.out.println(url+" is true.");
           assertTrue(testVal.isValid(url));
       }
       else if(valid==false) {
           System.out.println(url+" is false.");
           assertFalse(testVal.isValid(url));
       }
   }

    private void portTest(String test) {
        int MIN_VALUE = -200000;
        int MAX_VALUE = 200000;
        String url, ip;
        boolean valid = false;

        //Generate a random number
        int rand = (int)(Math.random() * MAX_VALUE * 2 + MIN_VALUE);
        ip = Integer.toString(rand);
        System.out.println("Random number is "+ip);

        //Determine if valid
        if( (rand<100000) && (rand>=0) ) {
            valid = true;
        }
        else
            valid = false;

        //Replace part of string
        url = test.replaceAll("@@@",ip);
        //System.out.println(url);

        //Determine assertion
        if(valid==true) {
            System.out.println(url+" is true.");
            assertTrue(testVal.isValid(url));
        }
        else if(valid==false) {
            System.out.println(url+" is false.");
            assertFalse(testVal.isValid(url));
        }
    }

   public void testAnyOtherUnitTest(){
	   
   }
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   

}
