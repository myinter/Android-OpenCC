package com.example.xiongwei.androidopencc;

import android.renderscript.Script;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import androidopencc.AndroidOpenCC;

public class MainActivity extends AppCompatActivity {
    TextView mOutputTV;
    EditText mInputText;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        AndroidOpenCC.getInstance().ConvertSimpleTextToTraditional("我是爱你的啊。。");
        AndroidOpenCC.getInstance().ConvertTradTextToSimplized("我是愛你的啊");
        Button btn = (Button)findViewById(R.id.btn);

        mOutputTV = (TextView)findViewById(R.id.outputTV);
        mInputText = (EditText)findViewById(R.id.editText);

        mInputText.setText(AndroidOpenCC.getInstance().ConverSimpleToCorrespondingTradChar(mInputText.getText().toString()));

        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mOutputTV.setText(AndroidOpenCC.getInstance().ConvertSimpleTextToTraditional(mInputText.getText().toString()));
            }
        });
        btn = (Button)findViewById(R.id.txjieengToKanBtn);
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mOutputTV.setText(AndroidOpenCC.getInstance().ConvertTradTextToSimplized(mInputText.getText().toString()));
            }
        });
    }
}
