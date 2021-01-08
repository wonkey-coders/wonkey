
Namespace openvr

#If __DESKTOP_TARGET__

#If __TARGET__="windows"

#If __ARCH__="x86"
#Import "bin/win32/openvr_api.dll"
#Import "lib/win32/openvr_api.lib"
#Elseif __ARCH__="x64"
#Import "bin/win64/openvr_api.dll"
#Import "lib/win64/openvr_api.lib"
#endif

#Elseif __TARGET__="macos"

'#Import "bin/osx64/OpenVR.framework"

#Elseif __TARGET__="linux"

'#Import "bin/liux64/libopenvr_api.so"

#Endif

#Import "headers/*.h"
#Import "glue.h"

Extern

Struct HmdMatrix34_t
	Field m:Float Ptr Ptr
End	

Struct HmdMatrix44_t
	Field m:Float Ptr Ptr
End

Struct HmdVector3_t
	Field v:Float Ptr
End

Enum EVRApplicationType
End

Const VRApplication_Scene:EVRApplicationType		'Application will submit 3D frames 

Enum EVRInitError
End
Const VRInitError_None:EVRInitError

Alias HmdError:EVRInitError

Function VR_IsHmdPresent:Bool()
Function VR_IsRuntimeInstalled:Bool()
Function VR_RuntimePath:CString()
Function VR_Init:IVRSystem( peError:HmdError Ptr,eApplicationType:EVRApplicationType )
Function VR_GetVRInitErrorAsSymbol:CString( error:EVRInitError )
Function VR_Shutdown()

Function VRSystem:IVRSystem()	
Function VRCompositor:IVRCompositor()
Function VROverlay:IVROverlay()
	
'***** System *****

Alias TrackedDeviceIndex_t:UInt

Enum EVREye
End
Const Eye_Left:EVREye
Const Eye_Right:EVREye

Const k_unTrackedDeviceIndexInvalid:UInt
Const k_unMaxTrackedDeviceCount:UInt
Const k_unTrackedDeviceIndex_Hmd:UInt

Enum ETrackingResult
End
Const TrackingResult_Uninitialized:ETrackingResult
const TrackingResult_Calibrating_InProgress:ETrackingResult
Const TrackingResult_Calibrating_OutOfRange:ETrackingResult
Const TrackingResult_Running_OK:ETrackingResult
Const TrackingResult_Running_OutOfRange:ETrackingResult

Enum ETrackedDeviceClass
End
Const TrackedDeviceClass_Invalid:ETrackedDeviceClass					'0: ID was not valid.
Const TrackedDeviceClass_HMD:ETrackedDeviceClass						'1: "Head-Mounted Displays
Const TrackedDeviceClass_Controller:ETrackedDeviceClass					'2: Tracked controllers
Const TrackedDeviceClass_GenericTracker:ETrackedDeviceClass				'3: Generic trackers, similar to controllers
Const TrackedDeviceClass_TrackingReference:ETrackedDeviceClass			'4: Camera and base stations that serve as tracking reference points
Const TrackedDeviceClass_DisplayRedirect:ETrackedDeviceClass			'5: Accessories that aren't necessarily tracked themselves, but may redirect video output from other tracked devices

'Describes what specific role associated with a tracked device */
Enum ETrackedControllerRole
End
Const TrackedControllerRole_Invalid:ETrackedControllerRole				'Invalid value for controller type
Const TrackedControllerRole_LeftHand:ETrackedControllerRole				'Tracked device associated with the left hand
Const TrackedControllerRole_RightHand:ETrackedControllerRole			'Tracked device associated with the right hand

'describes a single pose for a tracked object
Struct TrackedDevicePose_t
	
	Field mDeviceToAbsoluteTracking:HmdMatrix34_t
	Field vVelocity:HmdVector3_t					'velocity in tracker space in m/s
	field vAngularVelocity:HmdVector3_t				'angular velocity in radians/s (?)
	
	Field eTrackingResult:ETrackingResult
	
	Field bPoseIsValid:bool

	'This indicates that there is a device connected for this spot in the pose array.
	'It could go from true to false if the user unplugs the device.
	Field bDeviceIsConnected:Bool
End

enum ETrackingUniverseOrigin
End
Const TrackingUniverseSeated:ETrackingUniverseOrigin					'Poses are provided relative to the seated zero pose
Const TrackingUniverseStanding:ETrackingUniverseOrigin					'Poses are provided relative to the safe bounds configured by the user
Const TrackingUniverseRawAndUncalibrated:ETrackingUniverseOrigin		'Poses are provided in the coordinate system defined by the driver.  It has Y up and is unified for devices of the same driver. You usually don't want this one.
 
enum EVREventType
End
Const VREvent_None:EVREventType
Const VREvent_TrackedDeviceActivated:EVREventType
Const VREvent_TrackedDeviceDeactivated:EVREventType
Const VREvent_TrackedDeviceUpdated:EVREventType
Const VREvent_TrackedDeviceUserInteractionStarted:EVREventType
Const VREvent_TrackedDeviceUserInteractionEnded:EVREventType
Const VREvent_IpdChanged:EVREventType
Const VREvent_EnterStandbyMode:EVREventType
Const VREvent_LeaveStandbyMode:EVREventType
Const VREvent_TrackedDeviceRoleChanged:EVREventType
Const VREvent_WatchdogWakeUpRequested:EVREventType
Const VREvent_LensDistortionChanged:EVREventType
Const VREvent_PropertyChanged:EVREventType
Const VREvent_WirelessDisconnect:EVREventType
Const VREvent_WirelessReconnect:EVREventType
Const VREvent_ButtonPress:EVREventType
Const VREvent_ButtonUnpress:EVREventType
Const VREvent_ButtonTouch:EVREventType
Const VREvent_ButtonUntouch:EVREventType
Const VREvent_MouseMove:EVREventType
Const VREvent_MouseButtonDown:EVREventType
Const VREvent_MouseButtonUp:EVREventType
Const VREvent_FocusEnter:EVREventType
Const VREvent_FocusLeave:EVREventType
Const VREvent_Scroll:EVREventType
Const VREvent_TouchPadMove:EVREventType
Const VREvent_OverlayFocusChanged:EVREventType
Const VREvent_InputFocusCaptured:EVREventType
Const VREvent_InputFocusReleased:EVREventType
Const VREvent_SceneFocusLost:EVREventType
Const VREvent_SceneFocusGained:EVREventType
Const VREvent_SceneApplicationChanged:EVREventType
Const VREvent_SceneFocusChanged:EVREventType
Const VREvent_InputFocusChanged:EVREventType
Const VREvent_SceneApplicationSecondaryRenderingStarted:EVREventType
Const VREvent_HideRenderModels:EVREventType
Const VREvent_ShowRenderModels:EVREventType
Const VREvent_OverlayShown:EVREventType
Const VREvent_OverlayHidden:EVREventType
Const VREvent_DashboardActivated:EVREventType
Const VREvent_DashboardDeactivated:EVREventType
Const VREvent_DashboardThumbSelected:EVREventType
Const VREvent_DashboardRequested:EVREventType
Const VREvent_ResetDashboard:EVREventType
Const VREvent_RenderToast:EVREventType
Const VREvent_ImageLoaded:EVREventType
Const VREvent_ShowKeyboard:EVREventType
Const VREvent_HideKeyboard:EVREventType
Const VREvent_OverlayGamepadFocusGained:EVREventType
Const VREvent_OverlayGamepadFocusLost:EVREventType
Const VREvent_OverlaySharedTextureChanged:EVREventType
Const VREvent_DashboardGuideButtonDown:EVREventType
Const VREvent_DashboardGuideButtonUp:EVREventType
Const VREvent_ScreenshotTriggered:EVREventType
Const VREvent_ImageFailed:EVREventType
Const VREvent_DashboardOverlayCreated:EVREventType
Const VREvent_RequestScreenshot:EVREventType
Const VREvent_ScreenshotTaken:EVREventType
Const VREvent_ScreenshotFailed:EVREventType
Const VREvent_SubmitScreenshotToDashboard:EVREventType
Const VREvent_ScreenshotProgressToDashboard:EVREventType
Const VREvent_PrimaryDashboardDeviceChanged:EVREventType
Const VREvent_Notification_Shown:EVREventType
Const VREvent_Notification_Hidden:EVREventType
Const VREvent_Notification_BeginInteraction:EVREventType
Const VREvent_Notification_Destroyed:EVREventType
Const VREvent_Quit:EVREventType
Const VREvent_ProcessQuit:EVREventType
Const VREvent_QuitAborted_UserPrompt:EVREventType
Const VREvent_QuitAcknowledged:EVREventType
Const VREvent_DriverRequestedQuit:EVREventType
Const VREvent_ChaperoneDataHasChanged:EVREventType
Const VREvent_ChaperoneUniverseHasChanged:EVREventType
Const VREvent_ChaperoneTempDataHasChanged:EVREventType
Const VREvent_ChaperoneSettingsHaveChanged:EVREventType
Const VREvent_SeatedZeroPoseReset:EVREventType
Const VREvent_AudioSettingsHaveChanged:EVREventType
Const VREvent_BackgroundSettingHasChanged:EVREventType
Const VREvent_CameraSettingsHaveChanged:EVREventType
Const VREvent_ReprojectionSettingHasChanged:EVREventType
Const VREvent_ModelSkinSettingsHaveChanged:EVREventType
Const VREvent_EnvironmentSettingsHaveChanged:EVREventType
Const VREvent_PowerSettingsHaveChanged:EVREventType
Const VREvent_EnableHomeAppSettingsHaveChanged:EVREventType
Const VREvent_StatusUpdate:EVREventType
Const VREvent_MCImageUpdated:EVREventType
Const VREvent_FirmwareUpdateStarted:EVREventType
Const VREvent_FirmwareUpdateFinished:EVREventType
Const VREvent_KeyboardClosed:EVREventType
Const VREvent_KeyboardCharInput:EVREventType
Const VREvent_KeyboardDone:EVREventType
Const VREvent_ApplicationTransitionStarted:EVREventType
Const VREvent_ApplicationTransitionAborted:EVREventType
Const VREvent_ApplicationTransitionNewAppStarted:EVREventType
Const VREvent_ApplicationListUpdated:EVREventType
Const VREvent_ApplicationMimeTypeLoad:EVREventType
Const VREvent_ApplicationTransitionNewAppLaunchComplete:EVREventType
Const VREvent_ProcessConnected:EVREventType
Const VREvent_ProcessDisconnected:EVREventType
Const VREvent_Compositor_MirrorWindowShown:EVREventType
Const VREvent_Compositor_MirrorWindowHidden:EVREventType
Const VREvent_Compositor_ChaperoneBoundsShown:EVREventType
Const VREvent_Compositor_ChaperoneBoundsHidden:EVREventType
Const VREvent_TrackedCamera_StartVideoStream:EVREventType
Const VREvent_TrackedCamera_StopVideoStream:EVREventType
Const VREvent_TrackedCamera_PauseVideoStream:EVREventType
Const VREvent_TrackedCamera_ResumeVideoStream:EVREventType
Const VREvent_TrackedCamera_EditingSurface:EVREventType
Const VREvent_PerformanceTest_EnableCapture:EVREventType
Const VREvent_PerformanceTest_DisableCapture:EVREventType
Const VREvent_PerformanceTest_FidelityLevel:EVREventType
Const VREvent_MessageOverlay_Closed:EVREventType
Const VREvent_MessageOverlayCloseRequested:EVREventType
Const VREvent_VendorSpecific_Reserved_Start:EVREventType
Const VREvent_VendorSpecific_Reserved_End:EVREventType

Enum EVRButtonId
End
Const k_EButton_System:EVRButtonId
Const k_EButton_ApplicationMenu:EVRButtonId
Const k_EButton_Grip:EVRButtonId
Const k_EButton_DPad_Left:EVRButtonId
Const k_EButton_DPad_Up:EVRButtonId
Const k_EButton_DPad_Right:EVRButtonId
Const k_EButton_DPad_Down:EVRButtonId
Const k_EButton_A:EVRButtonId
Const k_EButton_ProximitySensor:EVRButtonId
Const k_EButton_Axis0:EVRButtonId
Const k_EButton_Axis1:EVRButtonId
Const k_EButton_Axis2:EVRButtonId
Const k_EButton_Axis3:EVRButtonId
Const k_EButton_Axis4:EVRButtonId
Const k_EButton_SteamVR_Touchpad:EVRButtonId
Const k_EButton_SteamVR_Trigger:EVRButtonId
Const k_EButton_Dashboard_Back:EVRButtonId
Const k_EButton_Max:EVRButtonId

Struct VREvent_Controller_t
	Field button:UInt	'EVRButtonId Enum
End

'Hmmm, not actually the controller touchpad!
struct VREvent_TouchPadMove_t
	Field bFingerDown:Bool
	Field flSecondsFingerDown:Float
	Field fValueXFirst:Float
	Field fValueYFirst:Float
	Field fValueXRaw:Float
	Field fValueYRaw:Float
End

Struct VREvent_Data_t
	Field controller:VREvent_Controller_t
	Field touchPadMove:VREvent_TouchPadMove_t
End
 
Struct VREvent_t
	'	
	Field eventType:UInt		'EVREventType enum
	Field trackedDeviceIndex:UInt
	Field eventAgeSeconds:Float
	'
	Field data:VREvent_Data_t
End

Enum EVRControllerAxisType
End
Const k_eControllerAxis_None:EVRControllerAxisType
Const k_eControllerAxis_TrackPad:EVRControllerAxisType
Const k_eControllerAxis_Joystick:EVRControllerAxisType
Const k_eControllerAxis_Trigger:EVRControllerAxisType

Struct VRControllerAxis_t
	Field x:Float	'Ranges from -1.0 to 1.0 for joysticks and track pads. Ranges from 0.0 to 1.0 for triggers were 0 is fully released.
	Field y:Float	'Ranges from -1.0 to 1.0 for joysticks and track pads. Is always 0.0 for triggers.
End

Const k_unControllerStateAxisCount:UInt

Struct VRControllerState001_t
	'If packet num matches that on your prior call, then the controller state hasn't been changed since 
	'your last call and there is no need to process it
	Field unPacketNum:Uint

	'bit flags for each of the buttons. Use ButtonMaskFromId to turn an ID into a mask
	Field ulButtonPressed:ULong
	Field ulButtonTouched:ULong

	'Axis data for the controller's analog inputs
	Field rAxis:VRControllerAxis_t Ptr	'[k_unControllerStateAxisCount]
End

Alias VRControllerState_t:VRControllerState001_t
 
Class IVRSystem Extends Void
	
	'------------------------------------
	'Display Methods
	'------------------------------------

	'Suggested size for the intermediate render target that the distortion pulls from.
	Method GetRecommendedRenderTargetSize( pnWidth:UInt Ptr,pnHeight:UInt Ptr )

	'The projection matrix for the specified eye
	Method GetProjectionMatrix:HmdMatrix44_t( eEye:EVREye,fNearZ:float,fFarZ:Float )
		
	'The components necessary to build your own projection matrix in case your
	'application is doing something fancy like infinite Z
	Method GetProjectionRaw( eEye:EVREye,pfLeft:Float Ptr,pfRight:Float Ptr,pfTop:Float Ptr,pfBottom:Float Ptr )
		
	'Returns the transform from eye space to the head space. Eye space is the per-eye flavor of head
	'space that provides stereo disparity. Instead of Model * View * Projection the sequence is Model * View * Eye^-1 * Projection. 
	'Normally View and Eye^-1 will be multiplied together and treated as View in your application. 
	Method GetEyeToHeadTransform:HmdMatrix34_t( eEye:EVREye )
		
	'Returns the number of elapsed seconds since the last recorded vsync event. This 
	'will come from a vsync timer event in the timer if possible or from the application-reported
	'time if that is not available. If no vsync times are available the function will 
	'return zero for vsync time and frame counter and return false from the method. */
	Method GetTimeSinceLastVsync:Bool( pfSecondsSinceLastVsync:Float Ptr,pulFrameCounter:ULong Ptr )
		
	' ------------------------------------
	'Tracking Methods
	'------------------------------------

	'The pose that the tracker thinks that the HMD will be in at the specified number of seconds into the 
	'future. Pass 0 to get the state at the instant the method is called. Most of the time the application should
	'calculate the time until the photons will be emitted from the display and pass that time into the method.
	'
	'This is roughly analogous to the inverse of the view matrix in most applications, though 
	'many games will need to do some additional rotation or translation on top of the rotation
	'and translation provided by the head pose.
	'
	'For devices where bPoseIsValid is true the application can use the pose to position the device
	'in question. The provided array can be any size up to k_unMaxTrackedDeviceCount. 
	'
	'Seated experiences should call this method with TrackingUniverseSeated and receive poses relative
	'to the seated zero pose. Standing experiences should call this method with TrackingUniverseStanding 
	'and receive poses relative to the Chaperone Play Area. TrackingUniverseRawAndUncalibrated should 
	'probably not be used unless the application is the Chaperone calibration tool itself, but will provide
	'poses relative to the hardware-specific coordinate system in the driver.
	Method GetDeviceToAbsoluteTrackingPose( eOrigin:ETrackingUniverseOrigin,fPredictedSecondsToPhotonsFromNow:Float,pTrackedDevicePoseArray:TrackedDevicePose_t Ptr,trackedDevicePoseArrayCount:UInt )

	'Sets the zero pose for the seated tracker coordinate system to the current position and yaw of the HMD. After 
	'ResetSeatedZeroPose all GetDeviceToAbsoluteTrackingPose calls that pass TrackingUniverseSeated as the origin 
	'will be relative to this new zero pose. The new zero coordinate system will not change the fact that the Y axis 
	'is up in the real world, so the next pose returned from GetDeviceToAbsoluteTrackingPose after a call to 
	'ResetSeatedZeroPose may not be exactly an identity matrix.
	'
	'NOTE: This function overrides the user's previously saved seated zero pose and should only be called as the result of a user action. 
	'Users are also able to set their seated zero pose via the OpenVR Dashboard.
	'
	Method ResetSeatedZeroPose()

	'Returns the transform from the seated zero pose to the standing absolute tracking system. This allows 
	'applications to represent the seated origin to used or transform object positions from one coordinate
	'system to the other. 
	'
	'The seated origin may or may not be inside the Play Area or Collision Bounds returned by IVRChaperone. Its position 
	'depends on what the user has set from the Dashboard settings and previous calls to ResetSeatedZeroPose. */
	Method GetSeatedZeroPoseToStandingAbsoluteTrackingPose:HmdMatrix34_t()
		
	'Get a sorted array of device indices of a given class of tracked devices (e.g. controllers).  Devices are sorted right to left
	'relative to the specified tracked device (default: hmd -- pass in -1 for absolute tracking space).  Returns the number of devices
	'in the list, or the size of the array needed if not large enough. */
	Method GetSortedTrackedDeviceIndicesOfClass:UInt( 
		eTrackedDeviceClass:ETrackedDeviceClass,
		punTrackedDeviceIndexArray:TrackedDeviceIndex_t Ptr,unTrackedDeviceIndexArrayCount:UInt,
		unRelativeToTrackedDeviceIndex:TrackedDeviceIndex_t = k_unTrackedDeviceIndex_Hmd )
		
	'Returns the device index associated with a specific role, for example the left hand or the right hand. */
	Method GetTrackedDeviceIndexForControllerRole:TrackedDeviceIndex_t( unDeviceType:ETrackedControllerRole )

	'Returns the controller type associated with a device index. */
	Method GetControllerRoleForTrackedDeviceIndex:ETrackedControllerRole( unDeviceIndex:TrackedDeviceIndex_t )
		
	'------------------------------------
	'Property methods
	'------------------------------------

	'Returns the device class of a tracked device. If there has not been a device connected in this slot
	'since the application started this function will return TrackedDevice_Invalid. For previous detected
	'devices the function will return the previously observed device class. 
	'
	'To determine which devices exist on the system, just loop from 0 to k_unMaxTrackedDeviceCount and check
	'the device class. Every device with something other than TrackedDevice_Invalid is associated with an 
	'actual tracked device. */
	Method GetTrackedDeviceClass:ETrackedDeviceClass( unDeviceIndex:TrackedDeviceIndex_t )

	'Returns true if there is a device connected in this slot. */
	Method IsTrackedDeviceConnected:Bool( unDeviceIndex:TrackedDeviceIndex_t )
		
	'------------------------------------
	'Event methods
	'------------------------------------

	'Returns true and fills the event with the next event on the queue if there is one. If there are no events
	'this method returns false. uncbVREvent should be the size in bytes of the VREvent_t struct */
	method PollNextEvent:bool( pEvent:VREvent_t Ptr,uncbVREvent:UInt )

	'Returns true and fills the event with the next event on the queue if there is one. If there are no events
	'this method returns false. Fills in the pose of the associated tracked device in the provided pose struct. 
	'This pose will always be older than the call to this function and should not be used to render the device. 
	'uncbVREvent should be the size in bytes of the VREvent_t struct */
	Method PollNextEventWithPose:Bool( oRigin:ETrackingUniverseOrigin,pEvent:VREvent_t Ptr,uncbVREvent:UInt,pTrackedDevicePose:TrackedDevicePose_t Ptr )

	'returns the name of an EVREvent enum value */
	Method GetEventTypeNameFromEnum:CString( eType:EVREventType )
		

	'------------------------------------
	'Controller methods
	'------------------------------------

	'Fills the supplied struct with the current state of the controller. Returns false if the controller index
	'is invalid.
	Method GetControllerState:Bool( unControllerDeviceIndex:TrackedDeviceIndex_t,pControllerState:VRControllerState_t Ptr,unControllerStateSize:uint  )

	'fills the supplied struct with the current state of the controller and the provided pose with the pose of 
	'the controller when the controller state was updated most recently. Use this form if you need a precise controller
	'pose as input to your application when the user presses or releases a button. */
	Method GetControllerStateWithPose:Bool( eOrigin:ETrackingUniverseOrigin,unControllerDeviceIndex:TrackedDeviceIndex_t,pControllerState:VRControllerState_t Ptr,unControllerStateSize:UInt,pTrackedDevicePose:TrackedDevicePose_t Ptr )
		
	'Trigger a single haptic pulse on a controller. After this call the application may not trigger another haptic pulse on this controller
	'and axis combination for 5ms. */
	Method TriggerHapticPulse:Void( unControllerDeviceIndex:TrackedDeviceIndex_t,unAxisId:UInt,usDurationMicroSec:UShort )
		
	'returns the name of an EVRButtonId enum value */
	Method GetButtonIdNameFromEnum:CString( eButtonId:EVRButtonId )

	'returns the name of an EVRControllerAxisType enum value */
	Method GetControllerAxisTypeNameFromEnum:CString( eAxisType:EVRControllerAxisType )
		
End

'***** Compositor *****

enum EVRCompositorError
End
Const VRCompositorError_None:EVRCompositorError
Const VRCompositorError_RequestFailed:EVRCompositorError
Const VRCompositorError_IncompatibleVersion:EVRCompositorError
Const VRCompositorError_DoNotHaveFocus:EVRCompositorError
Const VRCompositorError_InvalidTexture:EVRCompositorError
Const VRCompositorError_IsNotSceneApplication:EVRCompositorError
Const VRCompositorError_TextureIsOnWrongDevice:EVRCompositorError
Const VRCompositorError_TextureUsesUnsupportedFormat:EVRCompositorError
Const VRCompositorError_SharedTexturesNotSupported:EVRCompositorError
Const VRCompositorError_IndexOutOfRange:EVRCompositorError
Const VRCompositorError_AlreadySubmitted:EVRCompositorError
Const VRCompositorError_InvalidBounds:EVRCompositorError

enum EVRSubmitFlags
End
'Simple render path. App submits rendered left and right eye images with no lens distortion correction applied.
Const Submit_Default:EVRSubmitFlags
 
'App submits final left and right eye images with lens distortion already applied (lens distortion makes the images appear
'barrel distorted with chromatic aberration correction applied). The app would have used the data returned by
'vr::IVRSystem::ComputeDistortion() to apply the correct distortion to the rendered images before calling Submit().
Const Submit_LensDistortionAlreadyApplied:EVRSubmitFlags

'If the texture pointer passed in is actually a renderbuffer (e.g. for MSAA in OpenGL) then set this flag.
Const Submit_GlRenderBuffer:EVRSubmitFlags

'Do not use
Const Submit_Reserved:EVRSubmitFlags

'Set to indicate that pTexture is a pointer to a VRTextureWithPose_t.
Const Submit_TextureWithPose:EVRSubmitFlags

enum ETextureType
End
Const TextureType_OpenGL:ETextureType	'Handle is an OpenGL texture name or an OpenGL render buffer name, depending on submit flags
Const TextureType_Vulkan:ETextureType	'Handle is a pointer to a VRVulkanTextureData_t structure

enum EColorSpace
End
Const ColorSpace_Auto:EColorSpace		'Assumes 'gamma' for 8-bit per component formats, otherwise 'linear'.  This mirrors the DXGI formats which have _SRGB variants.
Const ColorSpace_Gamma:EColorSpace		'Texture data can be displayed directly on the display without any conversion (a.k.a. display native format).
Const ColorSpace_Linear:EColorSpace		'Same as gamma but has been converted to a linear representation using DXGI's sRGB conversion algorithm.

struct Texture_t
	Field handle:Void Ptr
	Field eType:ETextureType
	Field eColorSpace:EColorSpace
End

'Allows the application to control what part of the provided texture will be used in the
'frame buffer.
struct VRTextureBounds_t
	Field uMin:Float
	Field vMin:Float
	Field uMax:Float
	Field vMax:Float
End

Class IVRCompositor Extends Void
	
	'Sets tracking space returned by WaitGetPoses */
	Method SetTrackingSpace( eOrigin:ETrackingUniverseOrigin )
	

	'Scene applications should call this function to get poses to render with (and optionally poses predicted an additional frame out to use for gameplay).
	'This function will block until "running start" milliseconds before the start of the frame, and should be called at the last moment before needing to
	'start rendering.
	'
	'Return codes:
	'	- IsNotSceneApplication (make sure to call VR_Init with VRApplicaiton_Scene)
	'	- DoNotHaveFocus (some other app has taken focus - this will throttle the call to 10hz to reduce the impact on that app)
	Method WaitGetPoses:EVRCompositorError( 
		pRenderPoseArray:TrackedDevicePose_t Ptr,unRenderPoseArrayCount:UInt,
		pGamePoseArray:TrackedDevicePose_t Ptr,unGamePoseArrayCount:UInt )

	'Updated scene texture to display. If pBounds is NULL the entire texture will be used.  If called from an OpenGL app, consider adding a glFlush after
	'Submitting both frames to signal the driver to start processing, otherwise it may wait until the command buffer fills up, causing the app to miss frames.
	'
	'OpenGL dirty state:
	'	glBindTexture
	'
	'Return codes:
	'	- IsNotSceneApplication (make sure to call VR_Init with VRApplicaiton_Scene)
	'	- DoNotHaveFocus (some other app has taken focus)
	'	- TextureIsOnWrongDevice (application did not use proper AdapterIndex - see IVRSystem.GetDXGIOutputInfo)
	'	- SharedTexturesNotSupported (application needs to call CreateDXGIFactory1 or later before creating DX device)
	'	- TextureUsesUnsupportedFormat (scene textures must be compatible with DXGI sharing rules - e.g. uncompressed, no mips, etc.)
	'	- InvalidTexture (usually means bad arguments passed in)
	'	- AlreadySubmitted (app has submitted two left textures or two right textures in a single frame - i.e. before calling WaitGetPoses again)
	Method Submit:EVRCompositorError( eEye:EVREye,pTexture:Texture_t Ptr,pBounds:VRTextureBounds_t Ptr=Null,nSubmitFlags:EVRSubmitFlags=Submit_Default )

	'Clears the frame that was sent with the last call to Submit. This will cause the 
	'compositor to show the grid until Submit is called again. */
	Method ClearLastSubmittedFrame()

	'Call immediately after presenting your app's window (i.e. companion window) to unblock the compositor.
	'This is an optional call, which only needs to be used if you can't instead call WaitGetPoses immediately after Present.
	'For example, if your engine's render and game loop are not on separate threads, or blocking the render thread until 3ms before the next vsync would
	'introduce a deadlock of some sort.  This function tells the compositor that you have finished all rendering after having Submitted buffers for both
	'eyes, and it is free to start its rendering work.  This should only be called from the same thread you are rendering on. */
	Method PostPresentHandoff()

End

Class IVROverlay Extends Void
	
	'** Returns true if the dashboard is visible */
	Method IsDashboardVisible:Bool()

End

#end
