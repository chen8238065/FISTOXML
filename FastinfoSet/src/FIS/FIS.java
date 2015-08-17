package FIS;

import java.io.BufferedInputStream;
import java.io.ByteArrayOutputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.TransformerFactoryConfigurationError;
import javax.xml.transform.stream.StreamResult;

import org.jvnet.fastinfoset.FastInfosetSource;

public class FIS {
	public static void main(String[] args) throws TransformerFactoryConfigurationError, TransformerException, IOException
	{
		
		InputStream bis = new BufferedInputStream(new FileInputStream(args[0]),2048);
		OutputStream xmlDocument = new ByteArrayOutputStream();

		// Create the transformer
		Transformer tx = TransformerFactory.newInstance().newTransformer();
		// Transform to convert the FI document to an XML document
		tx.transform(new FastInfosetSource(bis), new StreamResult(xmlDocument));
		byte[] b=((ByteArrayOutputStream) xmlDocument).toByteArray();
		String rtStr= new String(b, "GB2312");
		System.out.println(rtStr);
		
	}
}
