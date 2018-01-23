function GetFavicons(parse) {
    'use strict'
    $('a', parse).each(function(index, element) {
        if (element.protocol.startsWith('http')) {
            let hostname = element.hostname;
            let icon = $('<img/>', {
                class: "url-favicon",
                src: "http://www.google.com/s2/favicons?domain=" + hostname,
                onerror: "this.style.display = 'none'"
            });
            $(element).before(icon);
        }
    });
}