var Emotes = {
    emoteList: {},
    emoteKeyList: [],
    emoteset_json: "emotesets.json",
    emote_list_element: {},
    retryID: 0,
    addEmote: function (key, value) {
        if (this.emoteList.hasOwnProperty(key)) {
            this.emoteList[key].element.remove();
            $('.emote-container:empty').parent().remove();
        }
        this.emoteList[key] = value;
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
        console.log("makeKeyList");
        this.emoteKeyList = Object.keys(this.emoteList).sort(function(a, b) {
            return b.length - a.length;
        });
    },
    clear: function () {
        window.clearTimeout(Emotes.retryID);
        Emotes.emoteList = {};
        Emotes.emoteKeyList = [];
        Emotes.emote_list_element.empty();
    },
    load: function () {
        $.getJSON(this.emoteset_json, function (setlist) {
            setlist.forEach(function(set) {
                Emotes.getSet(set);
            });
            Config.REMOTE_EMOTES.forEach(function(set) {
                Emotes.getSet(set);
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
        $.ajax({
            url: setPath,
            async: true,
            dataType: "json",
            retryCount: 0,
            retryLimit: 15,
            retryTimeout: 60000,
            timeout: 4000,
            errorNotified: false,
            created: Date.now(),
            error: function (xhr, textStatus, errorThrown) {
                this.retryCount++;
                if (this.retryCount <= this.retryLimit && Date.now() - this.created < this.retryTimeout) {
                    if (!this.errorNotified) {
                        this.errorNotified = true;
                        $.notify("Emote: " + errorThrown + ", retrying..");
                    }
                    var retry = this;
                    Emotes.retryID = window.setTimeout(function() { 
                        $.ajax(retry);
                    }, 4000);
                }
            },
            success: function (data, textStatus, xhr) {
                Emotes.parseJson(data);
            }
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
            var emote_img = $('<img >', {
                class: 'emote',
                src: e.name,
                alt: emote.code,
                'data-key': emote.code
            }).click(function(e) {
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