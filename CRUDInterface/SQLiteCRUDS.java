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
    private PreparedStatement Statement;
    private Scanner scanner = new Scanner(System.in);
    private String dbName;
    private String tableName;
    private String[] fieldNames;

    public cSQLiteCRUDS(String pdbName, String ptableName, String[] pfieldNames) 
    {
        try 
        {
            Class.forName("org.sqlite.JDBC");
            this.dbName = pdbName;
            this.tableName = ptableName;
            this.fieldNames = pfieldNames;
            String dbPath = "jdbc:sqlite:D:/training/sql/" + dbName;
            conn = DriverManager.getConnection(dbPath);
        } 
        catch (ClassNotFoundException | SQLException e) 
        {
            System.err.println("Error connecting to SQLite database: " + e.getMessage());
        }
    }

    public int insertRecord(String[] recordDetails) 
    {
        int rowInserted = 0;
        try 
        {
            StringBuilder queryBuilder = new StringBuilder("INSERT INTO ");
            queryBuilder.append(tableName).append(" (");
            for (int counter = 0; counter < fieldNames.length; counter++) 
            {
                queryBuilder.append(fieldNames[counter]);
                if (counter < fieldNames.length - 1) 
                {
                    queryBuilder.append(", ");
                }
            }
            queryBuilder.append(") VALUES (");
            for (int counter = 0; counter < recordDetails.length; counter++) 
            {
                queryBuilder.append("?");
                if (counter < recordDetails.length - 1) 
                {
                    queryBuilder.append(", ");
                }
            }
            queryBuilder.append(")");

            Statement = conn.prepareStatement(queryBuilder.toString());

            for (int counter = 0; counter < recordDetails.length; counter++) 
            {
                Statement.setString(counter + 1, recordDetails[counter]);
            }

            rowInserted = Statement.executeUpdate();
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
            Statement = conn.prepareStatement(query);
            ResultSet rs = Statement.executeQuery();

            while (rs.next()) 
            {
                String[] record = new String[5];
                record[0] = rs.getString(fieldNames[0]);
                record[1] = rs.getString(fieldNames[1]);
                record[2] = String.valueOf(rs.getInt(fieldNames[2]));
                record[3] = String.valueOf(rs.getInt(fieldNames[3]));
                record[4] = rs.getString(fieldNames[4]);
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
