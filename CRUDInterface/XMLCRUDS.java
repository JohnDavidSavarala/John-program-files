// XMLCRUDS

import java.io.*;
import java.util.ArrayList;
import java.util.List;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

public class cXMLCRUDS implements iCRUDOperations {

    private String xmlFilePath;
    private String rootElementName;
    private String[] fieldNames;

    public cXMLCRUDS(String xmlFilePath, String rootElementName, String[] pfieldNames) 
    {
        this.xmlFilePath = xmlFilePath;
        this.rootElementName = rootElementName;
        this.fieldNames = pfieldNames;
    }

    public int insertRecord(String[] itemDetails) 
    {
        try 
        {
            DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
            DocumentBuilder docBuilder = docFactory.newDocumentBuilder();
            Document doc;
            Element rootElement;

            File file = new File(xmlFilePath);

            if (file.exists()) 
            {
                FileInputStream fileInputStream = new FileInputStream(xmlFilePath);
                doc = docBuilder.parse(fileInputStream);
                fileInputStream.close();

                rootElement = doc.getDocumentElement();
            } 
            else 
            {
                doc = docBuilder.newDocument();
                rootElement = doc.createElement(rootElementName);
                doc.appendChild(rootElement);
            }

            Element itemElement = doc.createElement("Item");
            for (int counter = 0; counter < fieldNames.length; counter++) 
            {
                Element columnElement = doc.createElement(fieldNames[counter]);
                columnElement.appendChild(doc.createTextNode(itemDetails[counter]));
                itemElement.appendChild(columnElement);
            }

            rootElement.appendChild(itemElement);

            TransformerFactory transformerFactory = TransformerFactory.newInstance();
            Transformer transformer = transformerFactory.newTransformer();
            DOMSource source = new DOMSource(doc);
            StreamResult result = new StreamResult(new FileOutputStream(xmlFilePath));
            transformer.transform(source, result);

            return 1; 
        } 
        catch (ParserConfigurationException | SAXException | IOException | TransformerException e) 
        {
            e.printStackTrace();
            return 0; 
        }
    }

    public List<String[]> getAllRecords() 
    {
        List<String[]> records = new ArrayList<>();
        try 
        {
            File xmlFile = new File(xmlFilePath);
            DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
            DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
            Document doc = dBuilder.parse(xmlFile);
            doc.getDocumentElement().normalize();
            NodeList nodeList = doc.getElementsByTagName("Item");

            for (int counter = 0; counter < nodeList.getLength(); counter++) 
            {
                Node node = nodeList.item(counter);
                if (node.getNodeType() == Node.ELEMENT_NODE) 
                {
                    Element element = (Element) node;
                    String[] record = new String[5];
                    for (int fieldCounter = 0; fieldCounter < 5; fieldCounter++) 
                    {
                        record[fieldCounter] = element.getElementsByTagName(fieldNames[fieldCounter]).item(0).getTextContent();
                    }
                    records.add(record);
                }
            }
        } 
        catch (ParserConfigurationException | SAXException | IOException e) 
        {
            e.printStackTrace();
        }
        return records;
    }

}
