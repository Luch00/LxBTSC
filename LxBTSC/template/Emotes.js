var Emotes = {
    emoteList: new Array(),
    emoteKeyList: new Array(),
    addEmote: function (key, value) {
        if (!this.emoteList.hasOwnProperty(key)) {
            this.emoteList[key] = value;
        }
    },
    emoticonize: function (string) {
        //Object.keys(this.emoteList).forEach(function(key) {
            //string = string.replace(new RegExp("(?!<a[^>]*?>)("+escapeRegExp(key)+")(?![^<]*?</a>)", 'g'), '<img class="emote" src="'+Emotes.emoteList[key].name+'" alt="'+key+'">');
            //string = string.replace(new RegExp('(?!<[^>]*?>)('+escapeRegExp(key)+')(?![^<]*?(</a>|">))', 'g'), '<img class="emote" src="'+Emotes.emoteList[key].name+'" alt="'+key+'">');
        //});
        this.emoteKeyList.forEach(function(key) {
            string = string.replace(new RegExp('(?!<[^>]*?>)('+escapeRegExp(key)+')(?![^<]*?(</a>|">))', 'g'), '<img class="emote" src="'+Emotes.emoteList[key].name+'" alt="'+key+'">');
        });
        return string;
    },
    makeKeyList: function () {
        this.emoteKeyList = Object.keys(this.emoteList).sort(function(a, b) {
            return b.length - a.length;
        });
    }
}