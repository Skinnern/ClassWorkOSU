package com.example.android.lifecycleweather;

import android.content.SharedPreferences;
import android.os.Bundle;
import android.support.v7.preference.EditTextPreference;
import android.support.v7.preference.ListPreference;
import android.support.v7.preference.PreferenceFragmentCompat;

import com.example.android.lifecycleweather.data.WeatherPreferences;


public class SettingsFragment extends PreferenceFragmentCompat implements SharedPreferences.OnSharedPreferenceChangeListener {

    @Override
    public void onCreatePreferences(Bundle savedInstanceState, String key) {
        addPreferencesFromResource(R.xml.prefs);
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EditTextPreference userLoc = (EditTextPreference)findPreference(getString(R.string.pref_loc_key));
        userLoc.setSummary(userLoc.getText());

        ListPreference userUnits = (ListPreference)findPreference(getString(R.string.pref_key));
    }

    @Override
    public void onSharedPreferenceChanged(SharedPreferences sharedPreferences, String key) {
        //Update location preference summary
        if(key.equals(getString(R.string.pref_loc_key))) {
            EditTextPreference userLoc = (EditTextPreference)findPreference(key);
            userLoc.setSummary(userLoc.getText());
        }

        //update weather preferences
        ListPreference lp = (ListPreference)findPreference(getString(R.string.pref_key));
        CharSequence entry = lp.getEntry(); //delete
        String val = lp.getValue();
        WeatherPreferences.setUnits(val);
    }

    @Override
    public void onResume() {
        //register listener
        super.onResume();
        getPreferenceScreen().getSharedPreferences().registerOnSharedPreferenceChangeListener(this);
    }

    @Override
    public void onPause() {
        //unregister listener
        super.onPause();
        getPreferenceScreen().getSharedPreferences().unregisterOnSharedPreferenceChangeListener(this);
    }

}
