var Emotes = {
    emoteList: new Array(),
    emoteKeyList: new Array(),
    emoteBlackList: new Array(),
    addEmote: function (key, value) {
        if (!this.emoteList.hasOwnProperty(key) && $.inArray(key, this.emoteBlackList) === -1) {
            console.log("ADDED: " + key);
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
    }
}