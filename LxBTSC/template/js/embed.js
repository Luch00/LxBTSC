/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2019 Luch (https://github.com/Luch00)
*/
'use strict';
var imageMime = [ "image/gif", "image/jpeg", "image/png", "image/svg+xml", "image/webp" ];
var audioMime = [ "audio/mpeg", "audio/wave", "audio/wav", "audio/x-wav", "audio/x-pn-wav", "audio/webm", "audio/ogg", "audio/flac"];
var videoMime = [ "video/webm", "video/ogg", "application/ogg" ];
var h264capable = false;

function embed(messageId, message_text) {
    $('a', message_text).each(function(index, element) {
        if (element.protocol.toLocaleLowerCase().startsWith("http")) {
            fetchEmbedHead(element.href)
                .then(contentType => {
                    if (contentType.indexOf('text/html') === -1)
                        embedFile(contentType, element.href, messageId);
                    else
                        fetchEmbedData(element.href, messageId)
                            .then(responseText => parseHtml(responseText, element.href, messageId));
                });
        }
    });
}

async function fetchEmbedHead(url) {
    let response = await fetch(url, { method: 'HEAD' });
    let contentType = response.headers.get('Content-Type');
    return contentType;
}

async function fetchEmbedData(url, messageId) {
    try {
        let response = await fetch(url);
        let responseText = await response.text();
        return responseText;
    }
    catch (error) {
        console.log(error);
    }
}

function parseHtml(htmlString, url, messageId) {
    let s = htmlString.substring(0, htmlString.indexOf('</head>'));
    //console.log(s);
    let parser = new DOMParser();
    let doc = parser.parseFromString(s, 'text/html');
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
    embedHtml(set, messageId);
}

function embedFile(fileMIME, url, messageId) {
    //console.log(fileMIME);
    // embed single file
    // image
    if (imageMime.indexOf(fileMIME) > -1) {
        if (fileMIME === "image/gif" && Config.HOVER_ANIMATES_GIFS) {
            addEmbed(freezeframeGif(url), messageId);
        }
        else {
            addEmbed(imageFile(url), messageId);
        }
    }
    // audio
    if (audioMime.indexOf(fileMIME) > -1) {
        addEmbed(audioFile(url), messageId);
    }
    // video
    if (videoMime.indexOf(fileMIME) > -1) {
        addEmbed(videoFile(url), messageId);
    }
}

function embedHtml(json, messageId) {
    //console.log(json);

    if (json.ogSiteName === "YouTube") {
        addEmbed(youtube(json), messageId);
        return;
    }

    if (json.ogSiteName === "Gfycat") {
        addEmbed(gfycat(json), messageId);
        return;
    }

    if (json.ogSiteName === "Twitter") {
        addEmbed(twitter(json), messageId);
        return;
    }

    if (json.ogSiteName === "Pastebin") {
        addEmbed(pastebin(json), messageId);
        return;
    }

    if (json.ogSiteName === "Gist") {
        addEmbed(gist(json), messageId);
        return;
    }

    if (json.ogSiteName === "yande.re") {
        addEmbed(yandere(json), messageId);
        return;
    }

    if (json.ogSiteName === "Spotify") {
        addEmbed(spotify(json), messageId);
        return;
    }

    if (json.twitterSite === "@pornhub") {
        addEmbed(pornhub(json), messageId);
        return;
    }

    // not webm
    if (json.ogSiteName === "ニコニコ動画" && h264capable) {
        addEmbed(nicovideo(json), messageId);
        return;
    }

    // not webm
    if (json.ogSiteName === "Twitch" && json.ogType === "video.other" && h264capable) {
        addEmbed(twitch(json), messageId);
        return;
    }

    // generic embed
    if (!Config.GENERICS_DISABLED && json.ogTitle) {
        addEmbed(generic(json), messageId);
    }
}

function freezeframeGif(url) {
    let embed = $('<div/>', {
        class: "generic-file-embed"
    });
    let img = new Image();
    img.className = "embed-image";
    img.setAttribute('crossOrigin', 'anonymous');

    let a = $('<a/>', {
        class: 'hidden-image fancybox',
        href: url
    });

    a.append(img);
    img.onload = function() {
        $(img).freezeframe({overlay: true});        
        $(a).removeClass('hidden-image');
    };
    img.src = encodeURI(url);

    embed.append(a);
    return embedBlock(embed);
}

function imageFile(url) {
    let embed = $('<div/>', {
        class: "generic-file-embed"
    });
    let img = new Image();
    img.className = "embed-image";

    let a = $('<a/>', {
        class: 'fancybox',
        href: url,
        html: img
    });
    img.onerror = function() {
        console.log("image load failed");
        embed.parent().remove();
    };
    img.src = encodeURI(url);

    embed.append(a);
    return embedBlock(embed);
}

function audioFile(url) {
    let embed = $('<div/>', {
        class: "generic-file-embed"
    });
    let audio = $('<audio/>', {
        controls: true,
        preload: "metadata",
        src: encodeURI(url)
    });
    embed.append(audio);
    return embedBlock(embed);
}

function videoFile(url) {
    let embed = $('<div/>', {
        class: "generic-file-embed"
    });
    let video = $('<video/>', {
        /*width: "100%",*/
        /*height: "100%",*/
        height: "250px",
        controls: true,
        loop: true,
        allowfullscreen: true,
        preload: "metadata",
        src: encodeURI(url)
    });
    embed.append(video);
    return embedBlock(embed);
}

function youtube(json) {
    let embed;
    if (json.twitterPlayer) {
        embed = $('<iframe/>', {
            frameborder: "0",
            width: "400",
            height: "225",
            src: `${json.twitterPlayer}${json.twitterPlayer.includes('?') ? '&' : '?'}rel=0&modestbranding=1`,
            allowfullscreen: ""
        });
    }
    // embedding is disabled by uploader, create embed link manually
    // replace with image placeholder?
    else {
        var rx = /^.*(youtu.be\/|v\/|u\/\w\/|embed\/|watch\?v=|\&v=)([^#\&\?]*).*/;
        var match = json.url.match(rx);
        if (match && match[2]) {
            embed = $('<iframe/>', {
                frameborder: "0",
                width: "400",
                height: "225",
                src: `https://www.youtube.com/embed/${match[2]}`,
                allowfullscreen: ""
            });
        }
        else {
            return;
        }
    }
    return embedBlock(embed);
}

function twitter(json) {
    let name = json.ogTitle.split(' on Twitter', 1);
    let username = json.path.substr(1).split('/', 1);
    let tweet = $('<div/>', {
        class: "tweet-container"
    });
    tweet.append('<img src="https://twitter.com/'+username+'/profile_image?size=mini" class="twitter-avatar">');
    tweet.append('<span><a href="'+json.ogUrl+'" class="twitter-username">'+name+' (@'+username+')</a></span>');
    tweet.append('<div class="twitter-description">'+autolinker.link(json.ogDescription.slice(1, -1))+'</div>');
    if (json.ogImageUserGenerated === "true") {
        let img = $('<a/>', {
            class: "tweet-image fancybox",
            href: json.ogImage,
            html: $('<img/>', { class: "tweet-image", src: encodeURI(json.ogImage) })
        });
        tweet.append(img);
    }
    // not webm & iframe fails to load, frame-ancestor csp
    /*if (json.ogType == "video" && h264capable) {
        tweet.append(`<div><iframe src="${json.ogVideoUrl}" height="250" frameborder="0" allowfullscreen></iframe></div>`)
    }*/
    return embedBlock(tweet);
}

function pastebin(json) {
    let embed = $('<iframe/>', {
        frameborder: "0",
        width: "100%",
        src: "https://pastebin.com/embed_iframe/" + json.path.substr(1)
    });
    return embedBlock(embed);
}

function gist(json) {
    let embed = $('<iframe/>', {
        frameborder: '0',
        width: '100%',
        src: json.ogUrl + '.pibb?scroll=true'
    });
    return embedBlock(embed);
}

function gfycat(json) {
    let embed = $('<iframe/>', {
        src: json.ogVideoIframe,
        frameborder: '0',
        scrolling: 'no',
        allowfullscreen: true,
        width: '400',
        height: '225'
    });
    return embedBlock(embed);
}

function spotify(json) {
    let embed = $('<iframe/>', {
        width: 250,
        height: 330,
        'allow': 'encrypted-media',
        frameborder: "0",
        src: json.twitterPlayer.split('?', 1)
    });
    return embedBlock(embed);
}

function pornhub(json) {
    let embed = $('<iframe/>', {
        frameborder: "0",
        width: "400",
        height: "225",
        allowfullscreen: true,
        scrolling: "no",
        src: json.ogVideoUrl
    });
    return embedBlock(embed);
}

function yandere(json) {
    let embed = $('<div/>', {
        class: "generic-file-embed"
    });
    let img = new Image();
    img.className = "embed-image";

    let a = $('<a/>', {
        class: 'fancybox',
        href: json.ogImage,
        html: img
    });
    img.onerror = function() {
        console.log("image load failed");
        embed.parent().remove();
    };
    img.src = encodeURI(json.ogImage);

    embed.append(a);
    return embedBlock(embed);
}

function nicovideo(json) {
    let embed = $('<iframe/>', {
        frameborder: "0",
        width: "400",
        height: "225",
        allowfullscreen: true,
        src: json.twitterPlayer
    });
    return embedBlock(embed);
}

function twitch(json) {
    if (json.host === 'clips.twitch.tv') {
        let embed = $('<iframe/>', {
            frameborder: "0",
            allowfullscreen: "true",
            width: "400",
            height: "225",
            src: json.twitterPlayer + "&autoplay=false"
        });
        return embedBlock(embed);
    }
    let embed = $('<iframe/>', {
        frameborder: "0",
        allowfullscreen: "true",
        width: "400",
        height: "225",
        src: json.ogVideoSecureUrl.replace('autoplay=true', 'autoplay=false')
    });
    return embedBlock(embed);
}

function generic(json) {
    let embed = $('<div/>', {
        class: "generic-og-embed"
    });
    //embed.append(`<div><a href="${((json.ogUrl) ? json.ogUrl : json.url)}" class="embed-og-title">${json.ogTitle}</a></div>`);
    embed.append($('<a/>', {class: 'embed-og-title', href: json.ogUrl ? json.ogUrl : json.url, text: json.ogTitle}).wrap('<div>'));
    if (json.ogDescription) {
        embed.append(`<div class="embed-og-description">${json.ogDescription}</div>`);
    }
    else if (json.Description) {
        embed.append(`<div class="embed-og-description">${json.Description}</div>`);
    }
    
    if (json.twitterImage || json.ogImage) {
        let img = new Image();
        img.className = "embed-og-image";
        let a = $('<div/>').append(
            $('<a/>', {
                class: 'fancybox',
                href: encodeURI(json.twitterImage || json.ogImage),
                html: img
            })
        );
        img.onerror = function() {
            console.log("image load failed");
            img.remove();
        };
        img.src = json.ogImage;
        embed.append(a);
    }
    return embedBlock(embed);
}

function addEmbed(embed, messageId) {
    document.getElementById(messageId).insertAdjacentElement('afterend', embed[0]);
}

function embedBlock(embed) {
    let embed_container = $('<div/>', { class:'outer-container' }).append(
                            $('<div/>', { class:'embed-container' }).append([
                                    embed, 
                                    $('<a/>', { class:'close-embeds', href:'#_', title:'close', text:'x' })
                            ]));
    return embed_container;
}

function fixName(name) {
    return name.replace(/(?::|_)(\w)/g, (matches, letter) => letter.toUpperCase());
}

(() => {
    const v = document.createElement('video');
    if (v.canPlayType('video/mp4; codecs="avc1.42E01E"') === "probably") {
        videoMime.push('video/mp4');
        h264capable = true;
    }
})();