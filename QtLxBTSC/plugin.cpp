/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2018 Luch (https://github.com/Luch00)
*/

#ifdef _WIN32
#pragma warning (disable : 4100)  /* Disable Unreferenced parameter warning */
#include <Windows.h>
#endif

#include "plugin.h"
#include "PluginHelper.h"

#define PLUGIN_API_VERSION 22
#define PATH_BUFSIZE 512

static char* pluginID = nullptr;
PluginHelper* helper;

/*********************************** Required functions ************************************/
/*
 * If any of these required functions is not implemented, TS3 will refuse to load the plugin
 */

/* Unique name identifying this plugin */
const char* ts3plugin_name() {
	return "Better Chat";
}

/* Plugin version */
const char* ts3plugin_version() {
    return "1.11.1";
}

/* Plugin API version. Must be the same as the clients API major version, else the plugin fails to load. */
int ts3plugin_apiVersion() {
	return PLUGIN_API_VERSION;
}

/* Plugin author */
const char* ts3plugin_author() {
	/* If you want to use wchar_t, see ts3plugin_name() on how to use */
    return "Luch";
}

/* Plugin description */
const char* ts3plugin_description() {
	/* If you want to use wchar_t, see ts3plugin_name() on how to use */
    return "Better text chat";
}

/* Set TeamSpeak 3 callback functions */
void ts3plugin_setFunctionPointers(const struct TS3Functions funcs) {
    ts3Functions = funcs;
}

// Init plugin
int ts3plugin_init() {
	char pluginPath[PATH_BUFSIZE];

	ts3Functions.createReturnCode(pluginID, returnCodeEmoteFileInfo, 64);
	ts3Functions.createReturnCode(pluginID, returnCodeEmoteFileRequest, 64);
	ts3Functions.getPluginPath(pluginPath, PATH_BUFSIZE, pluginID);
	helper = new PluginHelper(pluginPath);

    return 0;
}

/* Custom code called right before the plugin is unloaded */
void ts3plugin_shutdown() {
    /* Your plugin cleanup code here */
	delete helper;

	/* Free pluginID if we registered it */
	if(pluginID) {
		free(pluginID);
		pluginID = NULL;
	}
}

/****************************** Optional functions ********************************/
/*
 * Following functions are optional, if not needed you don't need to implement them.
 */

void ts3plugin_registerPluginID(const char* id) {
	int len = strlen(id);
	pluginID = static_cast<char*>(malloc(len + 1));
	memcpy(pluginID, id, len + 1);
}

/* Plugin command keyword. Return NULL or "" if not used. */
const char* ts3plugin_commandKeyword() {
	return "lxb";
}

/* Plugin processes console command. Return 0 if plugin handled the command, 1 if not handled. */
int ts3plugin_processCommand(uint64 serverConnectionHandlerID, const char* command) {
	if (strcmp(command, "toggle") == 0)
	{
		helper->toggleNormalChat();
	}
	if (strcmp(command, "reload") == 0)
	{
		helper->reload();
	}
	if (strcmp(command, "emotes") == 0)
	{
		helper->fullReloadEmotes();
	}
	return 0;  /* Plugin handled command */
}

/* Client changed current server connection handler */
/*void ts3plugin_currentServerConnectionChanged(uint64 serverConnectionHandlerID) {
	helper->currentServerChanged(serverConnectionHandlerID);
}*/

/* Required to release the memory for parameter "data" allocated in ts3plugin_infoData and ts3plugin_initMenus */
void ts3plugin_freeMemory(void* data) {
	free(data);
}

int ts3plugin_requestAutoload() {
	return 0;  /* 1 = request autoloaded, 0 = do not request autoload */
}

/************************** TeamSpeak callbacks ***************************/
/*
 * Following functions are optional, feel free to remove unused callbacks.
 * See the clientlib documentation for details on each function.
 */

/* Clientlib */

// connected to or disconnected from a server
void ts3plugin_onConnectStatusChangeEvent(uint64 serverConnectionHandlerID, int newStatus, unsigned int errorNumber) {
	if (newStatus == STATUS_CONNECTION_ESTABLISHED)
	{
		helper->serverConnected(serverConnectionHandlerID);
	}
	if (newStatus == STATUS_DISCONNECTED)
	{
		helper->serverDisconnected(serverConnectionHandlerID);
	}
}

// Show a status message when a client connects or disconnects
void ts3plugin_onClientMoveEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* moveMessage) {
	if (oldChannelID == 0)
	{
		helper->clientConnected(serverConnectionHandlerID, clientID);
	}
	else if (newChannelID == 0)
	{
		helper->clientDisconnected(serverConnectionHandlerID, clientID, moveMessage);
	}
	else if (visibility == ENTER_VISIBILITY)
	{
		helper->clientEnteredView(serverConnectionHandlerID, clientID);
	}
}

// client drops connection
void ts3plugin_onClientMoveTimeoutEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* timeoutMessage) {
	helper->clientTimeout(serverConnectionHandlerID, clientID);
}

int ts3plugin_onServerErrorEvent(uint64 serverConnectionHandlerID, const char* errorMessage, unsigned int error, const char* returnCode, const char* extraMessage) {

	if (error == ERROR_ok) // on success, ignore
		return 1;

	if (strcmp(returnCode, returnCodeEmoteFileRequest) == 0)
	{
		ts3Functions.logMessage(QString("Could not dowload emotes, %1").arg(errorMessage).toLatin1(), LogLevel_INFO, "BetterChat", 0);
		return 1;
	}
	if (strcmp(returnCode, returnCodeEmoteFileInfo) == 0)
	{
		ts3Functions.logMessage(QString("Could not get emote fileinfo, %1").arg(errorMessage).toLatin1(), LogLevel_INFO, "BetterChat", 0);
		return 1;
	}
	
	if(returnCode)
	{
		return 1;
	}

	/* A plugin could now check the returnCode with previously (when calling a function) remembered returnCodes and react accordingly
	 * In case of using a a plugin return code, the plugin can return:
	 * 0: Client will continue handling this error (print to chat tab)
	 * 1: Client will ignore this error, the plugin announces it has handled it */
	
	// RETURN CODES MUST HAVE PREFIX "PR:" FOR ANY OF THIS TO WORK!!!!!!!
	// Using createReturnCode will make a string in the format of "PR:<PluginID>:<ID>"
	
	return 0;
}

int ts3plugin_onServerPermissionErrorEvent(uint64 serverConnectionHandlerID, const char* errorMessage, unsigned int error, const char* returnCode, unsigned int failedPermissionID) {

	if (error == ERROR_ok) // on success, ignore
		return 1;

	if (strcmp(returnCode, returnCodeEmoteFileRequest) == 0)
	{
		ts3Functions.logMessage(QString("Could not dowload emotes, %1").arg(errorMessage).toLatin1(), LogLevel_INFO, "BetterChat", 0);
		return 1;
	}
	if (strcmp(returnCode, returnCodeEmoteFileInfo) == 0)
	{
		ts3Functions.logMessage(QString("Could not get emote fileinfo, %1").arg(errorMessage).toLatin1(), LogLevel_INFO, "BetterChat", 0);
		return 1;
	}

	if (returnCode)
	{
		return 1;
	}

	// See onServerErrorEvent for return code description
	return 0;
}

// Client received a text message
int ts3plugin_onTextMessageEvent(uint64 serverConnectionHandlerID, anyID targetMode, anyID toID, anyID fromID, const char* fromName, const char* fromUniqueIdentifier, const char* message, int ffIgnored) {

	/* Friend/Foe manager has ignored the message, so ignore here as well. */
	if(ffIgnored) {
		return 0; /* Client will ignore the message anyways, so return value here doesn't matter */
	}

	// get clients own ID
	anyID myID;
	if (ts3Functions.getClientID(serverConnectionHandlerID, &myID) != ERROR_ok) {
		ts3Functions.logMessage("Error querying own client id", LogLevel_ERROR, "Plugin", serverConnectionHandlerID);
		return 0;
	}

	helper->textMessageReceived(serverConnectionHandlerID, fromID, toID, targetMode, fromUniqueIdentifier, fromName, message, myID == fromID);
    return 0;  /* 0 = handle normally, 1 = client will ignore the text message */
}

// this is called when file transfer ends in some way
void ts3plugin_onFileTransferStatusEvent(anyID transferID, unsigned int status, const char* statusMessage, uint64 remotefileSize, uint64 serverConnectionHandlerID) {
	helper->transferStatusChanged(transferID, status);
}

/* Called when client custom nickname changed */
void ts3plugin_onClientDisplayNameChanged(uint64 serverConnectionHandlerID, anyID clientID, const char* displayName, const char* uniqueClientIdentifier) {
	helper->clientDisplayNameChanged(serverConnectionHandlerID, clientID, displayName);
}

int ts3plugin_onClientPokeEvent(uint64 serverConnectionHandlerID, anyID fromClientID, const char* pokerName, const char* pokerUniqueIdentity, const char* message, int ffIgnored) {
	if (ffIgnored)
		return 0;
	helper->poked(serverConnectionHandlerID, fromClientID, pokerName, pokerUniqueIdentity, message);
    return 0;  /* 0 = handle normally, 1 = client will ignore the poke */
}

/* Tell client if plugin offers a configuration window. If this function is not implemented, it's an assumed "does not offer" (PLUGIN_OFFERS_NO_CONFIGURE). */
int ts3plugin_offersConfigure() {
	return PLUGIN_OFFERS_CONFIGURE_QT_THREAD;
}

/* Plugin might offer a configuration window. If ts3plugin_offersConfigure returns 0, this function does not need to be implemented. */
void ts3plugin_configure(void* handle, void* qParentWidget) {
	helper->openConfig();
}

void ts3plugin_onServerStopEvent(uint64 serverConnectionHandlerID, const char* shutdownMessage) {
	helper->serverStopped(serverConnectionHandlerID, shutdownMessage);
}

void ts3plugin_onFileInfoEvent(uint64 serverConnectionHandlerID, uint64 channelID, const char* name, uint64 size, uint64 datetime) {
	helper->handleFileInfoEvent(serverConnectionHandlerID, channelID, name, size, datetime);
}

//void ts3plugin_onNewChannelEvent(uint64 serverConnectionHandlerID, uint64 channelID, uint64 channelParentID) {
//}

//void ts3plugin_onNewChannelCreatedEvent(uint64 serverConnectionHandlerID, uint64 channelID, uint64 channelParentID, anyID invokerID, const char* invokerName, const char* invokerUniqueIdentifier) {
//}

//void ts3plugin_onDelChannelEvent(uint64 serverConnectionHandlerID, uint64 channelID, anyID invokerID, const char* invokerName, const char* invokerUniqueIdentifier) {
//}

//void ts3plugin_onChannelMoveEvent(uint64 serverConnectionHandlerID, uint64 channelID, uint64 newChannelParentID, anyID invokerID, const char* invokerName, const char* invokerUniqueIdentifier) {
//}

//void ts3plugin_onUpdateChannelEvent(uint64 serverConnectionHandlerID, uint64 channelID) {
//}

//void ts3plugin_onUpdateChannelEditedEvent(uint64 serverConnectionHandlerID, uint64 channelID, anyID invokerID, const char* invokerName, const char* invokerUniqueIdentifier) {
//}

//void ts3plugin_onUpdateClientEvent(uint64 serverConnectionHandlerID, anyID clientID, anyID invokerID, const char* invokerName, const char* invokerUniqueIdentifier) {
//}

void ts3plugin_onClientMoveSubscriptionEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility) {
	if (visibility == ENTER_VISIBILITY)
	{
		helper->clientEnteredView(serverConnectionHandlerID, clientID);
	}
}

//void ts3plugin_onClientMoveMovedEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID moverID, const char* moverName, const char* moverUniqueIdentifier, const char* moveMessage) {
//}

//void ts3plugin_onClientKickFromChannelEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID kickerID, const char* kickerName, const char* kickerUniqueIdentifier, const char* kickMessage) {
//}

//void ts3plugin_onClientKickFromServerEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID kickerID, const char* kickerName, const char* kickerUniqueIdentifier, const char* kickMessage) {
//}

//void ts3plugin_onClientIDsEvent(uint64 serverConnectionHandlerID, const char* uniqueClientIdentifier, anyID clientID, const char* clientName) {
//}

//void ts3plugin_onClientIDsFinishedEvent(uint64 serverConnectionHandlerID) {
//}

//void ts3plugin_onServerEditedEvent(uint64 serverConnectionHandlerID, anyID editerID, const char* editerName, const char* editerUniqueIdentifier) {
//}

//void ts3plugin_onServerUpdatedEvent(uint64 serverConnectionHandlerID) {
//}

//void ts3plugin_onTalkStatusChangeEvent(uint64 serverConnectionHandlerID, int status, int isReceivedWhisper, anyID clientID) {
//}

//void ts3plugin_onConnectionInfoEvent(uint64 serverConnectionHandlerID, anyID clientID) {
//}

//void ts3plugin_onServerConnectionInfoEvent(uint64 serverConnectionHandlerID) {
//}

//void ts3plugin_onChannelSubscribeEvent(uint64 serverConnectionHandlerID, uint64 channelID) {
//}

//void ts3plugin_onChannelSubscribeFinishedEvent(uint64 serverConnectionHandlerID) {
//}

//void ts3plugin_onChannelUnsubscribeEvent(uint64 serverConnectionHandlerID, uint64 channelID) {
//}

//void ts3plugin_onChannelUnsubscribeFinishedEvent(uint64 serverConnectionHandlerID) {
//}

//void ts3plugin_onChannelDescriptionUpdateEvent(uint64 serverConnectionHandlerID, uint64 channelID) {
//}

//void ts3plugin_onChannelPasswordChangedEvent(uint64 serverConnectionHandlerID, uint64 channelID) {
//}

//void ts3plugin_onPlaybackShutdownCompleteEvent(uint64 serverConnectionHandlerID) {
//}

//void ts3plugin_onSoundDeviceListChangedEvent(const char* modeID, int playOrCap) {
//}

//void ts3plugin_onEditPlaybackVoiceDataEvent(uint64 serverConnectionHandlerID, anyID clientID, short* samples, int sampleCount, int channels) {
//}

//void ts3plugin_onEditPostProcessVoiceDataEvent(uint64 serverConnectionHandlerID, anyID clientID, short* samples, int sampleCount, int channels, const unsigned int* channelSpeakerArray, unsigned int* channelFillMask) {
//}

//void ts3plugin_onEditMixedPlaybackVoiceDataEvent(uint64 serverConnectionHandlerID, short* samples, int sampleCount, int channels, const unsigned int* channelSpeakerArray, unsigned int* channelFillMask) {
//}

//void ts3plugin_onEditCapturedVoiceDataEvent(uint64 serverConnectionHandlerID, short* samples, int sampleCount, int channels, int* edited) {
//}

//void ts3plugin_onCustom3dRolloffCalculationClientEvent(uint64 serverConnectionHandlerID, anyID clientID, float distance, float* volume) {
//}

//void ts3plugin_onCustom3dRolloffCalculationWaveEvent(uint64 serverConnectionHandlerID, uint64 waveHandle, float distance, float* volume) {
//}

//void ts3plugin_onUserLoggingMessageEvent(const char* logMessage, int logLevel, const char* logChannel, uint64 logID, const char* logTime, const char* completeLogString) {
//}

/* Clientlib rare */

//void ts3plugin_onClientBanFromServerEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID kickerID, const char* kickerName, const char* kickerUniqueIdentifier, uint64 time, const char* kickMessage) {
//}

//void ts3plugin_onClientSelfVariableUpdateEvent(uint64 serverConnectionHandlerID, int flag, const char* oldValue, const char* newValue) {
//}

//void ts3plugin_onFileListEvent(uint64 serverConnectionHandlerID, uint64 channelID, const char* path, const char* name, uint64 size, uint64 datetime, int type, uint64 incompletesize, const char* returnCode) {
//}

//void ts3plugin_onFileListFinishedEvent(uint64 serverConnectionHandlerID, uint64 channelID, const char* path) {
//}

//void ts3plugin_onServerGroupListEvent(uint64 serverConnectionHandlerID, uint64 serverGroupID, const char* name, int type, int iconID, int saveDB) {
//}

//void ts3plugin_onServerGroupListFinishedEvent(uint64 serverConnectionHandlerID) {
//}

//void ts3plugin_onServerGroupByClientIDEvent(uint64 serverConnectionHandlerID, const char* name, uint64 serverGroupList, uint64 clientDatabaseID) {
//}

//void ts3plugin_onServerGroupPermListEvent(uint64 serverConnectionHandlerID, uint64 serverGroupID, unsigned int permissionID, int permissionValue, int permissionNegated, int permissionSkip) {
//}

//void ts3plugin_onServerGroupPermListFinishedEvent(uint64 serverConnectionHandlerID, uint64 serverGroupID) {
//}

//void ts3plugin_onServerGroupClientListEvent(uint64 serverConnectionHandlerID, uint64 serverGroupID, uint64 clientDatabaseID, const char* clientNameIdentifier, const char* clientUniqueID) {
//}

//void ts3plugin_onChannelGroupListEvent(uint64 serverConnectionHandlerID, uint64 channelGroupID, const char* name, int type, int iconID, int saveDB) {
//}

//void ts3plugin_onChannelGroupListFinishedEvent(uint64 serverConnectionHandlerID) {
//}

//void ts3plugin_onChannelGroupPermListEvent(uint64 serverConnectionHandlerID, uint64 channelGroupID, unsigned int permissionID, int permissionValue, int permissionNegated, int permissionSkip) {
//}

//void ts3plugin_onChannelGroupPermListFinishedEvent(uint64 serverConnectionHandlerID, uint64 channelGroupID) {
//}

//void ts3plugin_onChannelPermListEvent(uint64 serverConnectionHandlerID, uint64 channelID, unsigned int permissionID, int permissionValue, int permissionNegated, int permissionSkip) {
//}

//void ts3plugin_onChannelPermListFinishedEvent(uint64 serverConnectionHandlerID, uint64 channelID) {
//}

//void ts3plugin_onClientPermListEvent(uint64 serverConnectionHandlerID, uint64 clientDatabaseID, unsigned int permissionID, int permissionValue, int permissionNegated, int permissionSkip) {
//}

//void ts3plugin_onClientPermListFinishedEvent(uint64 serverConnectionHandlerID, uint64 clientDatabaseID) {
//}

//void ts3plugin_onChannelClientPermListEvent(uint64 serverConnectionHandlerID, uint64 channelID, uint64 clientDatabaseID, unsigned int permissionID, int permissionValue, int permissionNegated, int permissionSkip) {
//}

//void ts3plugin_onChannelClientPermListFinishedEvent(uint64 serverConnectionHandlerID, uint64 channelID, uint64 clientDatabaseID) {
//}

//void ts3plugin_onClientChannelGroupChangedEvent(uint64 serverConnectionHandlerID, uint64 channelGroupID, uint64 channelID, anyID clientID, anyID invokerClientID, const char* invokerName, const char* invokerUniqueIdentity) {
//}



//void ts3plugin_onPermissionListGroupEndIDEvent(uint64 serverConnectionHandlerID, unsigned int groupEndID) {
//}

//void ts3plugin_onPermissionListEvent(uint64 serverConnectionHandlerID, unsigned int permissionID, const char* permissionName, const char* permissionDescription) {
//}

//void ts3plugin_onPermissionListFinishedEvent(uint64 serverConnectionHandlerID) {
//}

//void ts3plugin_onPermissionOverviewEvent(uint64 serverConnectionHandlerID, uint64 clientDatabaseID, uint64 channelID, int overviewType, uint64 overviewID1, uint64 overviewID2, unsigned int permissionID, int permissionValue, int permissionNegated, int permissionSkip) {
//}

//void ts3plugin_onPermissionOverviewFinishedEvent(uint64 serverConnectionHandlerID) {
//}

//void ts3plugin_onServerGroupClientAddedEvent(uint64 serverConnectionHandlerID, anyID clientID, const char* clientName, const char* clientUniqueIdentity, uint64 serverGroupID, anyID invokerClientID, const char* invokerName, const char* invokerUniqueIdentity) {
//}

//void ts3plugin_onServerGroupClientDeletedEvent(uint64 serverConnectionHandlerID, anyID clientID, const char* clientName, const char* clientUniqueIdentity, uint64 serverGroupID, anyID invokerClientID, const char* invokerName, const char* invokerUniqueIdentity) {
//}

//void ts3plugin_onClientNeededPermissionsEvent(uint64 serverConnectionHandlerID, unsigned int permissionID, int permissionValue) {
//}

//void ts3plugin_onClientNeededPermissionsFinishedEvent(uint64 serverConnectionHandlerID) {
//}

//void ts3plugin_onClientChatClosedEvent(uint64 serverConnectionHandlerID, anyID clientID, const char* clientUniqueIdentity) {
//}

//void ts3plugin_onClientChatComposingEvent(uint64 serverConnectionHandlerID, anyID clientID, const char* clientUniqueIdentity) {
//}

//void ts3plugin_onServerLogEvent(uint64 serverConnectionHandlerID, const char* logMsg) {
//}

//void ts3plugin_onServerLogFinishedEvent(uint64 serverConnectionHandlerID, uint64 lastPos, uint64 fileSize) {
//}

//void ts3plugin_onMessageListEvent(uint64 serverConnectionHandlerID, uint64 messageID, const char* fromClientUniqueIdentity, const char* subject, uint64 timestamp, int flagRead) {
//}

//void ts3plugin_onMessageGetEvent(uint64 serverConnectionHandlerID, uint64 messageID, const char* fromClientUniqueIdentity, const char* subject, const char* message, uint64 timestamp) {
//}

//void ts3plugin_onClientDBIDfromUIDEvent(uint64 serverConnectionHandlerID, const char* uniqueClientIdentifier, uint64 clientDatabaseID) {
//}

//void ts3plugin_onClientNamefromUIDEvent(uint64 serverConnectionHandlerID, const char* uniqueClientIdentifier, uint64 clientDatabaseID, const char* clientNickName) {
//}

//void ts3plugin_onClientNamefromDBIDEvent(uint64 serverConnectionHandlerID, const char* uniqueClientIdentifier, uint64 clientDatabaseID, const char* clientNickName) {
//}

//void ts3plugin_onComplainListEvent(uint64 serverConnectionHandlerID, uint64 targetClientDatabaseID, const char* targetClientNickName, uint64 fromClientDatabaseID, const char* fromClientNickName, const char* complainReason, uint64 timestamp) {
//}

//void ts3plugin_onBanListEvent(uint64 serverConnectionHandlerID, uint64 banid, const char* ip, const char* name, const char* uid, uint64 creationTime, uint64 durationTime, const char* invokerName,
//							  uint64 invokercldbid, const char* invokeruid, const char* reason, int numberOfEnforcements, const char* lastNickName) {
//}

//void ts3plugin_onClientServerQueryLoginPasswordEvent(uint64 serverConnectionHandlerID, const char* loginPassword) {
//}

//void ts3plugin_onPluginCommandEvent(uint64 serverConnectionHandlerID, const char* pluginName, const char* pluginCommand) {
//}

//void ts3plugin_onIncomingClientQueryEvent(uint64 serverConnectionHandlerID, const char* commandText) {
//}

//void ts3plugin_onServerTemporaryPasswordListEvent(uint64 serverConnectionHandlerID, const char* clientNickname, const char* uniqueClientIdentifier, const char* description, const char* password, uint64 timestampStart, uint64 timestampEnd, uint64 targetChannelID, const char* targetChannelPW) {
//}

/* Client UI callbacks */

/*
 * Called from client when an avatar image has been downloaded to or deleted from cache.
 * This callback can be called spontaneously or in response to ts3Functions.getAvatar()
 */
//void ts3plugin_onAvatarUpdated(uint64 serverConnectionHandlerID, anyID clientID, const char* avatarPath) {
//}

/* This function is called if a plugin hotkey was pressed. Omit if hotkeys are unused. */
//void ts3plugin_onHotkeyEvent(const char* keyword) {
//}

/* Called when recording a hotkey has finished after calling ts3Functions.requestHotkeyInputDialog */
//void ts3plugin_onHotkeyRecordedEvent(const char* keyword, const char* key) {
//}

// This function receives your key Identifier you send to notifyKeyEvent and should return
// the friendly device name of the device this hotkey originates from. Used for display in UI.
//const char* ts3plugin_keyDeviceName(const char* keyIdentifier) {
//	return NULL;
//}

// This function translates the given key identifier to a friendly key name for display in the UI
//const char* ts3plugin_displayKeyText(const char* keyIdentifier) {
//	return NULL;
//}

// This is used internally as a prefix for hotkeys so we can store them without collisions.
// Should be unique across plugins.
//const char* ts3plugin_keyPrefix() {
//	return NULL;
//}

