'use strict'
let msgid = 0;
const NormalTextTemplate = (msgid, direction, time, userlink, name, text) => `
    <p id='${msgid}' class='TextMessage_Normal'>
    <span class='Body'>
    <img class='${direction}'>
    <span class='TextMessage_Time'><${time}> </span>
    <span class='TextMessage_UserLink'><a href='${userlink}' class='TextMessage_UserLink' oncontextmenu='Ts3LinkClicked(event)'>"${name}"</a></span>: 
    <span class='TextMessage_Text'>${text}</span>
    </span>
    </p>
`;

const AvatarStyle_NormalTextTemplate = (msgid, direction, time, userlink, name, text, target, client) => `
    <div id='${msgid}' class='avatar-style TextMessage_Normal'>
    <div class='Body'>
    <div class='avatar-container'>
    <img class='avatar' src='../../../cache/${target}/clients/avatar_${client}?timestamp=${new Date().getTime()}' onerror='this.onerror=null;this.src="style/avatar1.png";'>
    </div>
    <div class='message-container'>
        <div class='message-header'>
            <span class='TextMessage_UserLink'><a href='${userlink}' class='TextMessage_UserLink ${direction}' oncontextmenu='Ts3LinkClicked(event)'>${name}</a></span>
            <span class='avatar-style TextMessage_Time'>${time} </span>
        </div>
        <div class='message-content'>
        <span class='avatar-style TextMessage_Text'>${text}</span>
        </div>
    </div>
    </div>
    </div>
`;

/*const AvatarStyle_StatusTextTemplate = (msgid, type, time, text) => `
    <p id='${msgid}' class='message-containter ${type}'>
    <span class='TextMessage_Text'>${text}</span>
    <span class='avatar-style TextMessage_Time'>${time}</span>
    </p>
`;*/

const StatusTextTemplate = (msgid, type, time, text) => `
    <p id='${msgid}' class='${type}'>
    <img class='Incoming'>
    <span class='TextMessage_Time'><${time}> </span>
    <span class='TextMessage_Text'>${text}</span>
    </p>
`;

const PokeTextTemplate = (msgid, time, link, name, text) => `
    <p id='${msgid}' class="TextMessage_Poke">
    <span class='Body'>
    <img class='Incoming'>
    <span class='TextMessage_Time'><${time}> </span>
    <span class='TextMessage_UserLink'><a href='${link}' class='TextMessage_UserLink' oncontextmenu='Ts3LinkClicked(event)'>"${name}"</a></span>
    <span class='TextMessage_Text'>pokes you: ${text}</span>
    </span>
    </p>
`;

function CheckMessageLimit(tab) {
    if (tab.childElementCount > Config.MAX_LINES) {
        tab.firstElementChild.remove();
    }
}

function ParseBBCode(line) {
    let result = XBBCODE.process({
        text: line
    });
    return result.html;
}

function AddTextMessage(target, direction, time, name, userlink, line, mode, client, receiver) {
    //console.log(target);
    ++msgid;
    let parsed = $('<span/>').html(ParseBBCode(line));

    if (Config.EMOTICONS_ENABLED) {
        Emotes.emoticonize(parsed);
    }
    if (Config.FAVICONS_ENABLED) {
        GetFavicons(parsed);
    }
    
    //tabMap.get(target).append(NormalTextTemplate(msgid, direction, time, userlink, name, parsed.get(0).outerHTML));
    let tab = GetTab(target, mode, (direction == "Outgoing") ? receiver : client);
    CheckMessageLimit(tab);

    Config.AVATARS_ENABLED ? 
        tab.append(AvatarStyle_NormalTextTemplate(msgid, direction, time, userlink, name, parsed.get(0).outerHTML, target, client)) :
        tab.append(NormalTextTemplate(msgid, direction, time, userlink, name, parsed.get(0).outerHTML));
    
    if (Config.EMBED_ENABLED) {
        Embed(msgid, parsed);
    }

    if (IsBottom) {
        window.scroll(0, document.body.scrollHeight);
    }
}

function AddStatusMessage(target, line) {
    //console.log("status: "+target+" mesg:"+line);

    //tabMap.get(target).append(line);
    let tab = GetTab(target, 3, "");//.append(line);
    CheckMessageLimit(tab);
    tab.append(line);

    if (IsBottom) {
        window.scroll(0, document.body.scrollHeight);
    }
}

function Ts3ClientPoked(target, time, link, name, message) {
    ++msgid;

    var parsed = ParseBBCode(message);
    let tab = GetTab(target, 3, "");
    CheckMessageLimit(tab);
    tab.append(PokeMessageTemplate(msgid, time, link, name, parsed));

    if (IsBottom) {
        window.scroll(0, document.body.scrollHeight);
    }
}

function AddConsoleMessage(target, message) {
    ++msgid;

    let tab = GetTab(target, 3, "");
    CheckMessageLimit(tab);
    tab.append('<p class="TextMessage_Console">'+ParseBBCode(message)+'</p>');
    
    if (IsBottom) {
        window.scroll(0, document.body.scrollHeight);
    }
}

function Ts3ServerWelcome(target, time, message) {
    ++msgid;
    AddStatusMessage(target, StatusTextTemplate(msgid, "TextMessage_Welcome", time, ParseBBCode(message)));
}

function Ts3ServerConnected(target, time, servername) {
    var text;
    if (servername.length > 0) {
        text = 'Connected to Server: <b><a href="channelid://0" class="TextMessage_ServerLink" oncontextmenu="Ts3LinkClicked(event)">'+servername+'</a></b>';
    }
    else {
        text = "Connected";
    }
    ++msgid;
    AddStatusMessage(target, StatusTextTemplate(msgid, "TextMessage_Connected", time, text))
}

function Ts3ServerDisconnected(target, time) {
    ++msgid;
    AddStatusMessage(target, StatusTextTemplate(msgid, "TextMessage_Disconnected", time, "Disconnected"));
}

function Ts3ServerStopped(target, time, message) {
    ++msgid;
    AddStatusMessage(target, StatusTextTemplate(msgid, "TextMessage_ServerError", time, "Server Shutdown: "+message));
}

function Ts3ServerConnectionLost(target, time) {
    ++msgid;
    AddStatusMessage(target, StatusTextTemplate(msgid, "TextMessage_Disconnected", time, "Connection to server lost"))
}

function Ts3ClientConnected(target, time, link, name) {
    ++msgid;
    AddStatusMessage(target, StatusTextTemplate(msgid, "TextMessage_ClientConnected", time, '<a href="'+link+'" class="TextMessage_UserLink" oncontextmenu="Ts3LinkClicked(event)">"'+name+'"</a> connected'));
}

function Ts3ClientDisconnected(target, time, link, name, message) {
    ++msgid;
    AddStatusMessage(target, StatusTextTemplate(msgid, "TextMessage_ClientDisconnected", time, '<a href="'+link+'" class="TextMessage_UserLink" oncontextmenu="Ts3LinkClicked(event)">"'+name+'"</a> disconnected ('+message+')'));
}

function Ts3ClientTimeout(target, time, link, name) {
    ++msgid;
    AddStatusMessage(target, StatusTextTemplate(msgid, "TextMessage_ClientDropped", time, '<a href="'+link+'" class="TextMessage_UserLink" oncontextmenu="Ts3LinkClicked(event)">"'+name+'"</a> timed out'));
}