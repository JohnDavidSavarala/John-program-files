// MySQLCRUDS

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.DriverManager;
import java.util.List;
import java.util.ArrayList;
import java.sql.DatabaseMetaData;
import java.sql.ResultSetMetaData;
import java.util.Scanner;


public class cMySQLCRUDS implements iCRUDOperations 
{

    private Connection conn;
    private PreparedStatement itemStatement;
    private Scanner scanner = new Scanner(System.in);
    private String host;
    private String user;
    private String password;
    private String tableName;
    private String database;
    private String[] fieldNames;

    public cMySQLCRUDS(String pdbName, String ptableName, String[] pfieldNames) throws SQLException
    {
        this.host = "138.68.140.83";
        this.user = "John";
        this.password = "John@123";
        this.tableName = ptableName;
        this.database = pdbName;
        this.fieldNames = pfieldNames;

        try 
        {
            conn = DriverManager.getConnection("jdbc:mysql://" + host + "/" + database, user, password);
            System.out.println("Connected to the database.");
        } 
        catch (SQLException e) 
        {
            System.err.println("Error connecting to MySQL database: " + e.getMessage());
            throw e; 
        }
        
    }

    public int insertRecord(String[] itemDetails) 
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
