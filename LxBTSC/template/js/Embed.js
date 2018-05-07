'use strict'
var imageMime = [ "image/gif", "image/jpeg", "image/png", "image/svg+xml", "image/webp" ];
var audioMime = [ "audio/wave", "audio/wav", "audio/x-wav", "audio/x-pn-wav", "audio/webm", "audio/ogg", "audio/flac"];
var videoMime = [ "video/webm", "video/ogg", "application/ogg" ];

function Embed(message_id, message_text) {
    $('a', message_text).each(function(index, element){
        let url = element;
        if (url.protocol.toLocaleLowerCase().startsWith("http")) {
            
            $.getJSON('extract/' + encodeURIComponent(url.href)).then(function(json) {
                console.log(json);
                // embed single file
                if (json.file) {
                    // image
                    if (imageMime.indexOf(json.file.mime) > -1) {
                        addEmbed(ImageFile(url.href), message_id);
                        return;
                    }
                    // audio
                    if (audioMime.indexOf(json.file.mime) > -1) {
                        addEmbed(AudioFile(url.href), message_id);
                    }
                    // video
                    if (videoMime.indexOf(json.file.mime) > -1) {
                        addEmbed(VideoFile(url.href), message_id);
                    }
                    return;
                }

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
                    let promise = Yandere(json).then(function(result) {
                        addEmbed(result, message_id);
                    })
                    .catch(function() {
                        console.log("yande.re embed failed");
                    });
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
                if (json.ogTitle) {
                    addEmbed(Generic(json), message_id);
                }
            });
        }
    });
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
        src: json.ogVideoUrl
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
            html: $('<img/>', { src: encodeURI(json.ogImage) })
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
    // yande.re sample images fail to load for some reason on old chromium
    // so download it via server
    return new Promise((resolve, reject) => {
        if (json.ogImage) {
            let embed = $('<div/>', {
                class: "generic-file-embed"
            });
            let img = new Image();
            img.className = "embed-image";
            let a = $('<a/>', {
                "data-featherlight": "image",
                html: img
            });
            $.get('base64image/' + encodeURIComponent(json.ogImage)).then(function(text) {
                img.src = text;
                a.attr("href", text);
                a.featherlight();
                embed.append(a);
                resolve(EmbedBlock(embed));
            })
            .catch(function(e) {
                reject(Error("base64image failed"));
            });
        }
    });
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
    embed.append('<div><a href="'+ ((json.ogUrl) ? json.ogUrl : url.href) +'" class="embed-og-title">'+json.ogTitle+'</a></div>');
    if (json.ogDescription) {
        embed.append('<div class="embed-og-description">'+json.ogDescription+'</div>');
    }
    else if (json.Description) {
        embed.append('<div class="embed-og-description">'+json.Description+'</div>');
    }
    
    if (json.ogImage) {
        let img = new Image();
        img.className = "embed-og-image";
        let a = $('<a/>', {
            href: encodeURI(json.ogImage),
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