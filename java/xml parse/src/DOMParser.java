 import java.io.File; 
 import java.io.IOException; 
 import javax.xml.parsers.DocumentBuilder; 
 import javax.xml.parsers.DocumentBuilderFactory; 
 import javax.xml.parsers.ParserConfigurationException; 
 import org.w3c.dom.Document; 
 import org.w3c.dom.Element; 
 import org.w3c.dom.Node; 
 import org.w3c.dom.NodeList; 
 import org.xml.sax.SAXException;

import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
 import javax.xml.transform.TransformerFactory;
 import javax.xml.transform.TransformerException;
 import javax.xml.transform.TransformerConfigurationException;
 import javax.xml.transform.dom.DOMSource; 
 import javax.xml.transform.stream.StreamResult;

 //http://docs.oracle.com/javase/tutorial/jaxp/xslt/writingDom.html
 //ÏêÏ¸Ê¾Àý
 //http://www.cnblogs.com/ITEagle/archive/2010/03/03/1677431.html
 public class DOMParser { 
   public DocumentBuilderFactory builderFactory; 
   public DocumentBuilder db;
   public Document doc;

   //create empty DOM
   public DOMParser()
   {
	   try{
		   builderFactory = DocumentBuilderFactory.newInstance(); 
		   db=builderFactory.newDocumentBuilder();
		   doc=db.newDocument();
	   }
	   catch(Exception e)
	   {
		   e.printStackTrace();
	   }
   }
  
   //create DOM from file
   public DOMParser(String filePath)
   {
	   try{
	   builderFactory = DocumentBuilderFactory.newInstance(); 
	   db=builderFactory.newDocumentBuilder();
	   doc=db.parse(new File(filePath));
	   }
	   catch(Exception e)
	   {
		   e.printStackTrace();
	   }
   }
   
   //write DOM to xml file
   public void WriteToXML(String filePath)
   {
	   try {
		    // Use a Transformer for output
		    TransformerFactory tFactory = TransformerFactory.newInstance();
		    Transformer transformer = tFactory.newTransformer();
		    //for pretty print
		    //http://www.journaldev.com/1112/how-to-write-xml-file-in-java-dom-parser
		    transformer.setOutputProperty(OutputKeys.INDENT, "yes");
		    transformer.setOutputProperty("encoding", "UTF-8");
		    DOMSource source = new DOMSource(doc);
		    StreamResult result = new StreamResult(new File(filePath));
		    transformer.transform(source, result);
		}
	   catch(Exception e)
	   {
		   e.printStackTrace();
	   }
   }
   
   public void PrintXML()
   {
	   try {
		    // Use a Transformer for output
		    TransformerFactory tFactory = TransformerFactory.newInstance();
		    Transformer transformer = tFactory.newTransformer();

		    DOMSource source = new DOMSource(doc);
		    StreamResult result = new StreamResult(System.out);
		    transformer.transform(source, result);
		}
	   catch(Exception e)
	   {
		   e.printStackTrace();
	   }
   }
   
   //create root element
   public Element CreateElement(String tagName)
   {
	   Element root = doc.createElement(tagName);
	   //root.setAttribute("attr1", "1");
	   doc.appendChild(root);
	   
	   return root;
   }
   
   //create element under parent
   public Element CreateElement(Element parent,String tagName,String value)
   {
       Document doc=parent.getOwnerDocument();
       Element child=doc.createElement(tagName);
       child.appendChild(doc.createTextNode(value));
       parent.appendChild(child);
       return child;
   }
   
   public Document parse(String filePath) { 
      Document document = null; 
      try { 
         //DOM parser instance 
         DocumentBuilder builder = builderFactory.newDocumentBuilder(); 
         //parse an XML file into a DOM tree 
         document = builder.parse(new File(filePath)); 
      } catch (ParserConfigurationException e) { 
         e.printStackTrace();  
      } catch (SAXException e) { 
         e.printStackTrace(); 
      } catch (IOException e) { 
         e.printStackTrace(); 
      } 
      return document; 
   } 
	
   public void ttt()
   {
          //get root element 
         Element rootElement = doc.getDocumentElement(); 

         //traverse child elements 
         NodeList nodes = rootElement.getChildNodes(); 
         for (int i=0; i < nodes.getLength(); i++) 
         { 
            Node node = nodes.item(i); 
            if (node.getNodeType() == Node.ELEMENT_NODE) {   
               Element child = (Element) node; 
               //process child element 
            } 
         } 

         NodeList nodeList = rootElement.getElementsByTagName("book"); 
         if(nodeList != null) 
         { 
            for (int i = 0 ; i < nodeList.getLength(); i++) 
            { 
               Element element = (Element)nodeList.item(i); 
               String id = element.getAttribute("id"); 
            } 
         } 
   }
 }