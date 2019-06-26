/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2019 Luch (https://github.com/Luch00)
*/ 
'use strict';
let Emotes = {
    emoteList: new Map(),
    emotesetJson: "emotesets.json",
    emoteListElement: {},
    emoteIndex: 0,
    fullRegex: undefined,
    addEmote(key, value) {
        if (this.emoteList.has(key)) {
            this.emoteList.get(key).element.remove();
            $('.emote-container:empty').parent().remove();
        }
        this.emoteList.set(key, value);
    },
    emoticonize(string) {
        let html = string.html();
        html = html.replace(this.fullRegex, function (a, b, c) {
            let e = Emotes.emoteList.get(b);
            return `<img class="emote emote-${e.index} emote-mod-${c}" src="${e.name}" alt="${e.code}">`;
        });
        string.html(html);
    },
    buildRegex() {
        let emoteKeyList = Array.from(this.emoteList.keys()).sort(function (a, b) {
            return b.length - a.length;
        });
        let stringlist = Emotes.escapeRegExp(emoteKeyList.join('|'));
        Emotes.fullRegex = new RegExp('('+stringlist+')(?::([a-z0-9]+):)?(?![^<]*?(?:</a>|">))', 'g');
    },
    clear() {
        Emotes.emoteIndex = 0;
        Emotes.emoteList.clear();
        Emotes.fullRegex = "";
        Emotes.emoteListElement.empty();
    },
    async load() {
        let setarray;
        try {
            setarray = await this.getJson(this.emotesetJson);
        }
        catch (error) {
            console.error('Failed to load emotesets_json');
            return;
        }
        setarray.forEach((value, index) => setarray[index] = 'Emotes/' + value);
        setarray.push.apply(setarray, Config.REMOTE_EMOTES);
        console.info(setarray);
        for (let item of setarray) {
            let set;
            try {
                set = await this.getJson(item);
            }
            catch (error) {
                console.error('Failed to load emotes: '+ item);
                continue;
            }

            if (Array.isArray(set)) {
                set.forEach(set => this.parseJson(set));
            }
            else {
                this.parseJson(set);
            }
        }
    },
    getJson(url) {
        return new Promise(function(resolve, reject) {
            console.log(url);
            let xhr = new XMLHttpRequest();
            xhr.responseType = 'json';
            xhr.open('GET', url);
            xhr.onload = function() {
                resolve(xhr.response);
            };
            xhr.onerror = function(e) {
                reject(e);
            };
            xhr.send();
        });
    },
    parseJson(json) {
        let setElement = $('<div>', {
            class: 'emoteset',
            'data-name': json.setname
        });
        setElement.append('<div class="set-header">' + json.setname + '</div>');
        let emote_container = $('<div>', {
            class: 'emote-container'
        });
        setElement.append(emote_container);
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
            });
            emote_container.append(emote_img);
            e.element = emote_img;
            Emotes.addEmote(emote.code, e);
        });
        Emotes.buildRegex();
        this.emoteListElement.append(setElement);
    },
    escapeRegExp(str) {
        return str.replace(/[\-\[\]\/\{\}\(\)\*\+\?\.\\\^\$]/g, "\\$&");
    }
};