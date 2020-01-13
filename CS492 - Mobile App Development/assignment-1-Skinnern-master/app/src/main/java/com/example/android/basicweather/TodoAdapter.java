package com.example.android.basicweather;

import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import java.util.ArrayList;

public class TodoAdapter extends RecyclerView.Adapter<TodoAdapter.TodoViewHolder> {
    private ArrayList<String> mTodoList;
    private RecyclerView mTodoListRecyclerView;

    private ArrayList<String> Weather;
    private ArrayList<String> WeatherDetail;

    private TodoAdapter mTodoAdapter;


    public TodoAdapter() {

        mTodoList = new ArrayList<String>();
        Weather = new ArrayList<String>();
        WeatherDetail = new ArrayList<String>();
    }

    public void addTodo(String todo) {
        mTodoList.add(todo);
        notifyDataSetChanged();
    }


    public void WeatherInfo () {
        Weather.add("Wed April 12 - Sunny and Warm - 75F");
        WeatherDetail.add("Cloudless and generally warm, with a high of 75F and a low of 57F.  Some high clouds late in the day.");
    }

    @Override
    public int getItemCount() {
        return mTodoList.size();
    }


    class TodoViewHolder extends RecyclerView.ViewHolder {
        private TextView mTodoTextView;
        public TodoViewHolder(View itemView) {
            super(itemView);
            mTodoTextView =
                    (TextView)itemView.findViewById(R.id.tv_todo_text);
        }

        void bind(String todo) {
            mTodoTextView.setText(todo);
        }

    }


    @Override
    public TodoViewHolder onCreateViewHolder(ViewGroup viewGroup,
                                             int viewType) {
        LayoutInflater inflater =
                LayoutInflater.from(viewGroup.getContext());
        View view = inflater.inflate(R.layout.todo_list_item, viewGroup,
                false);
        TodoViewHolder viewHolder = new TodoViewHolder(view);
        return viewHolder;
    }

    @Override
    public void onBindViewHolder(TodoViewHolder holder,
                                 int position) {
        String todo =
                mTodoList.get(mTodoList.size() - position - 1);
        holder.bind(todo);
    }


}

