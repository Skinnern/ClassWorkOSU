package com.example.android.lifecycleweather;

import android.content.Context;
import android.support.annotation.Nullable;
import android.util.Log;

import com.example.android.lifecycleweather.utils.NetworkUtils;

import java.io.IOException;

public class WeatherSearchLoader extends android.support.v4.content.AsyncTaskLoader<String> {


    private static final String TAG = WeatherSearchLoader.class.getSimpleName();

    private String mForecastAdapter;
    private String mWeatherSearchURL;
    private static final int GITHUB_SEARCH_LOADER_ID = 0;

    WeatherSearchLoader(Context context, String url) {
        super(context);
        mWeatherSearchURL = url;
    }

    @Override
    protected void onStartLoading() {
        if (mWeatherSearchURL != null) {
            //forceLoad();
            forceLoad();

            if (mForecastAdapter != null) {
                Log.d(TAG, "Delivering cached results");
                deliverResult(mForecastAdapter);
            } else {
                forceLoad();
            }
        }
    }



    @Override
    public String loadInBackground() {
        if (mWeatherSearchURL != null) {
            String searchResults = null;
            try {
                searchResults =
                        NetworkUtils.doHTTPGet(mWeatherSearchURL);
                Log.d(TAG, "loading results from GitHub with URL: " + mWeatherSearchURL);
            } catch (IOException e) {
                e.printStackTrace();
            }
            return searchResults;
        } else {
            return null;
        }
    }

    @Override
    public void deliverResult(@Nullable String data) {
        mForecastAdapter = data;
        super.deliverResult(data);
    }


}
