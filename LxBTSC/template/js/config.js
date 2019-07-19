/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2019 Luch (https://github.com/Luch00)
*/
var Config = {
    MAX_LINES: 500,
    MAX_HISTORY: 50,
    EMBED_ENABLED: true,
    GENERICS_DISABLED : false,
    FAVICONS_ENABLED: false,
    EMOTICONS_ENABLED: true,
    AVATARS_ENABLED: false,
    HOVER_ANIMATES_GIFS: false,
    HISTORY_ENABLED: true,
    DOWNLOAD_DIR: "",
    REMOTE_EMOTES: [],
    FONT_SIZE: 12
};

function loadConfig() {
    return new Promise((resolve, reject) => {
        $.getJSON("config.json", function(data) {
            Object.keys(data).forEach((key) => {
                Config[key] = data[key];
            });
            resolve();
        })
        .fail(function() {
            resolve();
        });
    });
}