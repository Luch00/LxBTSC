var Emotes = {
    emoteList: {},
    emoteKeyList: [],
    emoteset_json: "emotesets.json",
    emote_list_element: {},
    addEmote: function (key, value) {
        if (!this.emoteList.hasOwnProperty(key)) {
            //console.log("ADDED: " + key);
            this.emoteList[key] = value;
            return true;
        }
        //console.log("NOT ADDED: " + key);
        return false;
    },
    emoticonize: function (string) {
        var html = string.html();
        this.emoteKeyList.forEach(function(key) {
            html = html.replace(new RegExp(escapeRegExp(key)+'(?![^<]*?(?:</a>|">))', 'g'), 
                '<img class="emote" src="'+Emotes.emoteList[key].name+'" alt="'+key+'">');
        });
        string.html(html);
    },
    makeKeyList: function () {
        this.emoteKeyList = Object.keys(this.emoteList).sort(function(a, b) {
            return b.length - a.length;
        });
    },
    clear: function () {
        Emotes.emoteList = {};
        Emotes.emoteKeyList = [];
        Emotes.emote_list_element.empty();
    },
    load: function () {
        return $.getJSON(this.emoteset_json).then(function(setlist) {
            if (Config.REMOTE_EMOTES.length != 0) {
                $.merge(setlist, Config.REMOTE_EMOTES);
            }
            setlist.forEach(function(set, index, array) {
                Emotes.getSet(set).then(function() {
                    if (index === array.length -1) {
                        Emotes.makeKeyList();
                    }
                });
            });
        });
    },
    getSet: function(set) {
        var setPath;
        if (set.startsWith("http")) {
            setPath = set;
        }
        else {
            setPath = "Emotes/" + set;
        }
        return $.getJSON(setPath).then(function(data) {
            Emotes.parseJson(data);
        });
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
            var e = { name: `${json.pathbase}${emote.name}${json.pathappend}` }
            if (Emotes.addEmote(emote.code, e)) {
                var emote_img = $('<img >', {
                    class: 'emote',
                    src: e.name,
                    alt: emote.code,
                    'data-key': emote.code
                }).click(function(e) {
                    emoteClicked($(this).data('key'), e.shiftKey);
                });
                emote_container.append(emote_img);
            }
        });
        this.emote_list_element.append(set_element);
    }
}