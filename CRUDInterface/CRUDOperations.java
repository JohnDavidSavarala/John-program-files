// iCRUDOperations

import java.sql.SQLException;
import java.sql.ResultSet;
import java.util.List;
import java.util.ArrayList;

public interface iCRUDOperations 
{
    int insertRecord(String[] ItemDetails);
    List<String[]> getAllRecords();
}
