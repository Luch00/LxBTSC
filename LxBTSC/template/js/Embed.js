'use strict'
var imageMime = [ "image/gif", "image/jpeg", "image/png", "image/svg+xml", "image/webp" ];
var audioMime = [ "audio/wave", "audio/wav", "audio/x-wav", "audio/x-pn-wav", "audio/webm", "audio/ogg", "audio/flac"];
var videoMime = [ "video/webm", "video/ogg", "application/ogg" ];

function Embed(message_id, message_text) {
    $('a', message_text).each(function(index, element) {
        //let url = element;
        if (element.protocol.toLocaleLowerCase().startsWith("http")) {
            QtObject.requestEmbedData(element.href, message_id);
        }
    });
}

function ParseHtml(htmlString, url, message_id) {
    let parser = new DOMParser();
    let doc = parser.parseFromString(htmlString, 'text/html');
    //console.log(doc);
    let meta = doc.getElementsByTagName('meta');
    let set = {};
    let embedUrl = new URL(url);
    set['title'] = doc.title;
    set['host'] = embedUrl.hostname;
    set['path'] = embedUrl.pathname;
    set['url'] = url;
    Array.prototype.forEach.call(meta, element => {
        let name = element.getAttribute('property');
        let content = element.getAttribute('content');
        if (!name) {
            name = element.getAttribute('name');
        }
        if (!name) {
            name = element.getAttribute('itemprop');
        }
        if (!name) {
            return;
        }
        set[fixName(name)] = content;
    });
    console.log(set);
    EmbedHtml(set, message_id);
}

function EmbedFile(fileMIME, url, message_id) {
    //console.log(fileMIME);
    // embed single file
    // image
    if (imageMime.indexOf(fileMIME) > -1) {
        if (fileMIME == "image/gif" && Config.HOVER_ANIMATES_GIFS) {
            addEmbed(ThumbnailGif(url), message_id);
        }
        else {
            addEmbed(ImageFile(url), message_id);
        }
    }
    // audio
    if (audioMime.indexOf(fileMIME) > -1) {
        addEmbed(AudioFile(url), message_id);
    }
    // video
    if (videoMime.indexOf(fileMIME) > -1) {
        addEmbed(VideoFile(url), message_id);
    }
}

function EmbedHtml(json, message_id) {
    //console.log(json);

    if (json.ogSiteName == "YouTube") {
        // embed youtube
        addEmbed(Youtube(json), message_id);
        return;
    }

    if (json.ogSiteName == "Gfycat") {
        addEmbed(Gfycat(json), message_id);
        return;
    }

    if (json.ogSiteName == "Twitter") {
        addEmbed(Twitter(json), message_id);
        return;
    }

    if (json.ogSiteName == "Pastebin") {
        addEmbed(Pastebin(json), message_id);
        return;
    }

    if (json.ogSiteName == "yande.re") {
        addEmbed(Yandere(json), message_id);
        return;
    }

    // embed works but does not play
    // most likely requires a newer version of chromium
    /*if (json.ogSiteName == "Spotify") {
        addEmbed(Spotify(json), message_id);
        return;
    }*/

    if (json.twitterSite == "@pornhub") {
        addEmbed(Pornhub(json), message_id);
        return;
    }

    // not webm
    /*if (json.ogSiteName == "ニコニコ動画") {
        addEmbed(Nicovideo(json), message_id);
        return;
    }*/

    // generic embed
    if (!Config.GENERICS_DISABLED && json.ogTitle) {
        addEmbed(Generic(json), message_id);
    }
}

function ThumbnailGif(url) {
    let embed = $('<div/>', {
        class: "generic-file-embed"
    });
    let img = new Image();
    img.className = "embed-image hidden-image";
    img.setAttribute('crossOrigin', 'anonymous');
    let still = new Image();
    still.className = "embed-image still-image";
    still.setAttribute('crossOrigin', 'anonymous');

    let a = $('<a/>', {
        class: 'play-gif',
        href: url,
        "data-featherlight": "image",
    });
    a.append(still);
    a.append(img);
    img.onload = function() {
        let canvas = document.createElement('canvas');
        let ctx = canvas.getContext('2d');
        canvas.height = img.naturalHeight;
        canvas.width = img.naturalWidth;
        ctx.drawImage(img, 0, 0);
        ctx.beginPath();
        ctx.moveTo(5, 5);
        ctx.lineTo(15, 10);
        ctx.lineTo(5, 15);
        ctx.fill();
        still.src = canvas.toDataURL('image/png');
    }
    img.src = encodeURI(url);

    a.featherlight();
    embed.append(a);
    return EmbedBlock(embed);
}

function ImageFile(url) {
    let embed = $('<div/>', {
        class: "generic-file-embed"
    });
    let img = new Image();
    img.className = "embed-image";

    let a = $('<a/>', {
        href: url,
        "data-featherlight": "image",
        html: img
    });
    /*i.onload = function() {
        console.log("success");
    };*/
    img.onerror = function() {
        console.log("image load failed");
        embed.parent().remove();
    };
    img.src = encodeURI(url);

    a.featherlight();
    embed.append(a);
    return EmbedBlock(embed);
}

function AudioFile(url) {
    let embed = $('<div/>', {
        class: "generic-file-embed"
    });
    let audio = $('<audio/>', {
        controls: true,
        preload: "metadata",
        src: encodeURI(url)
    });
    embed.append(audio);
    return EmbedBlock(embed);
}

function VideoFile(url) {
    let embed = $('<div/>', {
        class: "generic-file-embed"
    });
    let video = $('<video/>', {
        width: "100%",
        height: "100%",
        controls: true,
        loop: true,
        allowfullscreen: true,
        preload: "metadata",
        src: encodeURI(url)
    });
    embed.append(video);
    return EmbedBlock(embed);
}

function Youtube(json) {
    let embed = $('<iframe/>', {
        frameborder: "0",
        width: "400",
        height: "225",
        allowfullscreen: true,
        src: json.twitterPlayer
    });
    return EmbedBlock(embed);
}

function Twitter(json) {
    let name = json.ogTitle.split(' on Twitter', 1);
    let username = json.path.substr(1).split('/', 1);
    let tweet = $('<div/>', {
        class: "tweet-container"
    });
    tweet.append('<img src="https://twitter.com/'+username+'/profile_image?size=mini" class="twitter-avatar">');
    tweet.append('<span><a href="'+json.ogUrl+'" class="twitter-username">'+name+' (@'+username+')</a></span>');
    tweet.append('<div class="twitter-description">'+anchorme(json.ogDescription.slice(1, -1))+'</div>');
    if (json.ogImageUserGenerated == "true") {
        let img = $('<a/>', {
            class: "tweet-image",
            href: json.ogImage,
            "data-featherlight": "image",
            html: $('<img/>', { class: "tweet-image", src: encodeURI(json.ogImage) })
        });
        img.featherlight();
        tweet.append(img);
    }
    // videos don't work, not webm
    /*if (json.ogType == "video") {
        tweet.append('<div><video src="'+json.ogVideoUrl+'"</video></div>');
    }*/
    return EmbedBlock(tweet);
}

function Pastebin(json) {
    let embed = $('<iframe/>', {
        frameborder: "0",
        width: "100%",
        src: "https://pastebin.com/embed_iframe/" + json.path.substr(1)
    });
    return EmbedBlock(embed);
}

function Gfycat(json) {
    let embed = $('<iframe/>', {
        src: json.ogVideoIframe,
        frameborder: '0',
        scrolling: 'no',
        allowfullscreen: true,
        width: '400',
        height: '225'
    });
    return EmbedBlock(embed);
}

function Spotify(json) {
    let embed = $('<iframe/>', {
        frameborder: "0",
        src: json.twitterPlayer
    });
    return EmbedBlock(embed);
}

function Pornhub(json) {
    let embed = $('<iframe/>', {
        frameborder: "0",
        width: "400",
        height: "225",
        allowfullscreen: true,
        scrolling: "no",
        src: json.ogVideoUrl
    });
    return EmbedBlock(embed);
}

function Yandere(json) {

    let embed = $('<div/>', {
        class: "generic-file-embed"
    });
    let img = new Image();
    img.className = "embed-image";

    let a = $('<a/>', {
        href: json.ogImage,
        "data-featherlight": "image",
        html: img
    });
    /*i.onload = function() {
        console.log("success");
    };*/
    img.onerror = function() {
        console.log("image load failed");
        embed.parent().remove();
    };
    img.src = encodeURI(json.ogImage);

    a.featherlight();
    embed.append(a);
    return EmbedBlock(embed);
}

function Nicovideo(json) {
    let embed = $('<iframe/>', {
        frameborder: "0",
        width: "400",
        height: "225",
        allowfullscreen: true,
        src: json.twitterPlayer
    });
    return EmbedBlock(embed);
}

function Generic(json) {
    let embed = $('<div/>', {
        class: "generic-og-embed"
    });
    //embed.append(`<div><a href="${((json.ogUrl) ? json.ogUrl : json.url)}" class="embed-og-title">${json.ogTitle}</a></div>`);
    embed.append($('<a/>', {class: 'embed-og-title', href: ((json.ogUrl) ? json.ogUrl : json.url), text: json.ogTitle}).wrap('<div>'));
    if (json.ogDescription) {
        embed.append(`<div class="embed-og-description">${json.ogDescription}</div>`);
    }
    else if (json.Description) {
        embed.append(`<div class="embed-og-description">${json.Description}</div>`);
    }
    
    if (json.twitterImage || json.ogImage) {
        let img = new Image();
        img.className = "embed-og-image";
        let a = $('<a/>', {
            href: encodeURI(json.twitterImage || json.ogImage),
            "data-featherlight": "image",
            html: img
        });
        /*i.onload = function() {
            console.log("success");
        };*/
        img.onerror = function() {
            console.log("image load failed");
            img.remove();
        };
        img.src = json.ogImage;
        a.featherlight();
        embed.append(a);
    }
    return EmbedBlock(embed);
}

function addEmbed(embed, message_id) {
    embed.insertAfter($('#'+message_id));
}

function EmbedBlock(embed) {
    let embed_container = $('<div/>', { class:'outer-container' }).append($('<div/>', { class:'embed-container' }).append(embed));
    let close_a = $('<a/>', { class:'close-embeds', href:'#_', title:'close', text:'x' })
    .click(function(e) {
        $(this).parent().remove();
    });
    embed_container.append(close_a);
    return embed_container;
}

function fixName(name) {
    return name.replace(/(?::|_)(\w)/g, (matches, letter) => letter.toUpperCase());
}
