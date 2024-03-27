// TestInterface

import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.List;
import java.util.ArrayList;

public class cTestDatabaseInterface
{
    public static void main(String[] args) 
    {
        Scanner scanner = new Scanner(System.in);
        iCRUDOperations odatabase = null;
        String dbTypeFile = "db_type.cfg";
        String tableNameFile = "table_name.cfg";
        String dbNameFile = "db_name.cfg";
        String fieldsFile = "fieldNames.cfg";

        try 
        {
            String dbType = readConfigurationFile(dbTypeFile).trim();
            String tableName = readConfigurationFile(tableNameFile).trim();
            String dbName = readConfigurationFile(dbNameFile).trim();

            String className = dbType;
            String[] fieldNames = getFieldNames(fieldsFile);
            cUserInterface oUI = new cUserInterface(tableName, fieldNames);

            odatabase = (iCRUDOperations) Class.forName(className).getDeclaredConstructor(String.class, String.class, String[].class).newInstance(dbName, tableName, fieldNames);

            while (true) 
            {
                System.out.println("\n---- " + tableName + " Management ----");
                System.out.println("0. Exit");
                System.out.println("1. Insert " + tableName);
                System.out.println("2. Show all " + tableName);

                System.out.print("\nEnter your choice: ");
                int userChoice = scanner.nextInt();
                scanner.nextLine();

                if (userChoice == 0) 
                {
                    System.out.println("You chose to exit. Thank you.");
                    break;
                } 
                else if (userChoice == 1 || userChoice == 2) 
                {
                    switch (userChoice) 
                    {
                        case 1:
                            String[] itemDetails = oUI.getItemDetails();
                            int rowInserted = odatabase.insertRecord(itemDetails);
                            oUI.printOutcomeMessage(rowInserted, "insertion");
                            break;
                        case 2:
                            oUI.printRecords(odatabase.getAllRecords());
                            break;
                    }
                } 
                else 
                {
                    System.out.println("Invalid choice");
                }
            }
        } 
        catch (Exception e) 
        {
            e.printStackTrace();
            System.err.println("Error: " + e.getMessage());
        } 
        finally 
        {
            scanner.close();
        }
    }

    private static String[] getFieldNames(String fileName) 
    {
        List<String> fields = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(new FileReader(fileName))) 
        {
            String field;
            while ((field = br.readLine()) != null) 
            {
                fields.add(field.trim());
            }
        } 
        catch (IOException e) 
        {
            System.err.println("Error reading column names from file: " + e.getMessage());
        }
        return fields.toArray(new String[0]);
    }


    private static String readConfigurationFile(String fileName) throws FileNotFoundException 
    {
        File file = new File(fileName);
        Scanner scanner = new Scanner(file);
        String data = scanner.nextLine().trim();
        scanner.close();
        return data;
    }
}
