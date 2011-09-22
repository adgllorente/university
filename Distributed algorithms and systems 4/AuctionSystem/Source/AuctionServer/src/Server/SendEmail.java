package Server;

import java.util.Properties;

import javax.mail.Address;
import javax.mail.Message;
import javax.mail.Session;
import javax.mail.Transport;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeMessage;

public class SendEmail {
	
	public SendEmail(String email, String subject, String content) {
		try
        {
            // Propiedades de la conexión
            Properties props = new Properties();
            props.setProperty("mail.smtp.host", "smtp.gmail.com");
            props.setProperty("mail.smtp.starttls.enable", "true");
            props.setProperty("mail.smtp.port", "587");
            props.setProperty("mail.smtp.user", "kuve18@gmail.com");
            props.setProperty("mail.smtp.auth", "true");

            // Preparamos la sesion
            Session session = Session.getDefaultInstance(props);

            // Construimos el mensaje
            MimeMessage message = new MimeMessage(session);
            message.setFrom(new InternetAddress("kuve18@gmail.com"));
            message.addRecipient(
                Message.RecipientType.TO,
                new InternetAddress(email));
            message.setSubject(subject);
            message.setText(
                "Bid Information: " + content);

            // Lo enviamos.
            Transport t = session.getTransport("smtp");
            t.connect("kuve18@gmail.com", "1q2w3e4r");
            t.sendMessage(message, message.getAllRecipients());

            // Cierre.
            t.close();
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
	}
	
	public SendEmail(String emails[], String subject, String content) {
		try
        {
            // Propiedades de la conexión
            Properties props = new Properties();
            props.setProperty("mail.smtp.host", "smtp.gmail.com");
            props.setProperty("mail.smtp.starttls.enable", "true");
            props.setProperty("mail.smtp.port", "587");
            props.setProperty("mail.smtp.user", "kuve18@gmail.com");
            props.setProperty("mail.smtp.auth", "true");

            // Preparamos la sesion
            Session session = Session.getDefaultInstance(props);

            // Construimos el mensaje
            MimeMessage message = new MimeMessage(session);
            message.setFrom(new InternetAddress("kuve18@gmail.com"));
            message.addRecipient(
                Message.RecipientType.TO,
                new InternetAddress("kuve18@gmail.com"));
            Address dirs[] = new Address[emails.length];
            for(int i=0;i<emails.length;i++){
            	dirs[i] = new InternetAddress(emails[i]);
            }
            message.addRecipients(Message.RecipientType.BCC, dirs);
            message.setSubject(subject);
            message.setText(
                "Bid Information: " + content);

            // Lo enviamos.
            Transport t = session.getTransport("smtp");
            t.connect("kuve18@gmail.com", "1q2w3e4r");
            t.sendMessage(message, message.getAllRecipients());

            // Cierre.
            t.close();
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
	}
}
