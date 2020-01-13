package com.example.android.connectedweather;

import android.net.Uri;

import com.google.gson.Gson;
import com.google.gson.annotations.SerializedName;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;




public class WeatherUtils {
    private final static String GITHUB_SEARCH_BASE_URL = "https://api.openweathermap.org/data/2.5/forecast";
    private final static String GITHUB_SEARCH_QUERY_PARAM = "q";
    private final static String GITHUB_SEARCH_SORT_PARAM = "sort";
    private final static String GITHUB_SEARCH_API_PARAM = "APPID";
    private final static String Weather_API_KEY = "4f089dcd4ac474b62f297e497e2f5321";

    public static final String EXTRA_GITHUB_REPO = "WeatherUtils.GitHubRepo";

    public static class GitHubRepo implements Serializable {
        public String dt;

        public tempu main;

        public weather[] weather;

        public cloud clouds;

        public wind wind;

        public sys sys;

        public String dt_txt;

        //public City city;
    }




    public static class GitHubSearchResults {
        public GitHubRepo[] list;
    }

    public static String buildGitHubSearchURL(String query) {
        return Uri.parse(GITHUB_SEARCH_BASE_URL).buildUpon()
                .appendQueryParameter(GITHUB_SEARCH_QUERY_PARAM, query)
                .appendQueryParameter(GITHUB_SEARCH_API_PARAM, Weather_API_KEY)
                .build()
                .toString();
    }

    public static GitHubRepo[] parseGitHubSearchResults(String json) {
        Gson gson = new Gson();
        GitHubSearchResults results = gson.fromJson(json, GitHubSearchResults.class);
        if (results != null && results.list != null) {
            return results.list;
        } else {
            return null;
        }
    }
}
     class tempu implements Serializable {
        @SerializedName("temp") public String temp;
         @SerializedName("temp_min")public String temp_min;
         @SerializedName("temp_max") public String temp_max;
         @SerializedName("pressure") public String pressure;
         @SerializedName("sea_level") public String sea_level;
         @SerializedName("grnd_level") public String grnd_level;
         @SerializedName("humidity") public String humidity;
         @SerializedName("temp_kf") public String temp_kf;
    }

    class weather implements Serializable{
        @SerializedName("id") public String id;
        @SerializedName("main") public String main;
        @SerializedName("description") public String description;
        @SerializedName("icon") public String icon;
    }
class cloud implements Serializable{
    @SerializedName("all") public String all;
}
class wind implements Serializable{
    @SerializedName("speed") public String speed;
    @SerializedName("deg") public String deg;
}
class sys implements Serializable{
    @SerializedName("pod") public String pod;
}

//meme
class string implements Serializable{
    @SerializedName("String") public String string;
}

class City implements Serializable{
    @SerializedName("id") public String id;
    @SerializedName("name") public String name;
    @SerializedName("coord") public cordin coord;
    @SerializedName("country") public String country;
    @SerializedName("population") public String population;
}
class cordin implements Serializable{
    @SerializedName("lat") public String lat;
    @SerializedName("lon") public String lon;
}