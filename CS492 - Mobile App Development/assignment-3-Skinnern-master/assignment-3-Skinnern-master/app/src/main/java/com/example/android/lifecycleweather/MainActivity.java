package com.example.android.lifecycleweather;

import android.content.Intent;
import android.content.SharedPreferences;
import android.net.Uri;
import android.os.AsyncTask;
import android.support.v4.app.LoaderManager;
import android.support.v4.content.Loader;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.preference.PreferenceManager;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ProgressBar;
import android.widget.TextView;

import com.example.android.lifecycleweather.data.WeatherPreferences;
import com.example.android.lifecycleweather.utils.NetworkUtils;
import com.example.android.lifecycleweather.utils.OpenWeatherMapUtils;

import java.io.IOException;
import java.util.ArrayList;

public class MainActivity extends AppCompatActivity implements ForecastAdapter.OnForecastItemClickListener, LoaderManager.LoaderCallbacks<String> {

    private static final String TAG = MainActivity.class.getSimpleName();

    private TextView mForecastLocationTV;
    private RecyclerView mForecastItemsRV;
    private ProgressBar mLoadingIndicatorPB;
    private TextView mLoadingErrorMessageTV;
    private ForecastAdapter mForecastAdapter;

    //refresh
    private SharedPreferences settings;
    private SharedPreferences.OnSharedPreferenceChangeListener listener;


    private ArrayList<OpenWeatherMapUtils.ForecastItem> mForecasts;
    private static final String WEATHER_URL_KEY = "urlKey";
    private static final int LOADER_ID = 0;
    private static final int GITHUB_SEARCH_LOADER_ID = 0;
    ArrayList<OpenWeatherMapUtils.ForecastItem> forecastItems;
    private static final String LIFECYCLE_EVENTS_TEXT_KEY =
            "lifecycleEvents";
    private static final String REPOS_ARRAY_KEY = "WeatherRepos";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //refresh listener
        settings = PreferenceManager.getDefaultSharedPreferences(this);


        listener = new SharedPreferences.OnSharedPreferenceChangeListener() {
            @Override
            public void onSharedPreferenceChanged(SharedPreferences sharedPreferences, String key) {
                //getSupportActionBar().setElevation(0);

                //mForecastLocationTV = (TextView)findViewById(R.id.tv_forecast_location);
                //mForecastLocationTV.setText(WeatherPreferences.getDefaultForecastLocation());

                //mLoadingIndicatorPB = (ProgressBar)findViewById(R.id.pb_loading_indicator);
                //mLoadingErrorMessageTV = (TextView)findViewById(R.id.tv_loading_error_message);
                //mForecastItemsRV = (RecyclerView)findViewById(R.id.rv_forecast_items);

                //mForecastAdapter = new ForecastAdapter(this);
                //mForecastItemsRV.setAdapter(mForecastAdapter);
                //mForecastItemsRV.setLayoutManager(new LinearLayoutManager(this));
                //mForecastItemsRV.setHasFixedSize(true);

                //load defaults
                //

                //init loader and make weather api call
                //loadForecast();
                //getSupportLoaderManager().initLoader(LOADER_ID, null, this);
                // Refresh display
                refreshDisplay();
            }
        };

        settings.registerOnSharedPreferenceChangeListener(listener);


        //end refresh listener
        SharedPreferences sharedPreferences =
                PreferenceManager.getDefaultSharedPreferences(this);

        String locat2 = sharedPreferences.getString(getString(R.string.pref_loc_key),"");


        // Remove shadow under action bar.
        getSupportActionBar().setElevation(0);

        mForecastLocationTV = findViewById(R.id.tv_forecast_location);
        mForecastLocationTV.setText(locat2);

        mLoadingIndicatorPB = findViewById(R.id.pb_loading_indicator);
        mLoadingErrorMessageTV = findViewById(R.id.tv_loading_error_message);
        mForecastItemsRV = findViewById(R.id.rv_forecast_items);

        mForecastAdapter = new ForecastAdapter(this);
        mForecastItemsRV.setAdapter(mForecastAdapter);



        if (savedInstanceState != null && savedInstanceState.containsKey(LIFECYCLE_EVENTS_TEXT_KEY)){
            forecastItems = (ArrayList<OpenWeatherMapUtils.ForecastItem>) savedInstanceState.getSerializable(REPOS_ARRAY_KEY);
            mForecastAdapter.updateForecastItems(forecastItems);
        }


        getSupportLoaderManager().initLoader(GITHUB_SEARCH_LOADER_ID, null, this);



        mForecastItemsRV.setLayoutManager(new LinearLayoutManager(this));
        mForecastItemsRV.setHasFixedSize(true);

        //load defaults
        PreferenceManager.setDefaultValues(this, R.xml.prefs, true);

        //init loader and make weather api call
        loadForecast();
        getSupportLoaderManager().initLoader(LOADER_ID, null, this);
    }

    public void refreshDisplay() {
        // Retrieve entries from sharedPreferences & display them, e.g
        String prefValue1 = settings.getString("key1", "default value 1");
        String prefValue2 = settings.getString("key2", "default value 2");

        getSupportActionBar().setElevation(0);
        SharedPreferences sharedPreferences =
                PreferenceManager.getDefaultSharedPreferences(this);

        String locat2 = sharedPreferences.getString(getString(R.string.pref_loc_key),"");

        mForecastLocationTV = (TextView)findViewById(R.id.tv_forecast_location);
        mForecastLocationTV.setText(locat2);

        mLoadingIndicatorPB = (ProgressBar)findViewById(R.id.pb_loading_indicator);
        mLoadingErrorMessageTV = (TextView)findViewById(R.id.tv_loading_error_message);
        mForecastItemsRV = (RecyclerView)findViewById(R.id.rv_forecast_items);

        mForecastAdapter = new ForecastAdapter(this);
        mForecastItemsRV.setAdapter(mForecastAdapter);
        mForecastItemsRV.setLayoutManager(new LinearLayoutManager(this));
        mForecastItemsRV.setHasFixedSize(true);

        //load defaults
        //

        //init loader and make weather api call
        loadForecast();
        getSupportLoaderManager().initLoader(LOADER_ID, null, this);

        // Update UI with these values
        Log.d("refreshDisplay", "RefreshDisplay was called");
        loadForecast();
    }

    @Override
    public void onForecastItemClick(OpenWeatherMapUtils.ForecastItem forecastItem) {
        Intent intent = new Intent(this, ForecastItemDetailActivity.class);
        intent.putExtra(OpenWeatherMapUtils.ForecastItem.EXTRA_FORECAST_ITEM, forecastItem);
        startActivity(intent);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.action_location:
                showForecastLocation();
                return true;
            case R.id.action_settings:
                showPreferences();
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }

    //loader implementation
    @Override
    public void onLoaderReset(Loader<String> loader) {
        //Do nothing
    }

    @Override
    public Loader<String> onCreateLoader(int id, final Bundle bundle) {
        String url = null;
        if (bundle != null) {
            url = bundle.getString(WEATHER_URL_KEY);
        }

        return new WeatherSearchLoader(this, url);
    }

    @Override
    public void onLoadFinished(Loader<String> loader, String forecasts) {
        Log.d("onLoadFinished", "-- Got cached JSON data from loader. --");
        mLoadingIndicatorPB.setVisibility(View.INVISIBLE);
        if (forecasts != null) {
            mLoadingErrorMessageTV.setVisibility(View.INVISIBLE);
            mForecastItemsRV.setVisibility(View.VISIBLE);
            mForecasts = OpenWeatherMapUtils.parseForecastJSON(forecasts);
            mForecastAdapter.updateForecastItems(mForecasts);
        } else {
            mForecastItemsRV.setVisibility(View.INVISIBLE);
            mLoadingErrorMessageTV.setVisibility(View.VISIBLE);
        }
    }

    public void loadForecast() {
        //Get preferences
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
        String forecastLocation = sharedPreferences.getString(getString(R.string.pref_loc_key), "");
        String forecastUnits = sharedPreferences.getString(getString(R.string.pref_key), getString(R.string.pref_default));

        String openWeatherMapForecastURL = OpenWeatherMapUtils.buildForecastURL(
                forecastLocation,
                forecastUnits
        );
        Log.d(TAG, "Built url: " + openWeatherMapForecastURL);

        //Place url in loader and initialize
        Bundle weatherUrl = new Bundle();
        weatherUrl.putString(WEATHER_URL_KEY, openWeatherMapForecastURL);
        mLoadingIndicatorPB.setVisibility(View.VISIBLE);

        getSupportLoaderManager().restartLoader(LOADER_ID, weatherUrl, this);
    }

    public void showForecastLocation() {
        //Get forecast location from preferences
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
        String forecastLocation = sharedPreferences.getString(getString(R.string.pref_loc_key), "");

        Uri geoUri = Uri.parse("geo:0,0").buildUpon()
                .appendQueryParameter("q", forecastLocation)
                .build();
        Intent mapIntent = new Intent(Intent.ACTION_VIEW, geoUri);
        if (mapIntent.resolveActivity(getPackageManager()) != null) {
            startActivity(mapIntent);
        }
    }

    public void showPreferences() {
        //navigate to preferences page
        Intent preferences = new Intent(this, SettingsActivity.class);
        startActivity(preferences);
    }
}
