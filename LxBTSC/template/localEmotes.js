var localEmotes = {
    localEmoteJson: "emotesets.json",
    get: function() {
        return new Promise((resolve, reject) => {
            this.getBlacklist();
            $.getJSON(this.localEmoteJson, function(setlist) {
                setlist.forEach(function(set) {
                    localEmotes.getSet(set);
                }), resolve();
            });
        });
    },
    getBlacklist: function() {
        $.getJSON("emoteblacklist.json", function(data) {
            Emotes.emoteBlackList = data;
        });
    },
    getSet: function(set) {
        $.getJSON("Emotes/" + set, function(data) {
            localEmotes.parseJson(data);
        });
    },
    parseJson: function(json) {
        json.emoticons.forEach(function(emote) {
            var e = { name: `${json.pathBase}${emote.name}${json.pathAppend}` }
            Emotes.addEmote(emote.code, e);
        });
    }
}