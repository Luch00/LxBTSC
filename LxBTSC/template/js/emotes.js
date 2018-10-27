/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2018 Luch (https://github.com/Luch00)
*/ 
'use strict';
let Emotes = {
    emoteList: new Map(),
    emoteset_json: "emotesets.json",
    emote_list_element: {},
    emoteIndex: 0,
    fullRegex: undefined,
    addEmote: function (key, value) {
        if (this.emoteList.has(key)) {
            this.emoteList.get(key).element.remove();
            $('.emote-container:empty').parent().remove();
        }
        this.emoteList.set(key, value);
    },
    emoticonize: function (string) {
        let html = string.html();
        html = html.replace(this.fullRegex, function (a, b, c) {
            let e = Emotes.emoteList.get(b);
            return `<img class="emote emote-${e.index} emote-mod-${c}" src="${e.name}" alt="${e.code}">`;
        });
        string.html(html);
    },
    buildRegex: function () {
        let emoteKeyList = Array.from(this.emoteList.keys()).sort(function (a, b) {
            return b.length - a.length;
        });
        var stringlist = Emotes.escapeRegExp(emoteKeyList.join('|'));
        Emotes.fullRegex = new RegExp('('+stringlist+')(?::([a-z0-9]+):)?(?![^<]*?(?:</a>|">))', 'g');
    },
    clear: function () {
        Emotes.emoteIndex = 0;
        Emotes.emoteList.clear();
        Emotes.fullRegex = "";
        Emotes.emote_list_element.empty();
    },
    load: function () {
        $.getJSON(this.emoteset_json, function (setlist) {
            setlist.forEach(function (set) {
                $.getJSON("Emotes/" + set).then(function (json) {
                    if (Array.isArray(json)) {
                        json.forEach(function (item) {
                            Emotes.parseJson(item);
                        });
                    }
                    else {
                        Emotes.parseJson(json);
                    }
                });
            });
        });
        if (Config.REMOTE_EMOTES.length > 0) {
            QtObject.requestEmoteJson(Config.REMOTE_EMOTES);
        }
    },
    addRemoteEmote: function (jsonString) {
        let json = JSON.parseJson(jsonString);
        if (Array.isArray(json)) {
            json.forEach(function (item) {
                Emotes.parseJson(item);
            });
        }
        else {
            Emotes.parseJson(json);
        }
    },
    parseJson: function (json) {
        let set_element = $('<div>', {
            class: 'emoteset',
            'data-name': json.setname
        });
        set_element.append('<div class="set-header">' + json.setname + '</div>');
        let emote_container = $('<div>', {
            class: 'emote-container'
        });
        set_element.append(emote_container);
        json.emoticons.forEach(function (emote) {
            let e = {
                name: `${json.pathbase}${emote.name}${json.pathappend}`,
                code: emote.code,
                index: Emotes.emoteIndex
            };
            Emotes.emoteIndex++;
            let emote_img = $('<img >', {
                class: 'emote',
                src: e.name,
                alt: emote.code,
                'data-key': emote.code
            })
            .click(function (e) {
                emoteClicked($(this).data('key'), e.shiftKey);
            });
            emote_container.append(emote_img);
            e.element = emote_img;
            Emotes.addEmote(emote.code, e);
        });
        Emotes.buildRegex();
        this.emote_list_element.append(set_element);
    },
    escapeRegExp: function (str) {
        return str.replace(/[\-\[\]\/\{\}\(\)\*\+\?\.\\\^\$]/g, "\\$&");
    }
};
