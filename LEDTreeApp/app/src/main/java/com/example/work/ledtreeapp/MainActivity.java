package com.example.work.ledtreeapp;
import android.app.Activity;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.Spinner;
import android.widget.Toast;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.DataOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.URL;

public class MainActivity extends Activity {

    private RadioGroup soundGroup, lightsGroup;
    private Spinner animationModeSpinner;
    private static String httpLogger= "HTTPLOGGER";
    String[] animation={ "Spectrum","Red/Green Strips","Red Green Level","Random LED","Ring"};

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        //setSupportActionBar(toolbar);

        //FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
//        fab.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View view) {
//                Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
//                        .setAction("Action", null).show();
//            }
//        });

        /* initialize the sound group*/
        soundGroup = (RadioGroup)findViewById(R.id.soundGroup);
        soundGroup.check(R.id.play);
        /* Attach CheckedChangeListener to radio group */
        soundGroup.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(RadioGroup group, int checkedId) {
                RadioButton rb = (RadioButton) group.findViewById(checkedId);
                if (null != rb && checkedId > -1) {
                    //Toast.makeText(MainActivity.this, rb.getText(), Toast.LENGTH_SHORT).show();
                    if (checkedId == R.id.play) {
                        Toast.makeText(MainActivity.this, "Sound is now playing", Toast.LENGTH_SHORT).show();
                        jsonCreator("PLAY",1);
                    }
                    if (checkedId == R.id.pause) {
                        Toast.makeText(MainActivity.this, "Sound is now paused", Toast.LENGTH_SHORT).show();
                        jsonCreator("PAUSE", 1);
                    }
                }

            }
        });
        /*
        initialize the Lights group
         */
        lightsGroup = (RadioGroup)findViewById(R.id.ledGroup);
        lightsGroup.check(R.id.LEDOn);
        /* Attach CheckedChangeListener to radio group */
        lightsGroup.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener(){
            @Override
            public void onCheckedChanged(RadioGroup group, int checkedId){

                RadioButton rb = (RadioButton) group.findViewById(checkedId);

                if (null != rb && checkedId > -1) {
                    if(checkedId==R.id.LEDOn){
                        Toast.makeText(MainActivity.this, "Lights are on", Toast.LENGTH_SHORT).show();
                        jsonCreator("LED", 1);
                    }
                    if(checkedId==R.id.LEDOff){
                        Toast.makeText(MainActivity.this, "Lights are off", Toast.LENGTH_SHORT).show();
                        jsonCreator("LED", 0);
                    }
                }

            }
        });

        /* initialize the spinner*/
        //Set up the adapter
        //ArrayAdapter<String>adapter = new ArrayAdapter<String>(this,android.R.layout.simple_spinner_item, animation);
        ArrayAdapter<String>adapter = new ArrayAdapter<String>(this,R.layout.custom_spinner, animation);
        animationModeSpinner=(Spinner) findViewById(R.id.animationSpinner);
        animationModeSpinner.setAdapter(adapter);

        animationModeSpinner.setOnItemSelectedListener(
                new AdapterView.OnItemSelectedListener() {

                    @Override
                    public void onItemSelected(AdapterView<?> arg0, View arg1,
                                               int arg2, long arg3) {

                        int position = animationModeSpinner.getSelectedItemPosition();
                        Toast.makeText(getApplicationContext(), "You have selected " + animation[+position], Toast.LENGTH_LONG).show();
                        //TODO
                        // Add a switch-case statement for each position in the animation String Array
                        // Add a method to package into a JSON object

                        String jsonText="";
                        //"Spectrum","Red/Green Strips","Red Green Level","Random LED","Ring"
                        switch(position){
                            //SPECTRUM
                            case 0:jsonText= "SPECTRUM";
                                break;
                            //RG Strips
                            case 1:jsonText= "RGSTRIPS";
                                break;
                            //RG Level
                            case 2:jsonText= "RGLEVEL";
                                break;
                            //Random
                            case 3:jsonText= "RANDOM";
                                break;
                            //Ring
                            case 4:jsonText= "RING";
                                break;
                        }
                        int value=1;
                        jsonCreator(jsonText,value);
                    }

                    @Override
                    public void onNothingSelected(AdapterView<?> arg0) {

                    }

                }
        );


    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }


    private void jsonCreator(String jsonParameter,int value){

        try{
            JSONObject jsonObject = new JSONObject();
            jsonObject.put(jsonParameter, value);

            new sendRequest().execute(jsonObject.toString());
            //sendRequest(jsonObject.toString());
            Toast.makeText(MainActivity.this, "Sent to sendRequest()", Toast.LENGTH_SHORT).show();
        }
        catch(JSONException e){
            Toast.makeText(MainActivity.this, "Error: Unable to create JSONObject with"+jsonParameter, Toast.LENGTH_SHORT).show();
        }
    }

    public static class sendRequest extends AsyncTask<String, Void, Void> {
        @Override

        protected Void doInBackground(String... params) {
            //TODO: Get this to work
            String address = "http://192.168.1.14:9000/";
//            String address = "http://192.168.202.89:9000/";
            String data =params[0].toString();
            Log.v(httpLogger,"Data of params[0] is: "+data);
            //Toast.makeText(MainActivity.this, "JSON OBJECT: "+jsonObject, Toast.LENGTH_SHORT).show();
            HttpURLConnection urlConnection=null;
            DataOutputStream outputStream;
            try{
                Log.v(httpLogger, "Attempting to connect to PI");
                //Setup URLconnection

                URL url = new URL(address);
                urlConnection= (HttpURLConnection) (url.openConnection());

                urlConnection.setDoInput(true);
                urlConnection.setDoOutput(true);
                urlConnection.setRequestMethod("POST");
                urlConnection.setRequestProperty("Content-Type","application/json");
                //set timeout to be 10000ms
                urlConnection.setReadTimeout(10000);

                urlConnection.connect();

                Log.v(httpLogger, "url connection: " + urlConnection);
                Log.v(httpLogger, "Connected to PI");

                //Write JSON data to an output stream
                OutputStreamWriter writer = new OutputStreamWriter(urlConnection.getOutputStream());
//                BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(os, "UTF-8"));
                writer.write(data);
                Log.v(httpLogger, "Full data: " + writer);
                writer.flush();
                Log.v(httpLogger, "writer flushed");
                writer.close();
                Log.v(httpLogger, "writer closed");
                Log.v(httpLogger, "THe outputtream: "+urlConnection.getOutputStream());

                //Get the status code from the HTPP connection
                if(urlConnection.getResponseCode()==HttpURLConnection.HTTP_OK){
                    Log.v(httpLogger,"SUCCESS???");
                }else{
                    Log.v(httpLogger,"Something bad happened: "+urlConnection.getResponseCode());
                }

            }
            catch (UnsupportedEncodingException e) {
                Log.e(httpLogger,e.toString());
                e.printStackTrace();
            }
            catch (IOException e) {
                Log.e(httpLogger,e.toString());
                e.printStackTrace();
            }
            finally{
                //Close the URL Connection
                //urlConnection.connect();
                urlConnection.disconnect();
                Log.v(httpLogger, "Connection disconnected");

            }

            return null;
        }
    }

}
