//package com.jblearning.candystorev5;
//
//import android.content.Context;
//import android.database.Cursor;
//import android.database.sqlite.SQLiteDatabase;
//import android.database.sqlite.SQLiteOpenHelper;
//
//import java.util.ArrayList;
//
//public class TransactionsManager extends SQLiteOpenHelper {
//  private static final String DATABASE_NAME = "transactionsDB";
//  private static final int DATABASE_VERSION = 1;
//  private static final String TABLE_TRANSACTIONS = "transactions";
//  private static final String ID = "id";
//  private static final String TOTAL = "total";
//  private float TotalRevenue = 0;
//
//  public TransactionsManager(Context context ) {
//    super( context, DATABASE_NAME, null, DATABASE_VERSION );
//  }
//
//  public void onCreate( SQLiteDatabase db ) {
//    // build sql create statement
//    String sqlCreate = "create table " + TABLE_TRANSACTIONS + "( " + ID;
//    sqlCreate += " integer primary key autoincrement, ";
//    sqlCreate += " text, " + TOTAL + " real )" ;
//
//    db.execSQL( sqlCreate );
//  }
//
//  public void onUpgrade( SQLiteDatabase db,
//                         int oldVersion, int newVersion ) {
//    // Drop old table if it exists
//    db.execSQL( "drop table if exists " + TABLE_TRANSACTIONS );
//    // Re-create tables
//    onCreate( db );
//  }
//
//  public void insert( float transactionTotal ) {
//    TotalRevenue += transactionTotal;
//    SQLiteDatabase db = this.getWritableDatabase( );
//    String sqlInsert = "insert into " + TABLE_TRANSACTIONS + " values( null, '";
//    sqlInsert += "', '" + transactionTotal + "' )";
//
//    db.execSQL( sqlInsert );
//    db.close( );
//  }
//
//  public float selectById( int id ) {
//    String sqlQuery = "select * from " + TABLE_TRANSACTIONS;
//    sqlQuery += " where " + ID + " = " + id;
//
//    SQLiteDatabase db = this.getWritableDatabase( );
//    Cursor cursor = db.rawQuery( sqlQuery, null );
//
//    float transactionValue = 0;
//    if( cursor.moveToFirst( ) )
//      transactionValue = Float.parseFloat( cursor.getString( 1 ) );
//    return transactionValue;
//  }
//
//  public float totalRevenue(){
//    return TotalRevenue;
//  }
//
//
//  //  public void deleteById( int id ) {
////    SQLiteDatabase db = this.getWritableDatabase( );
////    String sqlDelete = "delete from " + TABLE_TRANSACTIONS;
////    sqlDelete += " where " + ID + " = " + id;
////
////    db.execSQL( sqlDelete );
////    db.close( );
////  }
//
////  public void updateById( int id, String name, double price ) {
////    SQLiteDatabase db = this.getWritableDatabase();
////
////    String sqlUpdate = "update " + TABLE_TRANSACTIONS;
////    sqlUpdate += " set " + NAME + " = '" + name + "', ";
////    sqlUpdate += PRICE + " = '" + price + "'";
////    sqlUpdate += " where " + ID + " = " + id;
////
////    db.execSQL( sqlUpdate );
////    db.close( );
////  }
//
////  public ArrayList<Candy> selectAll( ) {
////    String sqlQuery = "select * from " + TABLE_TRANSACTIONS;
////
////    SQLiteDatabase db = this.getWritableDatabase( );
////    Cursor cursor = db.rawQuery( sqlQuery, null );
////
////    ArrayList<Candy> candies = new ArrayList<Candy>( );
////    while( cursor.moveToNext( ) ) {
////      Candy currentCandy
////          = new Candy( Integer.parseInt( cursor.getString( 0 ) ),
////        		        cursor.getString( 1 ), cursor.getDouble( 2 ) );
////      candies.add( currentCandy );
////    }
////    db.close( );
////    return candies;
////  }
//
//
//}
