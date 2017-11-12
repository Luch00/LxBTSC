var Emotes = {
    emoteList: {},
    emoteKeyList: [],
    emoteset_json: "emotesets.json",
    emote_list_element: {},
    addEmote: function (key, value) {
        if (!this.emoteList.hasOwnProperty(key)) {
            //console.log("ADDED: " + key);
            this.emoteList[key] = value;
        }
    },
    emoticonize: function (string) {
        this.emoteKeyList.forEach(function(key) {
            string = string.replace(new RegExp('(?!<[^>]*?>)('+escapeRegExp(key)+')(?![^<]*?(</a>|">))', 'g'), 
                '<img class="emote" src="'+Emotes.emoteList[key].name+'" alt="'+key+'">');
        });
        return string;
    },
    makeKeyList: function () {
        this.emoteKeyList = Object.keys(this.emoteList).sort(function(a, b) {
            return b.length - a.length;
        });
    },
    load: function () {
        return new Promise((resolve, reject) => {
            $.getJSON(this.emoteset_json, function(setlist) {
                setlist.forEach(function(set) {
                    Emotes.getSet(set);
                }), resolve();
            });
        });
    },
    getSet: function(set) {
        $.getJSON("Emotes/" + set, function(data) {
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
            Emotes.addEmote(emote.code, e);
            
            var emote_img = $('<img >', {
                class: 'emote',
                src: e.name,
                alt: emote.code,
                'data-key': emote.code
            }).click(function(e) {
                emoteClicked($(this).data('key'));
            });
            emote_container.append(emote_img);
        });
        this.emote_list_element.append(set_element);
    }
}