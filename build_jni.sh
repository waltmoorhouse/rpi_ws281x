#!/usr/bin/env bash

if [ -z "${JAVA_HOME}" ]; then
  echo "Please set JAVA_HOME env variable and try again."
elif [ -z "${ANNOTATION_JAR_PATH}" ]; then
  echo "Please set ANNOTATION_JAR_PATH env variable and try again."
else
  mkdir -p build/generated
  echo "Java is creating the Header file..."
  javac -cp "${ANNOTATION_JAR_PATH}" -h build/generated/ java/com/waltmoorhouse/jni/rpi/ws2811/*.java

  echo "g++ is compiling the C code..."
  g++ -c -fPIC "-I${JAVA_HOME}/include" "-I${JAVA_HOME}/include/linux" com_waltmoorhouse_jni_rpi_ws2811_RaspberryPiWs2811LedStripJNI.cpp -o build/generated/com_waltmoorhouse_jni_rpi_ws2811_RaspberryPiWs2811LedStripJNI.o

  echo "g++ is creating the shared library..."
  g++ -shared -fPIC -o build/generated/libRaspberryPiWs2811LedStripJNI.so build/generated/com_waltmoorhouse_jni_rpi_ws2811_RaspberryPiWs2811LedStripJNI.o ws2811.o rpihw.o dma.o mailbox.o pwm.o pcm.o -lc

  echo "Done!"
fi
