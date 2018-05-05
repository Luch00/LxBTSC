var Config = {};

function loadConfig() {
    $.getJSON("config/", function(data) {
        Config = data;
    })
    .fail(function() {
        Config.MAX_LINES = 500;
        Config.EMBED_ENABLED = true;
        Config.FAVICONS_ENABLED = false;
        Config.EMOTICONS_ENABLED = true;
        Config.DOWNLOAD_DIR = "";
        Config.REMOTE_EMOTES = [];
    });
}

loadConfig();