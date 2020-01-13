package com.example.android.sqliteweather;

import android.content.ContentValues;
import android.content.SharedPreferences;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.support.v14.preference.PreferenceFragment;
import android.support.v7.preference.EditTextPreference;
import android.util.Log;

public class SettingsFragment extends PreferenceFragment implements SharedPreferences.OnSharedPreferenceChangeListener {
    private SQLiteDatabase mDB;

    @Override
    public void onCreatePreferences(Bundle savedInstanceState, String rootKey) {
        addPreferencesFromResource(R.xml.prefs);
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EditTextPreference locationPref = (EditTextPreference)findPreference(getString(R.string.pref_location_key));
        locationPref.setSummary(locationPref.getText());

        //get reference to database
        ForecastDatabase forecastDB = new ForecastDatabase(this.getActivity());
        mDB = forecastDB.getWritableDatabase();
    }

    @Override
    public void onSharedPreferenceChanged(SharedPreferences sharedPreferences, String key) {
        if (key.equals(getString(R.string.pref_location_key))) {
            EditTextPreference locationPref = (EditTextPreference)findPreference(key);
            locationPref.setSummary(locationPref.getText());

            //Save into database

            //Modified lecture code
            String sqlSelection = WeatherContract.ForecastLocations.COLUMN_NAME + " = ?";
            String[] sqlSelectionArgs = { locationPref.getText() };
            Cursor cursor = mDB.query(
                    WeatherContract.ForecastLocations.TABLE_NAME,
                    null,
                    sqlSelection,
                    sqlSelectionArgs,
                    null,
                    null,
                    null
            );
            if (cursor.getCount() == 0) {
                //if entry doesn't already exist
                ContentValues values = new ContentValues();
                values.put(WeatherContract.ForecastLocations.COLUMN_NAME, locationPref.getText());
                values.put(WeatherContract.ForecastLocations.COLUMN_URL, "dummy_url");
                mDB.insert(WeatherContract.ForecastLocations.TABLE_NAME, null, values);
                Log.d("SettingsFragment", "Added " + locationPref.getText() + " to database.");
            }
            else
                Log.d("SettingsFragment", locationPref.getText() + " already exists in database.");
        }
    }

    @Override
    public void onResume() {
        getPreferenceScreen().getSharedPreferences().registerOnSharedPreferenceChangeListener(this);
        super.onResume();
    }

    @Override
    public void onPause() {
        getPreferenceScreen().getSharedPreferences().unregisterOnSharedPreferenceChangeListener(this);
        super.onPause();
    }

    @Override
    public void onDestroy() {
        mDB.close();
        super.onDestroy();
    }
}
