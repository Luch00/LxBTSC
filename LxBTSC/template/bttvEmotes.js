var bttvEmotes = {
    bttvGlobalEmoteJson: "https://api.betterttv.net/2/emotes",
    bttvEmoteUrl: "https://cdn.betterttv.net/emote/",
    bttvEmoteSize: "1x",
    get: function() {
        return new Promise((resolve, reject) => {
            var cached = JSON.parse(localStorage.getItem('bttvJson'));
            
            if (!cached) {
                $.get(this.bttvGlobalEmoteJson, function(data) {
                    localStorage.setItem('bttvJson', JSON.stringify(data));
                    bttvEmotes.parseJson(data);
                    resolve();
                });
            }
            else {
                bttvEmotes.parseJson(cached);
                resolve();
            }
        });
        
    },
    parseJson: function(json) {
        json['emotes'].forEach(function(element) {
            var e = { name: `${bttvEmotes.bttvEmoteUrl}${element.id}/${bttvEmotes.bttvEmoteSize}` }
            Emotes.addEmote(element.code, e);
        });
    }
}