'use strict'
let apikey = "7ASG3DHEKMVX"
let anonid;
let result_element;

function init_tenor() {
    result_element = document.getElementById('tenor-results');
    console.log(result_element);
    anonid = localStorage.getItem('anonid');
    let url = "https://api.tenor.com/v1/anonid?key=" + apikey;
    if (!anonid) {
        $.getJSON(url, function(response) {
            anonid = response['anon_id'];
            localStorage.setItem('anonid', anonid);
            search_tenor();
        });
    }
    else {
        search_tenor();
    }
}

function search_tenor() {
    let input = document.getElementById('tenor-search');
    let search_term = input.value;
    let limit = 10;

    let search_url = `https://api.tenor.com/v1/search?tag=${search_term}&key=${apikey}&limit=${limit}&anon_id=${anonid}`;
    sessionStorage.setItem('tenorUrl', search_url);
    $.getJSON(search_url, search_new_clear);
}

function search_more(){
    let search_url = sessionStorage.getItem('tenorUrl');
    let next = sessionStorage.getItem('next');
    if (next > 0) {
        search_url = search_url + "&pos=" + sessionStorage.getItem('next');
        $.getJSON(search_url, search_append_callback);
    }
}

function search_new_clear(json) {
    let elem = document.getElementById('tenor-results');
    elem.innerHTML = "";
    search_append_callback(json);
}

function search_append_callback(json) {
    console.log(json);
    sessionStorage.setItem('next', json['next']);
    let elem = document.getElementById('tenor-results');
    let results = json['results'];
    results.forEach(element => {
        let img = new Image;
        img.className = "tenor-gif";
        img.setAttribute('share-url', element['media'][0]['gif']['url']);
        img.src = element['media'][0]['nanogif']['url'];
        img.onclick = function() { emoteClicked(this.getAttribute('share-url'), false); }
        elem.appendChild(img);
    });
}
