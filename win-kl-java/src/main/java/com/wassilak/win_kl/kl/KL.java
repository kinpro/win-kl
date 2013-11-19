package com.wassilak.win_kl.kl;

import java.io.File;

/**
 * The KL interface defines the behavior of a key-logger.
 */
public interface KL {

    /**
     * The run method triggers the key-logger to begin execution.
     *
     * @param logFile The file that the key-logger should log keys to.
     */
    public void run(File logFile);
}
