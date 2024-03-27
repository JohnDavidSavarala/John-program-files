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
    private String[] fieldNames;
    private String tableName;

    public cUserInterface(String ptableName, String[] pfieldNames) 
    {
        scanner = new Scanner(System.in);
        this.tableName = ptableName;
        this.fieldNames = pfieldNames;
    }

    public String[] getItemDetails() 
    {
	    String[] details = new String[fieldNames.length];
	    for (int counter = 0; counter < fieldNames.length; counter++) 
	    {
	        System.out.print("Enter " + fieldNames[counter] + ": ");
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


    public void printRecords(List<String[]> records) 
    {
        System.out.println("Records:");

        for (String columnName : fieldNames) 
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

