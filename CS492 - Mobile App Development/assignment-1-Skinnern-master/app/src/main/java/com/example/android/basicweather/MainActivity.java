package com.example.android.basicweather;

import android.content.Context;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayDeque;



public class MainActivity extends AppCompatActivity {
    private RecyclerView mRecyclerView;




    private final String[] Weather = new String[] {
            "Wed April 12 - Sunny and Warm - 75F",
            "Thu April 13 - Cold and Rainy - 45F",
            "Fri April 14 - Cold and Snowy - 25F",
            "Sat April 15 - Excessively Cold - 0F",
            "Sun April 16 - Cold and Snowy - 25F",
            "Mon April 17 - Cold and Rainy - 45F",
            "Tue April 18 - Sunny and Warm - 75F",
            "Wed April 19 - Sunny and Hot - 95F",
            "Thu April 20 - Unbearably Hot - 150F",
            "Fri April 21 - Sunny and Hot - 95F",
            "Sat April 22 - Sunny and Warm - 75F",
            "Sun April 23 - Cold and Rainy - 45F",
            "Mon April 24 - Cold and Snowy - 25F",
            "Tue April 25 - Excessively Cold - 0F",
            "Wed April 26 - Cold and Snowy - 25F",
            "Thu April 27 - Cold and Rainy - 45F",
            "Fri April 28 - Sunny and Warm - 75F"
    };






    private final String[] WeatherInfo = new String[] {
            "Cloudless and generally warm, with a high of 75F and a low of 57F.  Some high clouds late in the day.",
            "Very Cloudy with high likelihood of rain, high of 45 and low of 36. Don't expect to see the sun.",
            "Unexpected excessive wind chill in area. Lots of snow, High 25, low 13. Beware black ice",
            "Well below freezing, High of 0, low of who knows what. Bundle up and keep very warm.",
            "Recovering from excessive wind chill in area. Lots of snow, High 25, low 13. Beware black ice",
            "Very Cloudy with high likelihood of rain, high of 45 and low of 36. Don't expect to see the sun.",
            "Cloudless and generally warm, with a high of 75F and a low of 57F.  Some high clouds late in the day.",
            "Heat wave warning, high temperatures, high of 95, low of 83. Try to keep cool and stay inside.",
            "Extremely hot outdoors, high of 150F, Do not go outside unless necessary.",
            "Heat wave warning, high temperatures, high of 95, low of 83. Try to keep cool and stay inside.",
            "Cloudless and generally warm, with a high of 75F and a low of 57F.  Some high clouds late in the day.",
            "Very Cloudy with high likelihood of rain, high of 45 and low of 36. Don't expect to see the sun.",
            "Recovering from excessive wind chill in area. Lots of snow, High 25, low 13. Beware black ice",
            "Well below freezing, High of 0, low of who knows what. Bundle up and keep very warm.",
            "It is wednesday, my dudes.",
            "Very Cloudy with high likelihood of rain, high of 45 and low of 36. Don't expect to see the sun.",
            "Cloudless and generally warm, with a high of 75F and a low of 57F.  Some high clouds late in the day."
    };






    private class WeatherViewHolder
            extends RecyclerView.ViewHolder
            implements View.OnClickListener {

        public WeatherViewHolder(View v) {
            super(v);
            v.setOnClickListener(this);
        }

        @Override
        public void onClick(View v) {

            int pos = 0;
            mRecyclerView.findViewHolderForAdapterPosition(pos);
            String posString = String.valueOf(pos);
            /*

*/
            String string = ((TextView) v ).getText().toString();

            for(int i = 0; i<WeatherInfo.length; i++){
                if (string == Weather[i]){
                    string = WeatherInfo[i];
                    int temp;
                    temp = WeatherInfo.length - i;
                    i= i+temp;
                }

            }



            Toast.makeText(getApplicationContext(),
                    string/*((TextView) v ).getText()*/,
                    Toast.LENGTH_LONG).show();
        }

    }





    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mRecyclerView = (RecyclerView) findViewById(R.id.recycler_view);
        mRecyclerView.setLayoutManager(new LinearLayoutManager(this));
        mRecyclerView.setAdapter(new RecyclerView.Adapter<WeatherViewHolder>() {

            @Override
            public WeatherViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
                View v = LayoutInflater.from(parent.getContext()).inflate(
                        android.R.layout.simple_list_item_1,
                        parent,
                        false);
                WeatherViewHolder vh = new WeatherViewHolder(v);
                return vh;
            }

            @Override
            public void onBindViewHolder(WeatherViewHolder vh, int position) {
                TextView tv = (TextView) vh.itemView;
                tv.setText(Weather[position]);
                //tv.setText(WeatherInfo[position]);
                tv.setCompoundDrawablePadding(24);
            }

            @Override
            public int getItemCount() {
                return Weather.length;
            }
        });
    }
}
/*

public class MainActivity extends AppCompatActivity {
    //private TextView mTodoListTextView;
    private EditText mTodoEntryEditText;
    private ArrayDeque<String> mTodoList;
    private ArrayDeque<String> WeatherInfo;
    private RecyclerView WeatherInfoRecyclerView;
    private TodoAdapter mTodoAdapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        //WeatherInfoRecyclerView.setLayoutManager(new LinearLayoutManager(this));
        //WeatherInfoRecyclerView.setHasFixedSize(true);


        WeatherInfo = new ArrayDeque<String>();
        mTodoAdapter = new TodoAdapter();


        /*TextView todoListTextView =
                (TextView)findViewById(R.id.tv_todo_list);*/
        //todoListTextView.setText("Finish my TODO app.");
        /*mTodoListTextView =
                (TextView)findViewById(R.id.tv_todo_list);*/
        //mTodoListRecyclerView.setLayoutManager(new LinearLayoutManager(this));
        //mTodoListRecyclerView.setHasFixedSize(true);


    /*
        mTodoEntryEditText =
                (EditText)findViewById(R.id.et_todo_entry_box);
        Button addTodoButton =
                (Button)findViewById(R.id.btn_add_todo);

                */



        //WeatherInfoRecyclerView.setAdapter(mTodoAdapter);
/*
        mTodoListRecyclerView.setAdapter(mTodoAdapter);
        addTodoButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String todoText =
                        mTodoEntryEditText.getText().toString();
                if (!TextUtils.isEmpty(todoText)) {
                    WeatherInfo.addTodo(todoText);
                    mTodoEntryEditText.setText("");
                }
            }

        });
        */
/*

    }



}
*/