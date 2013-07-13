package com.lossboys.customerapp;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.StrictMode;
import android.view.Gravity;
import android.view.View;
import android.view.WindowManager;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.List;

import org.apache.http.NameValuePair;
import org.apache.http.message.BasicNameValuePair;
import org.json.JSONObject;

import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.Toast;

public class CustomerLogin extends Activity {

	Button btnLogin;
	Button btnLinkToRegister;
	EditText inputEmail;
	EditText inputPassword;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		if (android.os.Build.VERSION.SDK_INT > 9) {
			StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
			StrictMode.setThreadPolicy(policy);
		}

		getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_ALWAYS_HIDDEN);

		super.onCreate(savedInstanceState);

		// Check to see if already logged in
		List<NameValuePair> nameValuePair = new ArrayList<NameValuePair>(0);
		JSONObject checkJSON = CustomHTTP.makePOST("http://23.21.158.161:4912/check_login.php", nameValuePair);
		if (checkJSON != null) {
			try {
				String jsonResult = checkJSON.getString("login");
				if (jsonResult.equals("true")) {
					Intent i = new Intent(getApplicationContext(), com.lossboys.customerapp.dashboard.CustomerDashboard.class);
					startActivity(i);
					finish();
				}
			} catch (Exception e) {
				e.printStackTrace();
			}
		}

		setContentView(R.layout.customer_login);

		// Importing all assets like buttons, text fields
		inputEmail = (EditText) findViewById(R.id.loginEmail);
		inputPassword = (EditText) findViewById(R.id.loginPassword);
		btnLogin = (Button) findViewById(R.id.btnLogin);
		btnLinkToRegister = (Button) findViewById(R.id.btnLinkToRegisterScreen);

		// Set up the user interaction to manually show or hide the system UI.
		btnLogin.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View view) {
				String email = inputEmail.getText().toString();
				String password = inputPassword.getText().toString();
				Context context = CustomerLogin.this;
				CharSequence text = "";
				int duration = Toast.LENGTH_SHORT;
				boolean done = false;

				// Building post parameters
				// key and value pair
				List<NameValuePair> nameValuePair = new ArrayList<NameValuePair>(2);
				nameValuePair.add(new BasicNameValuePair("email", email));
				nameValuePair.add(new BasicNameValuePair("password", password));

				JSONObject loginJSON = CustomHTTP.makePOST("http://23.21.158.161:4912/login.php", nameValuePair);

				if (loginJSON != null) {
					try {
						String jsonResult = loginJSON.getString("login");
						if (jsonResult.equals("false"))
							text = "Invalid email or password!";
						else {
							done = true;
							Intent i = new Intent(getApplicationContext(), com.lossboys.customerapp.dashboard.CustomerDashboard.class);
							startActivity(i);
							finish();
						}
					} catch (Exception e) {
						e.printStackTrace();
						text = "Login failed.";
					}
				} else
					text = "Login failed.";

				Toast toast = Toast.makeText(context, text, duration);
				LinearLayout toastLayout = (LinearLayout) toast.getView();
				TextView toastTV = (TextView) toastLayout.getChildAt(0);
				toastTV.setTextSize(20);
				toast.setGravity(Gravity.CENTER, 0, 0);
				if(!done)
					toast.show();
			}
		});

		btnLinkToRegister.setOnClickListener(new View.OnClickListener() {
			public void onClick(View view) {
				Intent i = new Intent(getApplicationContext(), CustomerRegister.class);
				startActivity(i);
			}
		});
	}
}
