var ffzEmotes = {
    ffzGlobalEmoteJson: "https://api.frankerfacez.com/v1/set/global",
    bttvEmoteSize: "1",
    get: function() {
        var cached = JSON.parse(localStorage.getItem('ffzJson'));
        if (!cached) {
            $.get(this.ffzGlobalEmoteJson, function(data) {
                localStorage.setItem('ffzJson', JSON.stringify(data));
                ffzEmotes.parseJson(data);
            });
        }
        else {
            ffzEmotes.parseJson(cached);
        }
    },
    parseJson: function(json) {
        json.sets[3]['emoticons'].forEach(function(element) {
            var e = { name: `https:${element.urls[1]}` }
            Emotes.addEmote(element.name, e);
        });
    }
}