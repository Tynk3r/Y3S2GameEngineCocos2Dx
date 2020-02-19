LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
                   $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
                   $(LOCAL_PATH)/../../../Classes/HelloWorldScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/LoadingScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/MainMenuScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/Nodes.cpp \
                   $(LOCAL_PATH)/../../../Classes/SpaceshipScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/Anim/CAnimation.cpp \
                   $(LOCAL_PATH)/../../../Classes/Input/InputAction.cpp \
                   $(LOCAL_PATH)/../../../Classes/Input/InputActionMap.cpp \
                   $(LOCAL_PATH)/../../../Classes/Input/InputManager.cpp \
                   $(LOCAL_PATH)/../../../Classes/SceneManagement/SceneManager.cpp \
                   $(LOCAL_PATH)/../../../Classes/UI/UI.cpp \
                   $(LOCAL_PATH)/../../../Classes/HUDLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/Joystick.cpp \
                   $(LOCAL_PATH)/../../../Classes/AI/State.cpp \
                   $(LOCAL_PATH)/../../../Classes/AI/StateEnemyAttack.cpp \
                   $(LOCAL_PATH)/../../../Classes/AI/StateEnemyIdle.cpp \
                   $(LOCAL_PATH)/../../../Classes/AI/StateEnemyRetreat.cpp \
                   $(LOCAL_PATH)/../../../Classes/AI/StateMachine.cpp \
                   $(LOCAL_PATH)/../../../Classes/Shop.cpp \
                   $(LOCAL_PATH)/../../../Classes/GameObject.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes \
					$(LOCAL_PATH)/../../../Classes/Anim \
					$(LOCAL_PATH)/../../../Classes/Input \
					$(LOCAL_PATH)/../../../Classes/SceneManagement \
					$(LOCAL_PATH)/../../../Classes/UI \
					$(LOCAL_PATH)/../../../Classes/AI \
					$(LOCAL_PATH)/../../include

LOCAL_LDLIBS := $(LOCAL_PATH)/../../libs/arm64-v8a/libchilkatAndroid.a \
                $(LOCAL_PATH)/../../libs/armeabi-v7a/libchilkatAndroid.a \
                $(LOCAL_PATH)/../../libs/x86/libchilkatAndroid.a \
                $(LOCAL_PATH)/../../libs/x86_64/libchilkatAndroid.a

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cc_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module, cocos)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
