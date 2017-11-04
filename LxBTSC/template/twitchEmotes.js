var twitchEmotes = {
    twitchGlobalEmoteJson: "https://twitchemotes.com/api_cache/v3/global.json",
    twitchEmoteUrl: "https://static-cdn.jtvnw.net/emoticons/v1/",
    twitchEmoteSize: "1.0",
    get: function() {
        return new Promise((resolve, reject) => {
            var cached = JSON.parse(localStorage.getItem('twitchJson'));
            if (!cached) {
                $.get(this.twitchGlobalEmoteJson, function(data) {
                    localStorage.setItem('twitchJson', JSON.stringify(data));
                    twitchEmotes.parseJson(data);
                    resolve();
                });
            }
            else {
                twitchEmotes.parseJson(cached);
                resolve();
            }
        });
        
    },
    parseJson: function(json) {
        Object.keys(json).forEach(function(key) {
            var e = { name: `${twitchEmotes.twitchEmoteUrl}${json[key].id}/${twitchEmotes.twitchEmoteSize}` }
            Emotes.addEmote(json[key].code, e);
        });
    }
}