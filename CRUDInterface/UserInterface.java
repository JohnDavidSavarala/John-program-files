// User Interface

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class cUserInterface 
{
    private Scanner scanner;
    private String[] columnNames;
    private String tableName;

    public cUserInterface(String ptableName, String columnConfigFile) 
    {
        scanner = new Scanner(System.in);
        this.tableName = ptableName;
        this.columnNames = readColumnNames(columnConfigFile);
    }

    public String[] readColumnNames(String fileName) 
    {
        List<String> columns = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(new FileReader(fileName))) 
        {
            String column;
            while ((column = br.readLine()) != null) 
            {
                columns.add(column.trim());
            }
        } 
        catch (IOException e) 
        {
            System.err.println("Error reading column names from file: " + e.getMessage());
        }
        return columns.toArray(new String[0]);
    }

    public String[] getItemDetails() 
    {
	    String[] details = new String[columnNames.length];
	    for (int counter = 0; counter < columnNames.length; counter++) 
	    {
	        System.out.print("Enter " + columnNames[counter] + ": ");
	        details[counter] = scanner.nextLine();
	    }
	    return details;
	}

    public void printOutcomeMessage(int pRowInserted, String pOperation) 
    {
        System.out.print(tableName + " details " + pOperation + " is ");

        if (pRowInserted == 1) 
        {
            System.out.print("successful.\n");
        } 
        else 
        {
            System.out.print("failed.\n");
        }
    }

    public void printRecords(List<String[]> records, String[] columnNames) 
    {
        System.out.println("Records:");

        for (String columnName : columnNames) 
        {
            System.out.printf("%-20s", columnName);
        }
        System.out.println();

        for (String[] record : records) 
        {
            for (String field : record) 
            {
                System.out.printf("%-20s", field);
            }
            System.out.println();
        }
    }
}

