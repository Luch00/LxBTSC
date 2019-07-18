/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2019 Luch (https://github.com/Luch00)
*/
'use strict'
let msgid = 0;
const normalTextTemplate = (msgid, direction, time, userlink, name, text) => `
    <p id='${msgid}' class='TextMessage_Normal'>
    <span class='Body'>
    <img class='${direction}'>
    <span class='TextMessage_Time'><${time}> </span>
    <span class='TextMessage_UserLink'><a href='${userlink}' class='TextMessage_UserLink' oncontextmenu='ts3LinkClicked(event)'>"${name}"</a></span>: 
    <span class='TextMessage_Text'>${text}</span>
    </span>
    </p>
`;

const avatarStyle_normalTextTemplate = (msgid, direction, time, userlink, name, text, target, client) => `
    <div id='${msgid}' class='avatar-style TextMessage_Normal'>
    <div class='Body animate-avatar'>
    <div class='avatar-container'>
    ${Config.HOVER_ANIMATES_GIFS ? 
        `<img class='avatar hidden-image fancybox' src='../../../cache/${target}/clients/avatar_${client}?timestamp=${new Date().getTime()}' onload='thumbnailAvatar(this)' onerror='defaultAvatar(this)'>`: 
        `<img class='avatar fancybox' src='../../../cache/${target}/clients/avatar_${client}?timestamp=${new Date().getTime()}' onerror='defaultAvatar(this);'>`}
    </div>
    <div class='message-container'>
        <div class='message-header'>
            <span class='TextMessage_UserLink'><a href='${userlink}' class='TextMessage_UserLink ${direction}' oncontextmenu='ts3LinkClicked(event)'>${name}</a></span>
            <span class='avatar-style TextMessage_Time'>${time} </span>
        </div>
        <div class='message-content'>
        <span class='avatar-style TextMessage_Text'>${text}</span>
        </div>
    </div>
    </div>
    </div>
`;

const statusTextTemplate = (msgid, type, time, text) => Config.AVATARS_ENABLED ? 
`
    <p id='${msgid}' class='avatar-style-status ${type}'>
    <span class='avatar-style TextMessage_Text'>${text}</span>
    <span class='avatar-style TextMessage_Time'>${time}</span>
    </p>
`:
`
    <p id='${msgid}' class='${type}'>
    <img class='InfoMessage'>
    <span class='TextMessage_Time'><${time}> </span>
    <span class='TextMessage_Text'>${text}</span>
    </p>
`;

const pokeTextTemplate = (msgid, time, link, name, text) => Config.AVATARS_ENABLED ?
`
    <div id='${msgid}' class='TextMessage_Poke'>
    <div class='Body'>
    <div class='message-container'>
        <div class='message-header'>
        <span class='TextMessage_UserLink'><a href='${link}' class='TextMessage_UserLink' oncontextmenu='ts3LinkClicked(event)'>${name}</a></span>
        <span class='avatar-style TextMessage_Time'>${time}</span>
        </div>
        <div class='message-content'>
        <span class='avatar-style TextMessage_Text'>Pokes you: ${text}</span>
        </div>
    </div>
    </div>
    </div>
`:
`
    <p id='${msgid}' class="TextMessage_Poke">
    <span class='Body'>
    <img class='Incoming'>
    <span class='TextMessage_Time'><${time}> </span>
    <span class='TextMessage_UserLink'><a href='${link}' class='TextMessage_UserLink' oncontextmenu='ts3LinkClicked(event)'>"${name}"</a></span>
    <span class='TextMessage_Text'>pokes you: ${text}</span>
    </span>
    </p>
`;

function defaultAvatar(img) {
    img.onerror=null;
    img.classList.remove("hidden-image");
    img.classList.remove("fancybox");
    img.classList.add("default-avatar");
    img.src="";
}

function thumbnailAvatar(img) {
    let still = $('<img/>', { class: 'static-avatar'});
    let canvas = document.createElement('canvas');
    canvas.width = img.naturalWidth;
    canvas.height = img.naturalHeight;
    canvas.getContext('2d').drawImage(img, 0, 0);
    still[0].src = canvas.toDataURL('image/png');
    still.insertBefore(img);
}

function checkMessageLimit(tab) {
    let over = tab.children().length - Config.MAX_LINES;
    if(over > 0) {
        tab.children().slice(0, over).remove();
    }
}

function parseBBCode(line) {
    let result = XBBCODE.process({
        text: line
    });
    return result.html;
}

function addTextMessage(target, direction, time, name, userlink, line, mode, client, receiver) {
    //console.log(target);
    ++msgid;
    let parsed = $('<span/>').html(parseBBCode(line));

    if (Config.EMOTICONS_ENABLED) {
        Emotes.emoticonize(parsed);
    }
    if (Config.FAVICONS_ENABLED) {
        getFavicons(parsed);
    }
    
    let tab = getTab(target, mode, direction === "Outgoing" ? receiver : client);
    checkMessageLimit(tab);

    Config.AVATARS_ENABLED ? 
        tab.append(avatarStyle_normalTextTemplate(msgid, direction, time, userlink, name, parsed.get(0).outerHTML, target, client)) :
        tab.append(normalTextTemplate(msgid, direction, time, userlink, name, parsed.get(0).outerHTML));
    
    if (Config.EMBED_ENABLED) {
        embed(msgid, parsed);
    }

    if (isBottom) {
        window.scroll(0, document.body.scrollHeight);
    }
}

function addStatusMessage(target, line) {
    let tab = getTab(target, 3, "");
    checkMessageLimit(tab);
    tab.append(line);

    if (isBottom) {
        window.scroll(0, document.body.scrollHeight);
    }
}

function ts3ClientPoked(target, time, link, name, message) {
    ++msgid;

    var parsed = parseBBCode(message);
    let tab = getTab(target, 3, "");
    checkMessageLimit(tab);
    tab.append(pokeTextTemplate(msgid, time, link, name, parsed));

    if (isBottom) {
        window.scroll(0, document.body.scrollHeight);
    }
}

function addConsoleMessage(target, mode, client, message) {
    ++msgid;

    let tab = getTab(target, mode, client);
    checkMessageLimit(tab);
    tab.append('<p class="TextMessage_Console">'+parseBBCode(message)+'</p>');
    
    if (isBottom) {
        window.scroll(0, document.body.scrollHeight);
    }
}

function ts3ServerWelcome(target, time, message) {
    ++msgid;
    addStatusMessage(target, statusTextTemplate(msgid, "TextMessage_Welcome", time, parseBBCode(message)));
}

function ts3ServerConnected(target, time, servername) {
    var text;
    if (servername.length > 0) {
        text = 'Connected to Server: <b><a href="channelid://0" class="TextMessage_ServerLink" oncontextmenu="ts3LinkClicked(event)">'+servername+'</a></b>';
    }
    else {
        text = "Connected";
    }
    ++msgid;
    addStatusMessage(target, statusTextTemplate(msgid, "TextMessage_Connected", time, text));
}

function ts3ServerDisconnected(target, time) {
    ++msgid;
    addStatusMessage(target, statusTextTemplate(msgid, "TextMessage_Disconnected", time, "Disconnected"));
}

function ts3ServerStopped(target, time, message) {
    ++msgid;
    addStatusMessage(target, statusTextTemplate(msgid, "TextMessage_ServerError", time, "Server Shutdown: "+message));
}

function ts3ServerConnectionLost(target, time) {
    ++msgid;
    addStatusMessage(target, statusTextTemplate(msgid, "TextMessage_Disconnected", time, "Connection to server lost"));
}

function ts3ClientConnected(target, time, link, name) {
    ++msgid;
    addStatusMessage(target, statusTextTemplate(msgid, "TextMessage_ClientConnected", time, '<a href="'+link+'" class="TextMessage_UserLink" oncontextmenu="ts3LinkClicked(event)">"'+name+'"</a> connected'));
}

function ts3ClientDisconnected(target, time, link, name, message) {
    ++msgid;
    addStatusMessage(target, statusTextTemplate(msgid, "TextMessage_ClientDisconnected", time, '<a href="'+link+'" class="TextMessage_UserLink" oncontextmenu="ts3LinkClicked(event)">"'+name+'"</a> disconnected ('+message+')'));
}

function ts3ClientTimeout(target, time, link, name) {
    ++msgid;
    addStatusMessage(target, statusTextTemplate(msgid, "TextMessage_ClientDropped", time, '<a href="'+link+'" class="TextMessage_UserLink" oncontextmenu="ts3LinkClicked(event)">"'+name+'"</a> timed out'));
}

function ts3ClientKickedFromChannel(target, time, link, name, kickerlink, kickername, message) {
    ++msgid;
    let text;
    if (link)
        text = `<a href="${link}" class="TextMessage_UserLink" oncontextmenu="ts3LinkClicked(event)">"${name}"</a> was kicked from a channel by <a href="${kickerlink}" class="TextMessage_UserLink" oncontextmenu="ts3LinkClicked(event)">"${kickername}"</a> (${message})`;
    else
        text = `You were kicked from the channel by <a href="${kickerlink}" class="TextMessage_UserLink" oncontextmenu="ts3LinkClicked(event)">"${kickername}"</a> (${message})`;
    addStatusMessage(target, statusTextTemplate(msgid, "TextMessage_ClientKicked", time, text));
}

function ts3ClientKickedFromServer(target, time, link, name, kickerlink, kickername, message) {
    ++msgid;
    let text;
    if (link)
        text = `<a href="${link}" class="TextMessage_UserLink" oncontextmenu="ts3LinkClicked(event)">"${name}"</a> was kicked from the server by <a href="${kickerlink}" class="TextMessage_UserLink" oncontextmenu="ts3LinkClicked(event)">"${kickername}"</a> (${message})`;
    else
        text = `You were kicked from the server by <a href="${kickerlink}" class="TextMessage_UserLink" oncontextmenu="ts3LinkClicked(event)">"${kickername}"</a> (${message})`;
    addStatusMessage(target, statusTextTemplate(msgid, "TextMessage_ClientKicked", time, text));
}

function ts3ClientBannedFromServer(target, time, link, name, kickerlink, kickername, message) {
    ++msgid;
    let text;
    if (link)
        text = `<a href="${link}" class="TextMessage_UserLink" oncontextmenu="ts3LinkClicked(event)">"${name}"</a> was banned from the server by <a href="${kickerlink}" class="TextMessage_UserLink" oncontextmenu="ts3LinkClicked(event)">"${kickername}"</a> (${message})`;
    else
        text = `You were banned from the server by <a href="${kickerlink}" class="TextMessage_UserLink" oncontextmenu="ts3LinkClicked(event)">"${kickername}"</a> (${message})`;
    addStatusMessage(target, statusTextTemplate(msgid, "TextMessage_ClientBanned", time, text));
}

function ts3LogRead(target, log) {
    console.log(target);
    console.log(log);
    let json = JSON.parse(log);
    
    if (json.server.length > 0) {
        let tab = getTab(target, 3, "");
        appendLog(target, tab, json.server);
    }
    if (json.channel.length > 0) {
        let tab = getTab(target, 2, "");
        appendLog(target, tab, json.channel);
    }
}

function ts3PrivateLogRead(target, client, log) {
    let json = JSON.parse(log);

    if (json.private.length > 0) {
        let tab = getTab(target, 1, client);
        appendLog(target, tab, json.private);
    }
}

function appendLog(target, tab, log) {
    let i = Math.max(log.length - Config.MAX_HISTORY, 0);
    let html = "";
    for (; i < log.length; ++i) {
        html += Config.AVATARS_ENABLED ? 
            avatarStyle_normalTextTemplate(msgid, "", log[i].time, log[i].link, log[i].name, log[i].text, target, log[i].uid) :
            normalTextTemplate(msgid, "InfoMessage", log[i].time, log[i].link, log[i].name, log[i].text);
            
        ++msgid;
    }
    html += '<div class="history-divider"><span>End History</span></div>';
    tab[0].insertAdjacentHTML('afterbegin', html);
}