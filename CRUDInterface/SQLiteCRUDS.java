// SQLiteCRUDS 

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;

public class cSQLiteCRUDS implements iCRUDOperations
{

    private Connection conn;
    private PreparedStatement itemStatement;
    private Scanner scanner = new Scanner(System.in);
    private String dbName;
    private String tableName;
    private String[] columnNames;

    public cSQLiteCRUDS(String pdbName, String ptableName, String[] pcolumnNames) 
    {
        try 
        {
            Class.forName("org.sqlite.JDBC");
            this.dbName = pdbName;
            this.tableName = ptableName;
            this.columnNames = pcolumnNames;
            String dbPath = "jdbc:sqlite:D:/training/sql/" + dbName;
            conn = DriverManager.getConnection(dbPath);
        } 
        catch (ClassNotFoundException | SQLException e) 
        {
            System.err.println("Error connecting to SQLite database: " + e.getMessage());
        }
    }

    public int insertRecord(String[] itemDetails) 
    {
        int rowInserted = 0;
        try 
        {
            StringBuilder queryBuilder = new StringBuilder("INSERT INTO ");
            queryBuilder.append(tableName).append(" (");
            for (int counter = 0; counter < columnNames.length; counter++) 
            {
                queryBuilder.append(columnNames[counter]);
                if (counter < columnNames.length - 1) 
                {
                    queryBuilder.append(", ");
                }
            }
            queryBuilder.append(") VALUES (");
            for (int counter = 0; counter < itemDetails.length; counter++) 
            {
                queryBuilder.append("?");
                if (counter < itemDetails.length - 1) 
                {
                    queryBuilder.append(", ");
                }
            }
            queryBuilder.append(")");

            itemStatement = conn.prepareStatement(queryBuilder.toString());

            for (int counter = 0; counter < itemDetails.length; counter++) 
            {
                itemStatement.setString(counter + 1, itemDetails[counter]);
            }

            rowInserted = itemStatement.executeUpdate();
        } 
        catch (SQLException e) 
        {
            System.err.println("Error inserting record: " + e.getMessage());
        }
        return rowInserted;
    }

    public List<String[]> getAllRecords() 
    {
        List<String[]> records = new ArrayList<>();
        try 
        {
            String query = "SELECT * FROM " + tableName;
            itemStatement = conn.prepareStatement(query);
            ResultSet rs = itemStatement.executeQuery();

            while (rs.next()) 
            {
                String[] record = new String[5];
                record[0] = rs.getString(columnNames[0]);
                record[1] = rs.getString(columnNames[1]);
                record[2] = String.valueOf(rs.getInt(columnNames[2]));
                record[3] = String.valueOf(rs.getInt(columnNames[3]));
                record[4] = rs.getString(columnNames[4]);
                records.add(record);
            }
        } 
        catch (SQLException e) 
        {
            System.err.println("Error fetching records: " + e.getMessage());
        }
        return records;
    }

}
