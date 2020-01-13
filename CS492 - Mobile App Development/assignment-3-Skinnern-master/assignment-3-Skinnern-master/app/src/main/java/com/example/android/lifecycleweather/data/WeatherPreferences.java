package com.example.android.lifecycleweather.data;

import android.content.SharedPreferences;
import android.support.v7.preference.PreferenceManager;

import com.example.android.lifecycleweather.R;



public class WeatherPreferences {

    private static final String DEFAULT_FORECAST_LOCATION = "Corvallis, OR, US";
    private static final String DEFAULT_TEMPERATURE_UNITS = "imperial";
    private static final String DEFAULT_TEMPERATURE_UNITS_ABBR = "F";
    private static final String DEFAULT_DATE_FORMAT = "EEE, MMM d, h:mm a";
    private static String unit = "F";

    public static String getDefaultForecastLocation() {
        return DEFAULT_FORECAST_LOCATION;
    }

    public static String getDefaultTemperatureUnits() {
        return DEFAULT_TEMPERATURE_UNITS;
    }

    public static String getDefaultTemperatureUnitsAbbr() {
        return DEFAULT_TEMPERATURE_UNITS_ABBR;
    }

    public static String getDefaultDateFormat() {
        return DEFAULT_DATE_FORMAT;
    }

    public static String setUnits(String type) {
        if(type.equals("imperial"))
            unit = "F";
        else if(type.equals("metric"))
            unit = "C";
        else if(type.equals("kelvin"))
            unit = "K";

        return unit;
    }

    public static String getUnits() {
        return unit;
    }
}
