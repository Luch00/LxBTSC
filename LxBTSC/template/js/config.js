/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2018 Luch (https://github.com/Luch00)
*/
var Config = {};

function loadConfig() {
    return new Promise((resolve, reject) => {
        $.getJSON("config.json", function(data) {
            Config = data;
            resolve();
        })
        .fail(function() {
            Config.MAX_LINES = 500;
            Config.EMBED_ENABLED = true;
            Config.GENERICS_DISABLED = false;
            Config.FAVICONS_ENABLED = false;
            Config.EMOTICONS_ENABLED = true;
            Config.AVATARS_ENABLED = false;
            Config.HOVER_ANIMATES_GIFS = false;
            Config.DOWNLOAD_DIR = "";
            Config.REMOTE_EMOTES = [];
            resolve();
        });
    });
}