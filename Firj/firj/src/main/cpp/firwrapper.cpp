#include <jni.h>
#include <string>

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdexcept>

#include "../../../../../Fir1.h"

extern "C" {

jlong
Java_uk_me_berndporr_firj_Fir1_getInstance(JNIEnv *env,
                                           jclass clazz,
                                           jdoubleArray coeffArray) {

    double *coeffValues = env->GetDoubleArrayElements(coeffArray, 0);
    unsigned nTaps = (unsigned) env->GetArrayLength(coeffArray);

    Fir1 *fir = new Fir1(coeffValues, nTaps);

    env->ReleaseDoubleArrayElements(coeffArray, coeffValues, 0);

    return (jlong) fir;
}


jlong
Java_uk_me_berndporr_firj_Fir1_getInstanceLMS(JNIEnv *env,
                                              jclass clazz,
                                              jdouble nTaps) {

    Fir1 *fir = new Fir1(nTaps);
    return (jlong) fir;
}


jdouble
Java_uk_me_berndporr_firj_Fir1_filter(JNIEnv *env,
                                      jclass clazz,
                                      jlong instance,
                                      jdouble value) {
    Fir1 *fir = (Fir1 *) instance;
    if (fir == NULL) return 0;
    return fir->filter(value);
}


void
Java_uk_me_berndporr_firj_Fir1_lmsUpdate(JNIEnv *env,
                                         jclass clazz,
                                         jlong instance,
                                         jdouble error) {
    Fir1 *fir = (Fir1 *) instance;
    return fir->lms_update(error);
}


void
Java_uk_me_berndporr_firj_Fir1_setLearningRate(JNIEnv *env,
                                               jclass clazz,
                                               jlong instance,
                                               jdouble mu) {
    Fir1 *fir = (Fir1 *) instance;
    return fir->setLearningRate(mu);
}


jdouble
Java_uk_me_berndporr_firj_Fir1_getTapInputPower(JNIEnv *env,
                                                jclass clazz,
                                                jlong instance) {
    Fir1 *fir = (Fir1 *) instance;
    return fir->getTapInputPower();
}


void Java_uk_me_berndporr_firj_Fir1_releaseInstance(JNIEnv *env,
                                                    jclass clazz,
                                                    jlong instance) {
    Fir1 *fir = (Fir1 *) instance;
    if (fir == NULL) return;
    delete fir;
}


}