/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2018 Luch (https://github.com/Luch00)
*/
var Emotes = {
    emoteList: new Map(),
    emoteKeyList: [],
    emoteset_json: "emotesets.json",
    emote_list_element: {},
    emoteIndex: 0,
    addEmote: function (key, value) {
        if (this.emoteList.has(key)) {
            this.emoteList.get(key).element.remove();
            $('.emote-container:empty').parent().remove();
        }
        this.emoteList.set(key, value);
    },
    emoticonize: function (string) {
        var html = string.html();
        this.emoteKeyList.forEach(function(key) {
            html = html.replace(new RegExp(escapeRegExp(key)+'(?::([a-z]+):)?(?![^<]*?(?:</a>|">))', 'g'), function (a, b) {
                return `<img class="emote emote-${Emotes.emoteList.get(key).index} emote-mod-${b}" src="${Emotes.emoteList.get(key).name}" alt="${key}">`;
            });
        });
        string.html(html);
    },
    makeKeyList: function () {
        console.log("makeKeyList");
        this.emoteKeyList = Array.from(this.emoteList.keys()).sort(function(a, b) {
            return b.length - a.length;
        });
    },
    clear: function () {
        Emotes.emoteIndex = 0;
        Emotes.emoteList.clear();
        Emotes.emoteKeyList = [];
        Emotes.emote_list_element.empty();
    },
    load: function () {
        $.getJSON(this.emoteset_json, function(setlist) {
            console.log(setlist);
            setlist.forEach(function(set) {
                $.getJSON("Emotes/" + set).then(function(json) {
                    Emotes.parseJson(json);
                });
            });
        });
        /*var list = [];
        Config.REMOTE_EMOTES.forEach(function(set) {
            list.push(set);
        });
        QtObject.requestEmoteJson(list);*/
        QtObject.requestEmoteJson(Config.REMOTE_EMOTES);
    },
    addRemoteEmote: function (jsonString) {
        Emotes.parseJson(JSON.parse(jsonString));
    },
    parseJson: function(json) {
        var set_element = $('<div>', {
            class: 'emoteset',
            'data-name': json.setname
        });
        set_element.append('<div class="set-header">' + json.setname + '</div>');
        var emote_container = $('<div>', {
            class: 'emote-container'
        });
        set_element.append(emote_container);
        json.emoticons.forEach(function(emote) {
            var e = { 
                name: `${json.pathbase}${emote.name}${json.pathappend}`,
                index: Emotes.emoteIndex 
            }
            Emotes.emoteIndex++;
            var emote_img = $('<img >', {
                class: 'emote',
                src: e.name,
                alt: emote.code,
                'data-key': emote.code
            })
            .click(function(e) {
                emoteClicked($(this).data('key'), e.shiftKey);
            });
            emote_container.append(emote_img);
            e.element = emote_img;
            Emotes.addEmote(emote.code, e);
        });
        Emotes.makeKeyList();
        this.emote_list_element.append(set_element);
    }
}