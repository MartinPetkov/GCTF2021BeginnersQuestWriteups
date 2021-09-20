package gctf.researchctf;


import android.app.Activity;

import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;


import java.io.File;
import java.io.FileOutputStream;

import static android.os.Environment.DIRECTORY_DOWNLOADS;

public class MainActivity extends Activity {
    private EditText tv = null;
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);
        try{
            File bf = new File(Environment.getExternalStoragePublicDirectory(DIRECTORY_DOWNLOADS), "Raven.txt");
            File f = new File(getApplicationContext().getFilesDir(), "SusanSue.txt");
            FileOutputStream fos = new FileOutputStream(f);
            fos.write("Sctf:key:".getBytes());
            fos.close();
            FileOutputStream bkfos = new FileOutputStream(bf);
            bkfos.write("BKUP:KEY:SecretKey:P@$$".getBytes());
            bkfos.close();

        }catch(Exception e){
            e.printStackTrace();
        }
        tv = findViewById(R.id.editTextTextPersonName);
        tv.setText(stringFromJNI());
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native String getCTF(String enteredKey);

    public native int validateCTF(String enteredKey);

    public void read(View view) {
        try{
            File f = new File(getApplicationContext().getFilesDir(), "SusanSue.txt");
            int s = validateCTF(tv.getText().toString());
            if(s == 0){
                Log.v("WATCHOUT", "You are the winner");
                Toast.makeText(getApplicationContext(), "YOU ARE THE WINNER!!!!", Toast.LENGTH_LONG).show();
            }else{
                Log.v("WATCHOUT", "Please keep trying");
                Toast.makeText(getApplicationContext(), "Please keep trying!!!!", Toast.LENGTH_LONG).show();
            }
        }catch (Exception e){
            e.printStackTrace();
        }

    }
}