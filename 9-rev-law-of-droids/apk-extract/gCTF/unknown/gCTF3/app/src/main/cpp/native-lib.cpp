#include <jni.h>
#include <string>

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