package com.example.android.sqliteweather;

import android.provider.BaseColumns;

/**
 * Created by Samuel on 3/12/2018.
 */

public class WeatherContract {
    private WeatherContract() {}

    public static class ForecastLocations implements BaseColumns {
        public static final String TABLE_NAME = "forecastLocations";
        public static final String COLUMN_NAME = "name";
        public static final String COLUMN_URL = "url";
        public static final String COLUMN_TIMESTAMP = "timestamp";
    }
}
