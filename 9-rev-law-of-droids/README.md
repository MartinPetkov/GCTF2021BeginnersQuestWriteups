# Challenge #9 - Law of Droids

Category: `rev`

## Story

>Johannesburg is hot, and you are on your way to the secret lair. It seems like it is well fortified, even though you are expected under the alias of the assassin, perhaps it will be a better idea to sneak inside the lair, unseen? You climb up on a brick wall, and jump over it. On the other side you spot a lot of guards, quick, hide in a bush. Now you have to sneak past the guards into the main building's entrance.<br/><br/>
>In this challenge, you have to find the flag using memory forensics. Good luck! Note, surround the flag with CTF{...} to submit it. Note, API Level 25 is what you're looking for.

## Solution

This challenge comes with a download link. Let's fetch it and examine it:

```sh
$ wget -O law-of-droids.zip https://storage.googleapis.com/gctf-2021-attachments-project/06f923cd67e28af3d409ff78fd8385ae6457f4ea153a827e9a39c57293b7832e5064e75b4c48c1ac95bd62504a495258a04baec89e813eba7758fb88db329ca8
$ unzip law-of-droids.zip
Archive:  law-of-droids.zip
 extracting: bzImage
 extracting: bzImage.elf
 extracting: bzImage.elf.i64
 extracting: gCTF.apk
```

*Note: Unfortunately, I can't include the `law-of-droids.zip` file here as it exceeds GitHub's file size limit of 100.00 MB*

What is a `bzImage` you might ask? I hadn't heard of this before, but Googling immediately leads us to [vmlinux](https://en.wikipedia.org/wiki/Vmlinux) where it says that `bzImage` is just a compressed Linux image.

The .apk file is an [Android Package](https://en.wikipedia.org/wiki/Android_application_package), which can also be Googled quite easily but should be immediately familiar to anyone who's done Android development before.

### Exploring the code

Unfortunately, I'm not an Android developer and don't have an Android environment set up. I'm told this image and associated .apk can be run via the [`emulator`](https://developer.android.com/studio/run/emulator-commandline) command line, but let's just look at the code first and see what it does.

An .apk can be extracted using [`apktool`](https://ibotpeaches.github.io/Apktool/). Let's do that:

```sh
$ apktool d gCTF.apk
I: Using Apktool 2.5.0-dirty on gCTF.apk
I: Copying assets and libs...
I: Copying unknown files...
I: Copying original files...
$ ls ./gCTF
apktool.yml  original  unknown
```

`apktool.yml` is extraction metadata, and `original/` is empty. Let's explore `unknown/`. Presumably it's an Android Java source code tree.

```sh
$ cd ./gCTF/unknown/gCTF3/
gCTF/unknown/gCTF3 $ ls
app  build.gradle  gradle  gradle.properties  gradlew  gradlew.bat  local.properties  settings.gradle
```

You can explore various things here. The files related to [gradle](https://gradle.org/) and the properties files can give you the flags used to build this, and presumably how to run it in the emulator.

Let's continue on and try to find a Main class.

```sh
gCTF/unknown/gCTF3 $ cd app/src/main/
gCTF/unknown/gCTF3/app/src/main $ ls
AndroidManifest.xml  cpp  java  res
```

There's an [Android Manifest](https://developer.android.com/guide/topics/manifest/manifest-intro)

```xml
<?xml version="1.0" encoding="utf-8"?>
<manifest xmlns:android="http://schemas.android.com/apk/res/android"
    package="gctf.researchctf">
    <uses-permission android:name="android.permission.READ_EXTERNAL_STORAGE"></uses-permission>
    <uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE"></uses-permission>
    <application
        android:allowBackup="true"
        android:icon="@mipmap/ic_launcher"
        android:label="@string/app_name"
        android:roundIcon="@mipmap/ic_launcher_round"
        android:supportsRtl="true"
        android:theme="@style/Theme.GCTF">
        <activity android:name=".MainActivity">
            <intent-filter>
                <action android:name="android.intent.action.MAIN" />

                <category android:name="android.intent.category.LAUNCHER" />
            </intent-filter>
        </activity>
    </application>
</manifest>
```

Most of this is uninteresting but it does tell us that there's one [activity](https://developer.android.com/reference/android/app/Activity) called `MainActivity` and that it both reads and writes to storage (see the `uses-permission` lines). Hopefully this doesn't seem like too much of a stretch, but I suspect the flag isn't embedded in the apk but is instead written to or read from the Linux image from earlier.

Let's look at [the MainActivity.java file](apk-extract/gCTF/unknown/gCTF3/app/src/main/java/gctf/researchctf/MainActivity.java).

```sh
gCTF/unknown/gCTF3/app/src/main $ cd java/gctf/researchctf/
gCTF/unknown/gCTF3/app/src/main/java/gctf/researchctf $ ls
MainActivity.java
```

```java
private EditText tv = null;
// Used to load the 'native-lib' library on application startup.
static {
    System.loadLibrary("native-lib");
}
...
/**
* A native method that is implemented by the 'native-lib' native library,
* which is packaged with this application.
*/
public native String stringFromJNI();
public native String getCTF(String enteredKey);
public native int validateCTF(String enteredKey);
```

These register the use of [native libraries](https://developer.android.com/studio/projects/add-native-code), via C++ code. This is probably inside the `cpp/` folder from earlier. Two of these functions clearly operate on the flag too, so we should definitely check them out.

---

```java
@Override
protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);

    setContentView(R.layout.activity_main);
    try{
        File bf = new File(Environment.getExternalStoragePublicDirectory(DIRECTORY_DOWNLOADS), "Raven.txt");
        File f = new File(getApplicationContext().getFilesDir(), "SusanSue.txt");
        FileOutputStream fos = new FileOutputStream(f);
        fos.write("Sctf:key:".getBytes());
        fos.close();
        FileOutputStream bkfos = new FileOutputStream(bf);
        bkfos.write("BKUP:KEY:SecretKey:P@$$".getBytes());
        bkfos.close();

    }catch(Exception e){
        e.printStackTrace();
    }
    tv = findViewById(R.id.editTextTextPersonName);
    tv.setText(stringFromJNI());
}
```

I can't say I'm 100% sure what's going on here, but the [docs](https://developer.android.com/reference/android/app/Activity#onCreate(android.os.Bundle)) explain that this code runs when the activity is starting and contains initialization code. It appears to write two files, "Raven.txt" and "SusanSue.txt". Those files have slightly different key formatting; `Sctf:key:` for "SusanSue.txt" and `BKUP:KEY:SecretKey:P@$$` for "Raven.txt".

Now of course, `CTF{P@$$}` doesn't work. It wouldn't be that easy. So probably there's a SusanSue.txt file in the Linux image which contains the password.

---

```java
public void read(View view) {
    try{
        File f = new File(getApplicationContext().getFilesDir(), "SusanSue.txt");
        int s = validateCTF(tv.getText().toString());
        if(s == 0){
            Log.v("WATCHOUT", "You are the winner");
            Toast.makeText(getApplicationContext(), "YOU ARE THE WINNER!!!!", Toast.LENGTH_LONG).show();
        }else{
            Log.v("WATCHOUT", "Please keep trying");
            Toast.makeText(getApplicationContext(), "Please keep trying!!!!", Toast.LENGTH_LONG).show();
        }
    }catch (Exception e){
        e.printStackTrace();
    }

}
```

This just reads a text input and checks it against the expected string.

---

### Exploring the native library

Earlier we found reference to a native library.

```sh
gCTF/unknown/gCTF3/app/src/main/cpp $ ls
CMakeLists.txt  native-lib.cpp
```

The [CMake](https://cmake.org/) file is nothing special. It's just there to help build the .cpp file.

The [`native-lib.cpp` file](apk-extract/gCTF/unknown/gCTF3/app/src/main/cpp/native-lib.cpp) is more interesting. Let's explore it.

```cpp
extern "C" JNIEXPORT jstring JNICALL
Java_gctf_researchctf_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    FILE* tgt_filez_handle = NULL;

    //tgt_filez_handle = fopen(reinterpret_cast<const char *>(tgt_filez), "w");
    tgt_filez_handle = fopen("/data/data/gctf.researchctf/files/SusanSue.txt", "w");
    const char s[] = {'g', 'C', 'T', 'F', ':', 'K', 'E', 'Y', ':', '\0'};
    fputs(s, tgt_filez_handle);
    fclose(tgt_filez_handle);
    return env->NewStringUTF(hello.c_str());
}
```

This was only used once in the Activity. It suggests the app expects the user to input a key in the form `gCTF:KEY:<key>`.

---

```cpp
extern "C"
JNIEXPORT jstring JNICALL
Java_gctf_researchctf_MainActivity_getCTF(JNIEnv *env, jobject thiz, jstring entered_key) {
    FILE* tgt_file_handle = fopen("/data/data/gctf.researchctf/files/SusanSue.txt", "r");
    char *content = static_cast<char *>(calloc(256, sizeof(char)));

    //fgets(content, 256, tgt_file_handle);
    fscanf(tgt_file_handle, "%s", content);
    fclose(tgt_file_handle);

    return env->NewStringUTF(content);
}
```

This is a pretty big clue. It looks for a SusanSue.txt file and reads it out.

---

```cpp
extern "C"
JNIEXPORT jint JNICALL
Java_gctf_researchctf_MainActivity_validateCTF(JNIEnv *env, jobject thiz, jstring entered_key) {
    FILE* tgt_file_handle = fopen("/data/data/gctf.researchctf/files/SusanSue.txt", "r");
    char *content = static_cast<char *>(calloc(10, sizeof(char)));

    fgets(content, 10, tgt_file_handle);
    //fscanf(tgt_file_handle, "%s", content);
    fclose(tgt_file_handle);

    const char* ch = env->GetStringUTFChars(entered_key, 0);

    env->ReleaseStringUTFChars(entered_key, ch);
    //__android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "entered <%s>", reinterpret_cast<const char *>(ch));
    //printf("<%s>", ch);
    //__android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "CONTENT <%s>", reinterpret_cast<const char *>(content));
    //printf("<%s>", content);
    int comp = strcmp(content, reinterpret_cast<const char *>(ch));
    //printf("<%d>", comp);
    return comp;
}
```

This is a pretty big clue as well. It's comparing the user input against the contents of the SusanSue.txt file.

This gives us enough to continue. Let's go look for the flag in the Linux image.

---

### Searching for the flag in the Linux image

We're given the extracted image already, in the form of `bzImage.elf` and `bzImage.elf.i64`.

I don't really know how to "load" and examine this image file, though I feel like I should. However, I had a dumb idea that I wanted to try first before diving deeper. What if we just hexdump it and look for the "Susan" string?

```sh
$ hexdump -C bzImage.elf | grep 'Susan'
007e3d80  00 66 73 2f 6f 70 65 6e  2e 63 00 53 75 73 61 6e  |.fs/open.c.Susan|
```

We did find something! And only one something, at that. Let's expand the context a bit:

```sh
$ hexdump -C bzImage.elf | grep -C5 'Susan'
007e3d30  00 63 6d 61 00 6d 6d 5f  6d 69 67 72 61 74 65 5f  |.cma.mm_migrate_|
007e3d40  70 61 67 65 73 00 6d 69  67 72 61 74 65 00 6d 6d  |pages.migrate.mm|
007e3d50  2f 70 61 67 65 5f 69 73  6f 6c 61 74 69 6f 6e 2e  |/page_isolation.|
007e3d60  63 00 01 33 56 46 53 3a  20 43 6c 6f 73 65 3a 20  |c..3VFS: Close: |
007e3d70  66 69 6c 65 20 63 6f 75  6e 74 20 69 73 20 30 0a  |file count is 0.|
007e3d80  00 66 73 2f 6f 70 65 6e  2e 63 00 53 75 73 61 6e  |.fs/open.c.Susan|
007e3d90  53 75 65 00 2f 73 64 63  61 72 64 2f 44 6f 77 6e  |Sue./sdcard/Down|
007e3da0  6c 6f 61 64 2f 52 61 76  65 6e 2e 74 78 74 00 67  |load/Raven.txt.g|
007e3db0  43 54 46 3a 4b 45 59 3a  00 53 42 3a 35 37 35 37  |CTF:KEY:.SB:5757|
007e3dc0  35 36 00 01 36 56 46 53  3a 20 66 69 6c 65 2d 6d  |56..6VFS: file-m|
007e3dd0  61 78 20 6c 69 6d 69 74  20 25 6c 75 20 72 65 61  |ax limit %lu rea|
```

Okay, so this wasn't exactly the "SusanSue.txt" file we were looking for, but what's this? Could it be?

```
gCTF:KEY:.SB:575756..6VFS
```

We try it, and it works!

```
CTF{SB:575756}
```
