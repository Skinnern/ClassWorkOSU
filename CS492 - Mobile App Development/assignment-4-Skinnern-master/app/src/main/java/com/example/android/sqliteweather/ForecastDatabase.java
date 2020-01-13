package com.example.android.sqliteweather;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;



public class ForecastDatabase extends SQLiteOpenHelper {
    private static final String DATABASE_NAME = "forecasts.db";
    private static final int DATABASE_VERSION = 1;

    public ForecastDatabase(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        final String SQL_CREATE_FORECAST_TABLE =
                "CREATE TABLE " + WeatherContract.ForecastLocations.TABLE_NAME +
                        " (" + WeatherContract.ForecastLocations._ID + " INTEGER PRIMARY KEY AUTOINCREMENT, " +
                        WeatherContract.ForecastLocations.COLUMN_NAME + " TEXT NOT NULL, " +
                        WeatherContract.ForecastLocations.COLUMN_URL + " TEXT NOT NULL, " +
                        WeatherContract.ForecastLocations.COLUMN_TIMESTAMP +
                        " TIMESTAMP DEFAULT CURRENT_TIMESTAMP" +
                        ");";
        Log.d("SQL string ---------->", SQL_CREATE_FORECAST_TABLE);

        db.execSQL(SQL_CREATE_FORECAST_TABLE);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int old, int cur) {
        db.execSQL("DROP TABLE IF EXISTS " + WeatherContract.ForecastLocations.TABLE_NAME);
        onCreate(db);
    }
}
