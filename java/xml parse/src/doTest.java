import org.w3c.dom.Element;

public class doTest {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		//DOMParser parse=new DOMParser("books.xml");
		//parse.PrintXML();
		//parse.WriteToXML("book2.xml");
		
		DOMParser parse = new DOMParser();
		Element root = parse.CreateElement("root");
		parse.CreateElement(root,"child1","1");
		parse.CreateElement(root,"child2","2");
		parse.WriteToXML("test.xml");
	}

}
