var Emotes = {
    emoteList: new Map(),
    emoteKeyList: [],
    emote_list_element: {},
    retryID: 0,
    addEmote: function (key, value) {
        if (this.emoteList.has(key)) {
            this.emoteList.get(key).element.remove();
            $('.emote-container:empty').parent().remove();
        }
        this.emoteList.set(key, value);
    },
    emoticonize: function (string) {
        var html = string.html();
        this.emoteKeyList.forEach(function(key) {
            html = html.replace(new RegExp(escapeRegExp(key)+'(?![^<]*?(?:</a>|">))', 'g'), 
                '<img class="emote" src="'+Emotes.emoteList.get(key).name+'" alt="'+key+'" onmouseenter="showTooltip(this)" onmouseleave="hideTooltip()">');
        });
        string.html(html);
    },
    makeKeyList: function () {
        console.log("makeKeyList");
        this.emoteKeyList = Array.from(this.emoteList.keys()).sort(function(a, b) {
            return b.length - a.length;
        });
    },
    clear: function () {
        window.clearTimeout(Emotes.retryID);
        Emotes.emoteList.clear();
        Emotes.emoteKeyList = [];
        Emotes.emote_list_element.empty();
    },
    load: function () {
        $.getJSON('emotes/local-list/', function(data) {
            data.forEach(function(set) {
                Emotes.parseJson(set);
            });
        });
        Config.REMOTE_EMOTES.forEach(function(set) {
            $.getJSON('emotes/remote/'+encodeURIComponent(set), function(data) {
                Emotes.parseJson(data);
            });
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
            })
            .on('mouseenter', function() { showTooltip($(this)[0]); })
            .on('mouseleave', function() { hideTooltip(); })
            .click(function(e) {
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