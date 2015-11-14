# set params
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
#NDK_ROOT=__ndkroot__
#COCOS2DX_ROOT=__cocos2dxroot__
#GAME_ROOT=$COCOS2DX_ROOT/projects/__projectname__
#GAME_ANDROID_ROOT=$GAME_ROOT/android
#RESOURCE_ROOT=$GAME_ROOT/Resources

NDK_MODULE_PATH="$DIR/../../cocos2d-1.0.1-x-0.13.0-beta"
if [ ! -d "$NDK_MODULE_PATH" ]; then
    NDK_MODULE_PATH="$DIR/../../../cocos2d-1.0.1-x-0.13.0-beta/workspace"
fi

COCOS2DX_ROOT="$DIR/../../cocos2d-1.0.1-x-0.13.0-beta"
if [ ! -d "$COCOS2DX_ROOT" ]; then
    COCOS2DX_ROOT="$DIR/../../../cocos2d-1.0.1-x-0.13.0-beta/workspace"
fi

GAME_ROOT="$DIR/.."
GAME_ANDROID_ROOT=$GAME_ROOT/android
RESOURCE_ROOT=$GAME_ROOT/Resources

buildexternalsfromsource=

usage(){
cat << EOF
usage: $0 [options]

Build C/C++ native code using Android NDK

OPTIONS:
   -s	Build externals from source
   -h	this help
EOF
}

while getopts "s" OPTION; do
	case "$OPTION" in
		s)
			buildexternalsfromsource=1
			;;
		h)
			usage
			exit 0
			;;
	esac
done

# make sure assets is exist
if [ -d $GAME_ANDROID_ROOT/assets ]; then
    rm -rf $GAME_ANDROID_ROOT/assets
fi

mkdir $GAME_ANDROID_ROOT/assets

# copy resources
for file in $RESOURCE_ROOT/*
do
    if [ -d $file ]; then
        cp -rf $file $GAME_ANDROID_ROOT/assets
    fi

    if [ -f $file ]; then
        cp $file $GAME_ANDROID_ROOT/assets
    fi
done

if [[ $buildexternalsfromsource ]]; then
    echo "Building external dependencies from source"
    $NDK_ROOT/ndk-build -C $GAME_ANDROID_ROOT \
        NDK_MODULE_PATH=${COCOS2DX_ROOT}:${COCOS2DX_ROOT}/cocos2dx/platform/third_party/android/source
else
    echo "Using prebuilt externals"
    $NDK_ROOT/ndk-build -C $GAME_ANDROID_ROOT \
        NDK_MODULE_PATH=${COCOS2DX_ROOT}:${COCOS2DX_ROOT}/cocos2dx/platform/third_party/android/prebuilt
fi



