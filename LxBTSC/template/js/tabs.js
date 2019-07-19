/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2019 Luch (https://github.com/Luch00)
*/
'use strict'
let serverMap = new Map();
let messageLimitObserver = new MutationObserver((mutations) => {
    mutations.forEach((mutation) => {
        if (mutation.addedNodes.length > 0) {
            let over = mutation.target.childElementCount - Config.MAX_LINES;
            if(over > 0) {
                $(mutation.target).children().slice(0, over).remove();
            }
        }
    });
});

function addServerTabs(serverId, dontshow) {
    if (!serverMap.has(serverId)) {
        let tabs = new Map();
        tabs.set(3, createTab());
        tabs.set(2, createTab());
        tabs.set(1, new Map());
        serverMap.set(serverId, tabs);
        main.append(tabs.get(3), tabs.get(2));
        if (!dontshow) {
            showTab(serverId, 3, "");
        }
    }
}

function getTab(server, mode, client) {
    let tabs = serverMap.get(server);
    if (!tabs) {
        addServerTabs(server, true);
        tabs = serverMap.get(server);
    }
    if (mode === 1) {
        let privateTab = tabs.get(1).get(client);
        if (!privateTab) {
            privateTab = createTab();
            main.append(privateTab);
            tabs.get(1).set(client, privateTab);
        }
        return privateTab;
    }
    else {
        return tabs.get(mode);
    }
}

function showTab(target, mode, client) {
    hideTooltip();
    for (let server of serverMap.values()) {
        server.get(3).hide();
        server.get(2).hide();
        for (let privateTab of server.get(1).values()) {
            privateTab.hide();
        }
    }
    let tab = getTab(target, mode, client);
    tab.show();
    window.scroll(0, document.body.scrollHeight);
}

function createTab() {
    let tab = $('<div/>', { class: 'chattab', style: `font-size: ${Config.FONT_SIZE ? Config.FONT_SIZE : 12}pt;`} );
    messageLimitObserver.observe(tab[0], { childList: true });
    return tab;
    //return $('<div/>', { class: 'chattab', style: `font-size: ${Config.FONT_SIZE ? Config.FONT_SIZE : 12}pt;`} );
}
