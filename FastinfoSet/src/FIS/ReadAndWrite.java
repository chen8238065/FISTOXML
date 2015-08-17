package FIS;

import java.io.*;

import javax.xml.bind.*;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.XMLStreamReader;
import javax.xml.stream.XMLStreamWriter;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.TransformerFactoryConfigurationError;
import javax.xml.transform.stream.StreamResult;

import org.junit.Test;
import org.jvnet.fastinfoset.FastInfosetSource;
import org.jvnet.fastinfoset.sax.FastInfosetReader;
import org.jvnet.fastinfoset.sax.helpers.FastInfosetDefaultHandler;
import org.xml.sax.*;
import org.xml.sax.helpers.DefaultHandler;

import FIS.Entity.SerializerEntity;
import FIS.Entity.SerializerEntity.Gender;

import com.sun.xml.internal.stream.buffer.sax.DefaultWithLexicalHandler;
import com.sun.xml.internal.ws.encoding.fastinfoset.FastInfosetStreamReaderFactory;
import com.sun.xml.fastinfoset.sax.SAXDocumentParser;
import com.sun.xml.fastinfoset.sax.SAXDocumentSerializer;
import com.sun.xml.fastinfoset.stax.StAXDocumentParser;
import com.sun.xml.fastinfoset.stax.StAXDocumentSerializer;

public class ReadAndWrite {
	String fi_document="E:\\Study\\Ctrip\\FISerialization\\FISerialization\\bin\\Debug\\Noemax.FastInfoset.Net41.fi";
	String xml_document="E:\\Study\\Ctrip\\FISerialization\\FISerialization\\bin\\Debug\\Noemax.FastInfoset.Net41.xml";
	@Test
	public  void readFastinfoSetDocument() throws IOException, SAXException, ParserConfigurationException
	{
		
		// Create a SAX parser
        

		ContentHandler  builder = new FastinfosetEventHandler(); 
		 // Instantiate the FI SAX parser 
		 XMLReader saxReader = new SAXDocumentParser(); 
		 saxReader.setContentHandler(builder); 
		 // Parse the fast infoset document 
		 InputStream in = new BufferedInputStream(new FileInputStream(fi_document));
		 InputSource inputSource = new InputSource(in); 
		 saxReader.parse(inputSource);
	}
	@Test
	public void TranslateXMLToFIS() throws ParserConfigurationException, SAXException, IOException
	{
		// Get the input stream for the XML document
		InputStream xmlDocument =new BufferedInputStream(new FileInputStream(xml_document));
		// Set up output stream for fast infoset document
		OutputStream fiDocument =new BufferedOutputStream(new FileOutputStream(fi_document));

		// Create Fast Infoset SAX serializer
		SAXDocumentSerializer saxDocumentSerializer = new SAXDocumentSerializer();
		// Set the output stream
		saxDocumentSerializer.setOutputStream(fiDocument);

		// Instantiate JAXP SAX parser factory
		SAXParserFactory saxParserFactory = SAXParserFactory.newInstance();
		/* Set parser to be namespace aware
		 * Very important to do otherwise invalid FI documents will be
		 * created by the SAXDocumentSerializer
		 */
		saxParserFactory.setNamespaceAware(true);
		// Instantiate the JAXP SAX parser
		SAXParser saxParser = saxParserFactory.newSAXParser();
		// Set the lexical handler
		saxParser.setProperty("http://xml.org/sax/properties/lexical-handler",  new FastInfosetDefaultHandler());
		// Parse the XML document and convert to a fast infoset document
		saxParser.parse(xmlDocument, saxDocumentSerializer);
	}
	@Test
	public void TranslateFISToXML() throws TransformerFactoryConfigurationError, TransformerException, FileNotFoundException
	{
		// Get the input stream for the fast infoset document
		InputStream fiDocument = new BufferedInputStream(new FileInputStream(fi_document));
		// Set up output stream for XML document
		OutputStream xmlDocument = new BufferedOutputStream(new FileOutputStream(xml_document));

		// Create the transformer
		Transformer tx = TransformerFactory.newInstance().newTransformer();
		// Transform to convert the FI document to an XML document
		tx.transform(new FastInfosetSource(fiDocument), new StreamResult(xmlDocument));
	}
	
	public String TranslateFISToXMLFromString() throws TransformerFactoryConfigurationError, TransformerException, IOException
	{
		
		InputStream bis = new BufferedInputStream(new FileInputStream(fi_document),2048);
		//#region demo 功能
//   BufferedInputStream  TO String
//		StringBuilder sb=new StringBuilder();
//		byte[] byteArray=new byte[1024];
//		int tmp=0;
//		while((tmp=bis.read(byteArray))!=-1){ 
//            sb.append(new String(byteArray,0,tmp));
//		}
//		bis.close();
//		String str=sb.toString();
//		System.out.println(str);
//		// Get the input stream for the fast infoset documen
//		InputStream fiDocument = new ByteArrayInputStream(str.getBytes());

//		BufferedInputStream  To byte[]
//		// read number of bytes available
//        int numByte = bis.available();
//        byte[] buf = new byte[numByte];
//        bis.read(buf,0,numByte);
//        InputStream fiDocument = new ByteArrayInputStream(buf);
		//#endregion
		String s="?   <person<age?3?gender?male?name? hhh?";
		//InputStream fiDocument = new ByteArrayInputStream(s.getBytes());
        // Set up output stream for XML document
		OutputStream xmlDocument = new ByteArrayOutputStream();

		// Create the transformer
		Transformer tx = TransformerFactory.newInstance().newTransformer();
		// Transform to convert the FI document to an XML document
		tx.transform(new FastInfosetSource(bis), new StreamResult(xmlDocument));
		byte[] b=((ByteArrayOutputStream) xmlDocument).toByteArray();
		String rtStr= new String(b, "GB2312");
		//System.out.println(rtStr);
		return rtStr;
		
	}
	@Test
	public void readFISbySTAX() throws FileNotFoundException, XMLStreamException
	{
		InputStream fiDocument = new BufferedInputStream(new FileInputStream(fi_document));

		// Create the StAX XMLStreamReader using the input stream
		XMLStreamReader reader = new StAXDocumentParser(fiDocument);
		while(reader.hasNext())
		{  
            int point = reader.next();  
            switch(point)
            {  
            	case XMLStreamReader.START_DOCUMENT:
            	{
            		System.out.println("\nStax start.");
            		break;
            	}
	            case XMLStreamReader.START_ELEMENT :{   //开始节点  
	            	System.out.print("<"+reader.getName()+" ");
	        		for(int i=0;i<reader.getAttributeCount();i++)
	        		{
	        			System.out.print(reader.getAttributeLocalName(i));
	        			System.out.print("=\""+reader.getAttributeValue(i)+"\" ");
	        		}
	        		System.out.print(">");
	                    break;
	                }  
	            case XMLStreamReader.END_ELEMENT :{   //结束节点  
	            	System.out.print("</"+reader.getName()+">");
	            	break;
	            }  
	            case XMLStreamReader.CHARACTERS :{  //文本节点  
	            	
	        		System.out.print(reader.getText());
	        		break;	
	            }  
	            case XMLStreamReader.END_DOCUMENT:
	            {
	            	System.out.println("\nStax end.");
	            	break;
	            }  
            }
		}
         
	}
	
	
	@Test
	public void  FisSerialize() throws XMLStreamException, FileNotFoundException
	{
		// Set up output stream for fast infoset document
		OutputStream fiDocument =new BufferedOutputStream(new FileOutputStream(fi_document));
		// Create the StAX document serializer
		StAXDocumentSerializer staxDocumentSerializer = new StAXDocumentSerializer();
		staxDocumentSerializer.setOutputStream(fiDocument);

		// Obtain XMLStreamWriter interface
		XMLStreamWriter streamWriter = staxDocumentSerializer;

		// Write out some simple infoset
		streamWriter.writeStartDocument();
		   streamWriter.writeStartElement("foo");
		      streamWriter.writeCharacters("bar");
		   streamWriter.writeEndElement();
		streamWriter.writeEndDocument();
		streamWriter.close();
	}

	@Test
	public void FisSerializeByJAXB() throws JAXBException, FileNotFoundException
	{
		// Set up output stream for fast infoset document
		OutputStream fiDocument = new BufferedOutputStream(new FileOutputStream(fi_document));

		// Create the StAX document serializer
		StAXDocumentSerializer staxDocumentSerializer = new StAXDocumentSerializer();
		staxDocumentSerializer.setOutputStream(fiDocument);

		// Obtain XMLStreamWriter interface
		XMLStreamWriter streamWriter = staxDocumentSerializer;

		// Create JAXB context
		JAXBContext context = JAXBContext.newInstance(SerializerEntity.class);

		SerializerEntity jaxbObject=new SerializerEntity();
		jaxbObject.setAge(23);
		jaxbObject.setGender(Gender.male);
		jaxbObject.setName("hhh");
		// Create the marshaller
		Marshaller m = context.createMarshaller();
		// Marshall the object to the stream
		m.marshal(jaxbObject, streamWriter);
	}

	@Test
	public void FISDeserializerToJAXB() throws JAXBException, FileNotFoundException
	{
		InputStream fiDocument = new BufferedInputStream(new FileInputStream(fi_document));

		// Create the StAX XMLStreamReader using the input stream
		XMLStreamReader streamReader = new StAXDocumentParser(fiDocument);

		// Create JAXB context
		JAXBContext context = JAXBContext.newInstance(SerializerEntity.class);

		// Create unmarshaller
		Unmarshaller u = context.createUnmarshaller();
		// Unmarshall from the stream to an object
		Object jaxbObject = u.unmarshal(streamReader);
		SerializerEntity jaxject=(SerializerEntity) jaxbObject;
		System.out.println(jaxject.getName());
		System.out.println(jaxject.getAge());
	}
}

class FastinfosetEventHandler extends DefaultHandler
{
	/**
	 * 标记开始
	 * @param uri 名称空间
	 * @param qName 标记名称
	 * @param atts 属性集
	 */
	public void startElement(String uri, String localName, String qName, Attributes atts){
		System.out.print("<"+qName+" ");
		atts.getLength();
		for(int i=0;i<atts.getLength();i++)
		{
			System.out.print(atts.getLocalName(i));
			System.out.print("=\""+atts.getValue(i)+"\" ");
		}
		System.out.print(">");
	}
	
	/**
	 * 文字事件
	 */
	public void characters(char[] ch, int start ,int length){
		String temp=new String(ch,start,length);
		System.out.print(temp);
	}
	
	
	/**
	 * 标记结束
	 */
	public void endElement(String uri, String localName, String qName){
		System.out.print("</"+qName+">");
		
	}
	/**
	 * 文档开始
	 */
	public void startDocument()
	{
		System.out.println("Sax Start.");
	}
	/**
	 * 文档结束
	 */
	public void endDocument()
	{
		System.out.println("\nSax end.");
	}
}
	