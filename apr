#!/bin/bash
#set -x

tolower() 
{
	echo $1 | tr "[:upper:]" "[:lower:]" ;
} 

toupper() 
{
	echo $1 | tr "[:lower:]" "[:upper:]" ;
}

function invalid_command
{
	echo "Invalid command. Run help/-h command to see full usage"
}

function display_help
{
	echo "Android PRoject (APR) usage: "
	echo "	clean/-c 	= clean project"
	echo "	build 		= compile, link and upload. Use -v option for verbose mode"
	echo "	compile		= use ndk-build to build libso. Use -v option for verbose mode"
	echo "	link 		= link current libso to apk"
	echo "	push	 	= push apk to default device. Use -l option to link apk before push"
	echo "	help/-h		= display this help"
}

function pre_compile
{
	#mkdir tmp_jni
	cp -R -a jni ./tmp_jni
	rm -R jni/*

	/usr/bin/find ./tmp_jni -name "*.cpp" -exec cp -a {} ./jni \;
	/usr/bin/find ./tmp_jni -name "*.hpp" -exec cp -a {} ./jni \;
	/usr/bin/find ./tmp_jni -name "*.c" -exec cp -a {} ./jni \;
	/usr/bin/find ./tmp_jni -name "*.h" -exec cp -a {} ./jni \;
	/usr/bin/find ./tmp_jni -name "*.mk" -exec cp -a {} ./jni \;
}

function post_compile
{
	rm -R jni
	cp -R -a tmp_jni ./jni
	rm -R tmp_jni
}

function compile
{
	pre_compile
	$NDKROOT/ndk-build all
	STATUS=$?
	post_compile

	if [[ $STATUS -eq 0 ]] ; then
		echo "Compile ndk-build success!"
	else
		echo "PANIC!!! ndk-build failed!"
		exit 1
	fi
}

function compile_verbose
{
	pre_compile
	$NDKROOT/ndk-build all v=1
	STATUS=$?
	post_compile
	if [[ $STATUS -eq 0 ]] ; then
		echo 'Compile: "ndk-build" success!'
	else
		echo 'PANIC!!! "ndk-build" failed!'
		exit 1
	fi
}

function link
{
	ant debug
	if [[ $? -eq 0 ]] ; then
		echo 'Link: "ant debug" success!'
	else
		echo 'PANIC!!! "ant debug" failed!'
		exit 1
	fi
}

function push
{
	ant installd
	if [[ $? -eq 0 ]] ; then
		echo 'Push: "ant installd" success!'
	else
		echo 'PANIC!!! "ant debug" failed!'
		exit 1
	fi
}

function run
{
	PACKAGE=$(cat ./AndroidManifest.xml | grep "package=\"*\"" | cut -d"\"" -f2)
	ACTIVITY=$(cat ./AndroidManifest.xml | grep "<activity android:name=\"*\"" | cut -d"\"" -f2)
	adb shell am start -n $PACKAGE/$ACTIVITY
	if [[ $? -eq 0 ]] ; then
		echo 'Run: "adb shell am start -n <PACKAGE/ACTIVITY>" success!'
	else
		echo 'PANIC!!! "adb shell am start -n <PACKAGE/ACTIVITY>" failed!'
		exit 1
	fi
}

function clean
{
	rm -rf bin/ libs/ obj/
	$NDKROOT/ndk-build clean
	ant debug clean
}

if [[ $# -eq 1 ]] ; then
	PARAM1=$(tolower $1)

	if [ "$PARAM1" == "clean" ] || [ "$PARAM1" == "-c" ] ; then
		clean
	elif [ "$PARAM1" == "help" ] || [ "$PARAM1" == "-h" ] ; then
		display_help
	elif [ "$PARAM1" == "build" ] ; then
		compile
		link
		push
	elif [ "$PARAM1" == "compile" ] ; then
		compile
	elif [ "$PARAM1" == "link" ] ; then
		link
	elif [ "$PARAM1" == "push" ] ; then
		push
	elif [ "$PARAM1" == "run" ] ; then
		run
	elif [ "$PARAM1" == "brun" ] ; then
		compile
		link
		push
		run
	else
		invalid_command
		exit 1
	fi
elif [[ $# -eq 2 ]] ; then
	PARAM1=$(tolower $1)
	PARAM2=$(tolower $2)

	if [[ "$PARAM1" == "compile"  &&  "$PARAM2" == "-v" ]] ; then
		compile_verbose
	elif [ "$PARAM1" == "push" ] || [ "$PARAM1" == "-l" ] ; then
		link
		push
	elif [ "$PARAM1" == "build" ] || [ "$PARAM1" == "-v" ] ; then
		compile_verbose
		link
		push
	else
		invalid_command
		exit 1
	fi
else
	invalid_command
	exit 1
fi

