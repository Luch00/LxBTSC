var ffzEmotes = {
    ffzGlobalEmoteJson: "https://api.frankerfacez.com/v1/set/global",
    bttvEmoteSize: "1",
    get: function() {
        return new Promise((resolve, reject) =>{
            var cached = JSON.parse(localStorage.getItem('ffzJson'));
            if (!cached) {
                $.get(this.ffzGlobalEmoteJson, function(data) {
                    localStorage.setItem('ffzJson', JSON.stringify(data));
                    ffzEmotes.parseJson(data);
                    resolve();
                });
            }
            else {
                ffzEmotes.parseJson(cached);
                resolve();
            }
        });
        
    },
    parseJson: function(json) {
        json.sets[3]['emoticons'].forEach(function(element) {
            var e = { name: `https:${element.urls[1]}` }
            Emotes.addEmote(element.name, e);
        });
    }
}