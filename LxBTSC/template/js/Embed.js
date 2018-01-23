function Embed(message_id, message_text) {
    'use strict'
    let embeds = [];

    $('a', message_text).each(function(index, element){
        let url = element;
        if (url.protocol.toLocaleLowerCase().startsWith("http")) {
            
            let path = url.pathname.toLocaleLowerCase();
            // images
            if (path.endsWith(".png") || path.endsWith(".jpg") || path.endsWith(".jpeg") || path.endsWith(".gif") || path.endsWith(".webp")) {
                console.log('Found image link:' + url.href);
                let embed = $('<a/>', { 
                    href: encodeURI(url.href),
                    html: $('<img/>', { src: encodeURI(url.href) })
                });
                embeds.push(EmbedBlock(embed));
                return;
            }

            // video
            if (path.endsWith(".webm") || path.endsWith(".ogv")) {
                console.log('Found video link:' + url.href);
                let embed = $('<video/>', {
                    width: "100%",
                    height: "100%",
                    controls: true,
                    loop: true,
                    allowfullscreen: true,
                    preload: "metadata",
                    src: encodeURI(url.href)
                });
                embeds.push(EmbedBlock(embed));
                return;
            }

            // gifv to gif
            if (path.endsWith(".gifv")) {
                console.log('Found gifv link:' + url.href);
                let embed = $('<a/>', { 
                    href: encodeURI(url.href),
                    html: $('<img/>', { src: encodeURI(url.href.slice(0, -1)) })
                });
                embeds.push(EmbedBlock(embed));
                return;
            }

            // audio
            if (path.endsWith(".opus") || path.endsWith(".ogg") || path.endsWith(".oga") || path.endsWith(".wav") || path.endsWith(".wma") || path.endsWith(".flac")) {
                console.log('Found audio link:' + url.href)
                let embed = $('<audio/>', {
                    controls: true,
                    preload: "metadata",
                    src: encodeURI(url.href)
                });
                embeds.push(EmbedBlock(embed));
                return;
            }

            // youtube
            let match;
             match = /http(?:s?):\/\/(?:www\.)?youtu(?:be\.com\/watch\?v=|\.be\/)([-_A-Za-z0-9]{10}[AEIMQUYcgkosw048]*)(&(amp;)?[\w\?=]*)?/i.exec(url.href);
             if (match) {
                console.log('Found youtube link:' + match[1]);
                let embed = $('<iframe/>', {
                    frameborder: "0",
                    width: "400",
                    height: "225",
                    allowfullscreen: true,
                    src: "https://www.youtube.com/embed/"+ match[1]
                });
                embeds.push(EmbedBlock(embed));
                return;
             }

             // gfycat (simple)
             match = /(?:gfycat\.com)\/(?:([A-Z][\w\-_]+)|(?:gifs\/detail\/([\w\-_]+)))/.exec(url.href);
             if (match) {
                 let id = match[1];
                 if (match[2]) {
                     id = match[2];
                 }
                console.log('Found gfycat link:' + id);
                
                let embed = $('<video/>', {
                    width: "100%",
                    height: "100%",
                    controls: true,
                    loop: true,
                    allowfullscreen: true,
                    preload: "metadata"
                    //src: "https://giant.gfycat.com/" + id + ".webm"
                });
                // get the url
                $.getJSON('https://gfycat.com/cajax/get/' + id).then(function(json) {
                    let webmurl = json.gfyItem.webmUrl;
                    embed.attr('src', webmurl);
                });
                embeds.push(EmbedBlock(embed));
                return;
             }

             // tweet
             match = /twitter\.com\/\w+\/status\/(\d+)/.exec(url.href);
             if (match) {
                 console.log("tweet found:"+match[1]);
                 let embed = $('<div/>', {
                     class: "tweet-container"
                 });
                 twttr.widgets.createTweet(match[1], $(embed)[0], { cards: 'hidden', width: '400'});
                 embeds.push(EmbedBlock(embed));
                 return;
             }

             // embed works but does not play
             // most likely requires a newer version of chromium
             // spotify track
             //match = /open\.spotify.com\/track\/(\w+)/.exec(url.href);
             //if (match) {
             //    console.log("spotify found");

             //    let embed = $('<iframe/>', {
             //        width: "300",
             //        height: "80",
             //        frameborder: "0",
             //        allowtransparency: "true",
             //        src: "https://open.spotify.com/embed?uri=spotify:track:"+match[1]
             //    });
             //    embeds.push(EmbedBlock(embed));
             //    return;
             //}

             // spotify album
             //match = /open\.spotify\.com\/album\/(\w+)/.exec(url.href);
             //if (match) {}

             // spotify playlist
             //match = /open\.spotify\.com\/user\/(\w+)\/playlist\/(\w+)/.exec(url.href);
             //if (match) {}

             // pastebin
             match = /https?:\/\/pastebin.com\/([0-9a-zA-Z]+)/i.exec(url.href);
             if (match) {
                console.log('Found pastebin link:' + match[1]);
                let embed = $('<iframe/>', {
                    frameborder: "0",
                    width: "100%",
                    src: "https://pastebin.com/embed_iframe/" + match[1]
                });
                embeds.push(EmbedBlock(embed));
                return;
             }

             // pornhub
             match = /https?:\/\/(?:[a-z0-9]+[.])*pornhub[.]com\/view_video.php\?viewkey=([0-9a-z]+)/i.exec(url.href);
             if (match) {
                console.log('Found pornhub link:' + match[1]);
                let embed = $('<iframe/>', {
                    frameborder: "0",
                    width: "400",
                    height: "225",
                    allowfullscreen: true,
                    src: "https://pornhub.com/embed/" + match[1]
                });
                embeds.push(EmbedBlock(embed));
                return;
             }
        }
    });
    if (embeds.length > 0) {
        let embeds_div = $('<div/>', { class:'embeds'});
        let close_a = $('<a/>', { class:'close-embeds', href:'#_', title:'close', text:'x' })
        .click(function(e) {
            $(this).parent().remove();
        });
        for (const element of embeds) {
            embeds_div.append(element);
        }
        embeds_div.append(close_a).insertAfter($('#'+message_id));
    }
}

function EmbedBlock(embed) {
    'use strict'
    let embed_container = $('<div/>').append($('<div/>', { class:'embed-container' }).append(embed));
    return embed_container;
}

$.urlParam = function(url, name){
    var results = new RegExp('[\?&]' + name + '=([^]*)').exec(url);
    if (results==null){
       return null;
    }
    else{
       return results[1] || 0;
    }
}