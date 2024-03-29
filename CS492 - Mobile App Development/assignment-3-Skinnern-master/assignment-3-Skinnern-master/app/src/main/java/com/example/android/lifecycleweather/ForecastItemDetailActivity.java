package com.example.android.lifecycleweather;

import android.content.Intent;
import android.content.SharedPreferences;
import android.support.v4.app.ShareCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.preference.PreferenceManager;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TextView;

import com.example.android.lifecycleweather.data.WeatherPreferences;
import com.example.android.lifecycleweather.utils.OpenWeatherMapUtils;

import java.text.SimpleDateFormat;

public class ForecastItemDetailActivity extends AppCompatActivity {

    private static final SimpleDateFormat DATE_FORMATTER = new SimpleDateFormat(WeatherPreferences.getDefaultDateFormat());

    private TextView mDateTV;
    private TextView mTempDescriptionTV;
    private TextView mLowHighTempTV;
    private TextView mWindTV;
    private TextView mHumidityTV;
    private OpenWeatherMapUtils.ForecastItem mForecastItem;
    private String units;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_forecast_item_detail);

        //Get units
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
        String forecastUnits = sharedPreferences.getString(getString(R.string.pref_key), getString(R.string.pref_default));

        //Assign correct unit abbreviation
        if(forecastUnits.equals("imperial"))
            units = "F";
        else if(forecastUnits.equals("metric"))
            units = "C";
        else
            units = "K";

        mDateTV = (TextView)findViewById(R.id.tv_date);
        mTempDescriptionTV = (TextView)findViewById(R.id.tv_temp_description);
        mLowHighTempTV = (TextView)findViewById(R.id.tv_low_high_temp);
        mWindTV = (TextView)findViewById(R.id.tv_wind);
        mHumidityTV = (TextView)findViewById(R.id.tv_humidity);

        Intent intent = getIntent();
        if (intent != null && intent.hasExtra(OpenWeatherMapUtils.ForecastItem.EXTRA_FORECAST_ITEM)) {
            mForecastItem = (OpenWeatherMapUtils.ForecastItem)intent.getSerializableExtra(
                    OpenWeatherMapUtils.ForecastItem.EXTRA_FORECAST_ITEM
            );
            fillInLayoutText(mForecastItem);
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.forecast_item_detail, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.action_share:
                shareForecast();
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }

    public void shareForecast() {
        if (mForecastItem != null) {
            String shareText = "Weather for " + DATE_FORMATTER.format(mForecastItem.dateTime) +
                    ": " + mForecastItem.temperature +
                    units +
                    " - " + mForecastItem.description;
            ShareCompat.IntentBuilder.from(this)
                    .setType("text/plain")
                    .setText(shareText)
                    .setChooserTitle(R.string.share_chooser_title)
                    .startChooser();
        }
    }

    private void fillInLayoutText(OpenWeatherMapUtils.ForecastItem forecastItem) {

        String dateString = DATE_FORMATTER.format(forecastItem.dateTime);
        String detailString = forecastItem.temperature +
                units +
                " - " + forecastItem.description;
        String lowHighTempString = "Low: " + forecastItem.temperatureLow +
                units +
                "   High: " + forecastItem.temperatureHigh +
                units;
        String windString = "Wind: " + forecastItem.windSpeed + " MPH " + forecastItem.windDirection;
        String humidityString = "Humidity: " + forecastItem.humidity + "%";

        mDateTV.setText(dateString);
        mTempDescriptionTV.setText(detailString);
        mLowHighTempTV.setText(lowHighTempString);
        mWindTV.setText(windString);
        mHumidityTV.setText(humidityString);
    }
}
