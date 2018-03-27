'use strict'
let tabMap = new Map();

function AddServerTabs(serverId) {
    if (!tabMap.has('tab-'+serverId+'-server')) {
        let tab1 = 'tab-'+serverId+'-server';        
        let tab2 = 'tab-'+serverId+'-channel';
        let server = $('<div/>', {
            id: tab1,
            class: 'chattab'
        });
        let channel = $('<div/>', {
            id: tab2,
            class: 'chattab'
        });
        tabMap.set(tab1, server);
        tabMap.set(tab2, channel);
        main.append(server, channel);
        ShowTab(tab1);
    }
}

function ShowTab(target) {
    hideTooltip();
    CreateTabIfNotExist(target);
    for (let value of tabMap.values()) {
        value.hide();
    }
    tabMap.get(target).show();
    window.scroll(0, document.body.scrollHeight);
}

function CreateTabIfNotExist(target) {
    if (!tabMap.has(target)) {
        let tab = $('<div/>', {
            id: target,
            class: 'chattab'
        });
        tabMap.set(target, tab);
        main.append(tab);
    }
}