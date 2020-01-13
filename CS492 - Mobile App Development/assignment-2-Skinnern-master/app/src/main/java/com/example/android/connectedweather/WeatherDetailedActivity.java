package com.example.android.connectedweather;

import android.content.Intent;
import android.net.Uri;
import android.support.v4.app.ShareCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TextView;

public class WeatherDetailedActivity extends AppCompatActivity {
    private TextView mRepoNameTV;
    private TextView WeatherMax;
    private TextView WeatherMin;
    private TextView mRepoDescriptionTV;
    private WeatherUtils.GitHubRepo mRepo;

    //mRepo = null;
    Intent intent = getIntent();
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_repo_detail);

        mRepoNameTV = findViewById(R.id.tv_repo_name);
        WeatherMax = findViewById(R.id.tv_repo_stars);
        WeatherMin= findViewById(R.id.tv_repo_min);
        mRepoDescriptionTV = findViewById(R.id.tv_repo_description);

        Intent intent = getIntent();
        if (intent != null && intent.hasExtra(WeatherUtils.EXTRA_GITHUB_REPO)) {
            mRepo = (WeatherUtils.GitHubRepo) intent.getSerializableExtra(WeatherUtils.EXTRA_GITHUB_REPO);
            mRepoNameTV.setText("Date: "+mRepo.dt_txt);
            WeatherMax.setText("Max Temp: " + mRepo.main.temp_max);
            WeatherMin.setText("Min Temp: "+mRepo.main.temp_min);
            mRepoDescriptionTV.setText("Weather Description: " + mRepo.weather[0].description );
        //+ mRepo.city.coord.lon + " " + mRepo.city.coord.lat

            //old
            /*
            WeatherUtils.GitHubRepo repo = (WeatherUtils.GitHubRepo) intent.getSerializableExtra(WeatherUtils.EXTRA_GITHUB_REPO);
            mRepoNameTV.setText("Date: "+repo.dt_txt);
            WeatherMax.setText("Max Temp: " + repo.main.temp_max);
            WeatherMin.setText("Min Temp: "+repo.main.temp_min);
            mRepoDescriptionTV.setText("Weather Description: " + repo.weather[0].description);
            */
        }
    }




    //new stuffs:

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.repo_detail, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.action_share:
                shareRepo();
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }


    public void shareRepo() {
        if (mRepo != null) {
            String shareText = getString(R.string.share_repo_text , mRepo.dt_txt, mRepo.weather[0].description);
            ShareCompat.IntentBuilder.from(this)
                    .setType("text/plain")
                    .setText(shareText)
                    .setChooserTitle(R.string.share_chooser_title)
                    .startChooser();
        }
    }



}
