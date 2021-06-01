package com.jblearning.candystorev5;

import android.app.Dialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Point;
import android.os.Bundle;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;
import android.widget.Toast;

import com.jblearning.candystorev5.DatabaseManager;
import com.jblearning.candystorev5.R;

import org.w3c.dom.Text;

import java.text.NumberFormat;
import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {
    private DatabaseManager dbManager;
    private verification dataValid;
    private final Context context = this;
    Button getInfo, submit;
    EditText cardNumber, cvc, firstName, lastName, middleInitial, expdatemonth, expdateyear;
    EditText state, zipCode,address, city;
    RadioGroup cardType;

    private void testData() {
        cardNumber.setText("1111222233334444");
        cvc.setText("123");
        firstName.setText("John");
        middleInitial.setText("A");
        lastName.setText("Doe");
        expdatemonth.setText("12");
        expdateyear.setText("31");
        address.setText("10 Clarkson Ave");
        city.setText("Potsdam");
        state.setText("NY");
        zipCode.setText("13699");
        cardType.check(R.id.ten);
    }
////
//    private void testData2() {
//        cardNumber.setText("1111222233334445");
//        cvc.setText("123");
//        firstName.setText("John");
//        middleInitial.setText("B");
//        lastName.setText("Doe");
//        expdatemonth.setText("12");
//        expdateyear.setText("31");
//        address.setText("10 Clarkson Ave");
//        city.setText("Potsdam");
//        state.setText("NY");
//        zipCode.setText("13699");
//        cardType.check(R.id.ten);
//    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        cardNumber = (EditText) findViewById(R.id.info_card_number);
        cvc = (EditText) findViewById(R.id.info_cvc);
        firstName = (EditText) findViewById(R.id.info_first_name);
        lastName = (EditText) findViewById(R.id.info_last_name);
        middleInitial = (EditText) findViewById(R.id.info_middle_name);
        expdatemonth = (EditText) findViewById(R.id.info_exp_month);
        expdateyear = (EditText) findViewById(R.id.info_exp_year);
        address = (EditText) findViewById(R.id.info_address);
        city = (EditText) findViewById(R.id.info_city);
        state = (EditText) findViewById(R.id.info_state);
        zipCode = (EditText) findViewById(R.id.info_zip_code);
        cardType = (RadioGroup) findViewById(R.id.card_type);
        getInfo = (Button) findViewById(R.id.get_info);
        submit = (Button) findViewById(R.id.submit);
        dbManager = new DatabaseManager(this);
        dataValid = new verification();
        testData();

        View.OnClickListener ButtonFunction = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Button b = (Button) v;
                if (b.getId() == getInfo.getId()) {
                    getInfoFunc();
                } else if (b.getId() == submit.getId()) {
                    inputSubmit();
                }
            }
        };

        getInfo.setOnClickListener(ButtonFunction);
        submit.setOnClickListener(ButtonFunction);

    }

    private void getInfoFunc(){
        AlertDialog.Builder builder = new AlertDialog.Builder(context);
        View dialog = View.inflate(context, R.layout.get_info_dialog, null);
        builder.setView(dialog);
        builder.setCancelable(false);
        final EditText getCardNumber = (EditText) dialog.findViewById(R.id.get_info_card_number);
        final EditText getCVC = (EditText) dialog.findViewById(R.id.get_info_cvc);
        builder.setPositiveButton("SEARCH", new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int id) {
                long searchNumber = Long.parseLong("1111222233334444");
                int searchCVC = 123;
                if (!(checkEmpty(getCardNumber) || checkEmpty(getCVC))) {
                    searchNumber = Long.parseLong(getCardNumber.getText().toString());
                    searchCVC = Integer.parseInt(getCVC.getText().toString());
                }
                Card searchCard = dbManager.searchData(searchNumber, searchCVC);
                String message;
                if(searchCard == null) {
                    message = "Not Found!";
                }
                else{
                    message = searchCard.Name + '\n' + searchCard.Address;
                }
                final Dialog showInfo = new Dialog(context);
                showInfo.setTitle("Search Results");
                TextView showMessage = new TextView(context);
                showMessage.setText(message);
                showInfo.setContentView(showMessage);
                showInfo.show();
            }
        });
        builder.setNegativeButton("CANCEL", new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int id) {
                dialog.dismiss();
            }
        });
        final AlertDialog alert = builder.create();
        alert.setOnShowListener(new DialogInterface.OnShowListener() {
            @Override
            public void onShow(DialogInterface arg0) {
                alert.getButton(AlertDialog.BUTTON_POSITIVE).setTextColor(getResources().getColor(R.color.colorPrimaryDark));
                alert.getButton(AlertDialog.BUTTON_POSITIVE).setTextSize(20);
            }
        });
        alert.show();
    }

    private void inputSubmit(){
        //Get Data from User
        EditText[] allInputs = {cardNumber, cvc, firstName, lastName, middleInitial, expdatemonth,
                expdateyear, address, city, state, zipCode};

        if (validateInput(allInputs)) {
            RadioButton ctype = (RadioButton) findViewById(cardType.getCheckedRadioButtonId());
//            //Create Card
            Card inCard = new Card(
                    firstName.getText().toString(),
                    middleInitial.getText().toString(),
                    lastName.getText().toString(),
                    address.getText().toString(),
                    city.getText().toString(),
                    state.getText().toString(),
                    zipCode.getText().toString(),
                    expdatemonth.getText().toString(),
                    expdateyear.getText().toString(),
                    ctype.getText().toString(),
                    Integer.parseInt(cvc.getText().toString()),
                    Long.parseLong(cardNumber.getText().toString())
            );

            //Insert Card
            dbManager.insert(inCard);

            //Clear Data
            for (int k = 0; k < allInputs.length; k++) {
                allInputs[k].setText("");
            }
            alertMessage("Information Submitted");
        }
    }

    private String ViewName(EditText v){
        String objName = "";
        switch (v.getId()){
            case R.id.info_address: objName = "Address"; break;
            case R.id.info_card_number: objName = "Card Number"; break;
            case R.id.info_city: objName = "City"; break;
            case R.id.info_cvc: objName = "CVC"; break;
            case R.id.info_exp_month: objName = "Expiration Month"; break;
            case R.id.info_exp_year: objName = "Expiration Year"; break;
            case R.id.info_first_name: objName = "First Name"; break;
            case R.id.info_last_name: objName = "Last Name"; break;
            case R.id.info_middle_name: objName = "Middle Name"; break;
            case R.id.info_state: objName = "State"; break;
            case R.id.info_zip_code: objName = "Zip Code"; break;
            default: objName = "";break;
        }
        return objName;
    }

    private boolean validateInput(EditText[] allInputs) {
        boolean valid = true;
        String errorMessage = "";
        for (int i = 0; i < allInputs.length; i++) {
            if (checkEmpty(allInputs[i])) {
                errorMessage += ViewName(allInputs[i]) + " is Empty" + '\n';
                valid = false;
            }
            else{
                switch(allInputs[i].getId()){
                    case R.id.info_card_number:
                        if(!dataValid.verCard(lazyText(allInputs[i])))
                        {
                            valid = false;
                            errorMessage += ViewName(allInputs[i]) + " has incorrect length" + '\n';
                        }
                        break;
                    case R.id.info_cvc:
                        if(!dataValid.verCVC(lazyText(allInputs[i])))
                        {
                            valid = false;
                            errorMessage += ViewName(allInputs[i]) + " has incorrect length" + '\n';
                        }
                        break;
                    case R.id.info_state:
                        if(!dataValid.verState(lazyText(allInputs[i])))
                        {
                            valid = false;
                            errorMessage += ViewName(allInputs[i]) + " does not exist" + '\n';
                        }
                        break;
                    case R.id.info_address:
                        if(!dataValid.verAddress(lazyText(allInputs[i]))) {
                            valid = false;
                            errorMessage += ViewName(allInputs[i]) + " invalid format" + '\n';
                        }
                        break;
                    case R.id.info_exp_year:
                        if(!dataValid.verYear(lazyText(allInputs[i])))
                        {
                            valid = false;
                            errorMessage += ViewName(allInputs[i]) + " invalid format" + '\n';
                        }
                        break;
                    case R.id.info_exp_month:
                        if(!dataValid.verMonth(lazyText(allInputs[i])))
                        {
                            valid = false;
                            errorMessage += ViewName(allInputs[i]) + " invalid format" + '\n';
                        }
                        break;
                }
            }
        }

        if(!valid){
//            final Dialog showError = new Dialog(context);
//            showError.setTitle("Invalid Information");
//            TextView showMessage = new TextView(context);
//            showMessage.setTextSize(20);
//            showMessage.setText(errorMessage);
//            showError.setContentView(showMessage);
//            showError.show();
            alertMessage(errorMessage);
        }

        return valid;
    }

    private int inputLength(EditText v){
        return v.getText().toString().trim().length();
    }

    private boolean checkEmpty(EditText v) {
        if (inputLength(v) > 0) {
            return false;
        } else {
            return true;
        }
    }

    private String lazyText(EditText input){
        return input.getText().toString();
    }

    private void alertMessage (String mess){
        AlertDialog.Builder builder = new AlertDialog.Builder(context);
        builder.setMessage(mess)
                .setCancelable(false)
                .setPositiveButton("X", new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int id) {
                        //do things
                    }
                });
        AlertDialog alert = builder.create();
        alert.show();

    }

}