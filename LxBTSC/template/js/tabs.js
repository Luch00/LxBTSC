/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2018 Luch (https://github.com/Luch00)
*/
'use strict'
let serverMap = new Map();

function AddServerTabs(serverId, dontshow) {
    //console.log("AddServerTabs: "+serverId);
    if (!serverMap.has(serverId)) {
        let tabs = new Map();
        tabs.set(3, CreateTab());
        tabs.set(2, CreateTab());
        tabs.set(1, new Map());
        serverMap.set(serverId, tabs);
        //console.log(serverMap);
        main.append(tabs.get(3), tabs.get(2));
        if (!dontshow) {
            ShowTab(serverId, 3, "");
        }
    }
}

function GetTab(server, mode, client) {
    //console.log("GetTab: "+server+" mode: "+mode+" client: "+client);
    let tabs = serverMap.get(server);
    if (!tabs) {
        //console.log("server not found");
        AddServerTabs(server, true);
        tabs = serverMap.get(server);
    }
    if (mode === 1) {
        let privateTab = tabs.get(1).get(client);
        if (!privateTab) {
            privateTab = CreateTab();
            main.append(privateTab);
            tabs.get(1).set(client, privateTab);
        }
        return privateTab;
    }
    else {
        //console.log(tabs);
        return tabs.get(mode);
    }
}

function ShowTab(target, mode, client) {
    //console.log("ShowTab: "+target+" mode: "+mode+" client: "+client);
    hideTooltip();
    for (let server of serverMap.values()) {
        server.get(3).hide();
        server.get(2).hide();
        for (let privateTab of server.get(1).values()) {
            privateTab.hide();
        }
    }
    let tab = GetTab(target, mode, client);
    //console.log(tab);
    tab.show();
    window.scroll(0, document.body.scrollHeight);
}

function CreateTab() {
    return $('<div/>', { class: 'chattab'} );
}
