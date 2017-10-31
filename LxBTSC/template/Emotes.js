var Emotes = {
    emoteList: new Array(),
    addEmote: function (key, value) {
        if (!this.emoteList.hasOwnProperty(key)) {
            this.emoteList[key] = value;
        }
    },
    emoticonize: function (string) {
        Object.keys(this.emoteList).forEach(function(key) {
            string = string.replace(new RegExp("(?!<a[^>]*?>)("+escapeRegExp(key)+")(?![^<]*?</a>)", 'g'), '<img class="emote" src="'+Emotes.emoteList[key].name+'" alt="'+key+'">');
        });
        return string;
    }
}