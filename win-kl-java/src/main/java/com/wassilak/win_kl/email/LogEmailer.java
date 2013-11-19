package com.wassilak.win_kl.email;

import java.io.File;

/**
 * The LogEmailer interface defines the behavior of a LogEmailer object.
 */
public interface LogEmailer {

    /**
     * The emailLog method triggers the LogEmailer to send the given log file
     * via email, then truncates the file.
     *
     * @param logFile The file to be emailed.
     */
    public void emailLog(File logFile);
}
