package com.example.android.sqliteweather;

import android.content.Context;
import android.content.SharedPreferences;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.preference.PreferenceManager;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.example.android.sqliteweather.utils.OpenWeatherMapUtils;

import java.text.DateFormat;
import java.util.ArrayList;


public class SavedLocationAdapter extends RecyclerView.Adapter<SavedLocationAdapter.SavedLocationViewHolder> {
    private static final String TAG = MainActivity.class.getSimpleName();

    private ArrayList<String> mLocations;
    private OnSavedLocationClickListener mSavedLocationClickListener;
    private Context mContext;
    private DrawerLayout mDrawerLayout;

    public interface OnSavedLocationClickListener {
        void onForecastItemClick(OpenWeatherMapUtils.ForecastItem forecastItem);
    }

    public SavedLocationAdapter(Context context, SavedLocationAdapter.OnSavedLocationClickListener clickListener) {
        mContext = context;
        mSavedLocationClickListener = clickListener;
    }

    public void updateLocations(ArrayList<String> locations) {
        mLocations = locations;
        notifyDataSetChanged();
    }

    @Override
    public int getItemCount() {
        if (mLocations != null) {
            return mLocations.size();
        } else {
            return 0;
        }
    }

    @Override
    public SavedLocationAdapter.SavedLocationViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        LayoutInflater inflater = LayoutInflater.from(parent.getContext());
        View itemView = inflater.inflate(R.layout.location_item, parent, false);
        return new SavedLocationAdapter.SavedLocationViewHolder(itemView);
    }

    @Override
    public void onBindViewHolder(SavedLocationAdapter.SavedLocationViewHolder holder, int position) {
        holder.bind(mLocations.get(position));
    }

    class SavedLocationViewHolder extends RecyclerView.ViewHolder implements View.OnClickListener {
        private TextView mLocationTV;

        public SavedLocationViewHolder(View itemView) {
            super(itemView);
            mLocationTV = (TextView)itemView.findViewById(R.id.tv_location);
            itemView.setOnClickListener(this);
        }

        public void bind(String loc) {
            mLocationTV.setText(loc);
        }

        @Override
        public void onClick(View v) {
            //nothing


            //CHANGE THIS STUFF FOR LOCATION UPDATES
            SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(mContext);
            SharedPreferences.Editor clickchange = sharedPreferences.edit();
            clickchange.putString("location pref name",mLocations.get(1));
            clickchange.commit();

            //mDrawerLayout = (DrawerLayout) findViewById(R.id.drawer_layout);

            Log.d(TAG, "changing to location" + mLocations.get(1));

        }
    }

}
