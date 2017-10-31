var twitchEmotes = {
    twitchGlobalEmoteJson: "https://twitchemotes.com/api_cache/v3/global.json",
    twitchEmoteUrl: "https://static-cdn.jtvnw.net/emoticons/v1/",
    twitchEmoteSize: "1.0",
    get: function() {
        var cached = JSON.parse(localStorage.getItem('twitchJson'));

        if (!cached) {
            $.get(this.twitchGlobalEmoteJson, function(data) {
                console.log(data);
                localStorage.setItem('twitchJson', JSON.stringify(data));
                Object.keys(data).forEach(function(key) {
                    var e = { name: `${twitchEmotes.twitchEmoteUrl}${data[key].id}/${twitchEmotes.twitchEmoteSize}` }
                    Emotes.addEmote(data[key].code, e);
                });
            });
        }
        else {
            Object.keys(cached).forEach(function(key) {
                var e = { name: `${twitchEmotes.twitchEmoteUrl}${cached[key].id}/${twitchEmotes.twitchEmoteSize}` }
                Emotes.addEmote(cached[key].code, e);
            });
        }
    }
}