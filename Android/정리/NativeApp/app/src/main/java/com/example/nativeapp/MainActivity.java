package com.example.nativeapp;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("ndktest");
    }

    public native String getJNIString();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView jniText = (TextView)findViewById(R.id.jniText);
        jniText.setText(getJNIString());
    }
}
