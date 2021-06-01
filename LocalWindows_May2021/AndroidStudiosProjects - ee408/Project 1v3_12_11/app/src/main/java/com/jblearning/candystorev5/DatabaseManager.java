package com.jblearning.candystorev5;

import android.content.ContentResolver;
import android.content.Context;
import android.database.CharArrayBuffer;
import android.database.ContentObserver;
import android.database.Cursor;
import android.database.DataSetObserver;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.net.Uri;
import android.os.Bundle;

import java.util.ArrayList;

///SQL TEST COMMANDS////
//create table CreditCardInfo( id integer primary key autoincrement, name text,CreditCardNumber bigint,CVC int,CardType text,ExpirationDate text,BillingAddress text);
//insert into CreditCardInfo values(null, 'Doe John A.','1111222233334444','123','Mastercard','12/31','10 Clarkson Ave, Potsdam, NY, 13699');

public class DatabaseManager extends SQLiteOpenHelper {
  private static final String DATABASE_NAME = "CreditCardDB";
  private static final int DATABASE_VERSION = 2;
  private static final String TABLE_CARD = "CreditCardInfo";
  private static final String ID = "id";
  private static final String NAME = "name";
  private static final String CARDNUM = "CreditCardNumber";
  private static final String CVC = "CVC";
  private static final String CARDTYPE = "CardType";
  private static final String EXPDATE = "ExpirationDate";
  private static final String ADDRESS = "BillingAddress";


  public DatabaseManager(Context context) {
    super(context, DATABASE_NAME, null, DATABASE_VERSION);
  }

    public void onUpgrade(SQLiteDatabase db,
                          int oldVersion, int newVersion) {
        // Drop old table if it exists
        db.execSQL("drop table if exists " + TABLE_CARD);
        // Re-create tables
        onCreate(db);
    }

    //db.execSQL("create table CreditCardInfo( id integer primary key autoincrement, name text,CreditCardNumber bigint,CVC int,CardType text,ExpirationDate text,BillingAddress text)");

    public void onCreate( SQLiteDatabase db ) {
    // build sql create statement
    String sqlCreate = "create table " + TABLE_CARD + "( " + ID ;
    sqlCreate += " integer primary key autoincrement, ";
    sqlCreate += NAME + " text, ";
    sqlCreate += CARDNUM + " numeric, ";
    sqlCreate += CVC + " int, ";
    sqlCreate += CARDTYPE + " text, ";
    sqlCreate += EXPDATE + " text, ";
    sqlCreate += ADDRESS + " text )";
//    sqlCreate += ");";

    db.execSQL( sqlCreate );

  }
    public void insert( Card card ) {
        SQLiteDatabase db = this.getWritableDatabase( );
        String sqlInsert = "insert into " + TABLE_CARD;
        sqlInsert += " values(null, '" + card.Name;
        sqlInsert += "','" + card.Number;
        sqlInsert += "','" + card.CVC;
        sqlInsert += "','" + card.CardType;
        sqlInsert += "','" + card.ExpDate;
        sqlInsert += "','" + card.Address;
        sqlInsert += "');";

        db.execSQL( sqlInsert );

        db.close( );
    }

  public Card searchData(long cardnum, int CVC)
  {
    SQLiteDatabase db = this.getWritableDatabase();
    String sqlQuery = "select * from " + TABLE_CARD;
    sqlQuery += " WHERE " + CARDNUM + " = " + cardnum;
    sqlQuery += " AND " + CVC + " = " + CVC;

    Cursor cursor = db.rawQuery( sqlQuery, null );
    Card searchCard;
    if(cursor.moveToFirst()){
        searchCard = new Card(
                cursor.getString(1),
                cursor.getString(6),
                cursor.getString(5),
                cursor.getString(4),
                cursor.getInt(3),
                cursor.getLong(2)
        );
    }
    else
    {
        searchCard = null;
    }
    db.close();
    return searchCard;
  }

}