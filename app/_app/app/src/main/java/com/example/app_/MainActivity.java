package com.example.app_;

import androidx.activity.result.contract.ActivityResultContracts;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.Manifest;
import android.annotation.SuppressLint;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothManager;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ImageButton;
import android.widget.ListView;
import android.widget.TextView;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.util.Set;
import java.util.UUID;

public class MainActivity extends AppCompatActivity {

    ImageButton butt, bt_butt;
    TextView y;
    ListView lw;
    BluetoothAdapter bA;

    private BluetoothSocket btSocket;
    private DataInputStream dataInputStream;
    private DataOutputStream dataOutputStream;
    private boolean isConnected = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        butt = (ImageButton) findViewById(R.id.butt);
        bt_butt = (ImageButton) findViewById(R.id.bt_button);
        y = (TextView) findViewById(R.id.y_text);
        lw = (ListView) findViewById(R.id.list);

        bA = BluetoothAdapter.getDefaultAdapter();
        connectDevice("14:2B:2F:C4:EF:EA");
        sendMessage("2");


    }

    public void connectDevice(String address) {
        BluetoothDevice device = bA.getRemoteDevice(address);
        UUID uuid = UUID.fromString("00001101-0000-1000-8000-00805f9b34fb");
        try {
            if (ActivityCompat.checkSelfPermission(this, Manifest.permission.BLUETOOTH_CONNECT) != PackageManager.PERMISSION_GRANTED) {
                // TODO: Consider calling
                //    ActivityCompat#requestPermissions
                // here to request the missing permissions, and then overriding
                //   public void onRequestPermissionsResult(int requestCode, String[] permissions,
                //                                          int[] grantResults)
                // to handle the case where the user grants the permission. See the documentation
                // for ActivityCompat#requestPermissions for more details.
                return;
            }
            btSocket = device.createRfcommSocketToServiceRecord(uuid);
            if (ActivityCompat.checkSelfPermission(this, Manifest.permission.BLUETOOTH_SCAN) != PackageManager.PERMISSION_GRANTED) {
                // TODO: Consider calling
                //    ActivityCompat#requestPermissions
                // here to request the missing permissions, and then overriding
                //   public void onRequestPermissionsResult(int requestCode, String[] permissions,
                //                                          int[] grantResults)
                // to handle the case where the user grants the permission. See the documentation
                // for ActivityCompat#requestPermissions for more details.
                return;
            }
            bA.cancelDiscovery();
            btSocket.connect();
            dataInputStream = new DataInputStream(btSocket.getInputStream());
            dataOutputStream = new DataOutputStream(btSocket.getOutputStream());
            isConnected = true;
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void sendMessage(String message) {
        if (isConnected) {
            try {
                dataOutputStream.writeUTF(message);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public void receiveMessage() {
        if (isConnected) {
            try {
                String incomingMessage = dataInputStream.readUTF();
                Log.d("Bluetooth", incomingMessage);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
