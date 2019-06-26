/*
    * Better Chat plugin for TeamSpeak 3
    * GPLv3 license
    *
    * Copyright (C) 2019 Luch (https://github.com/Luch00)
*/
'use strict'
let apikey = "7ASG3DHEKMVX";
let anonid;
let result_element;
let delay;
let lang;

function initTenor() {
    lang = navigator.language;
    result_element = document.getElementById('tenor-results');
    anonid = localStorage.getItem('anonid');
    let url = `https://api.tenor.com/v1/anonid?key=${apikey}`;
    if (!anonid) {
        $.getJSON(url, function(response) {
            anonid = response['anon_id'];
            localStorage.setItem('anonid', anonid);
            searchTrending();
        });
    }
    else {
        searchTrending();
    }
}

function searchTrending() {
    let search_url = `https://api.tenor.com/v1/trending?key=${apikey}&anon_id=${anonid}&locale=${lang}&limit=10`;
    sessionStorage.setItem('tenorUrl', search_url);
    $.getJSON(search_url, searchNewClear);
}

function searchTenor() {
    clearTimeout(delay);
    delay = setTimeout(function() {
        let input = document.getElementById('tenor-search');
        let search_term = input.value;
        if (!search_term) {
            searchTrending();
        }
        else {
            let limit = 10;
            let search_url = `https://api.tenor.com/v1/search?tag=${search_term}&key=${apikey}&limit=${limit}&anon_id=${anonid}&locale=${lang}`;
            sessionStorage.setItem('tenorUrl', search_url);
            $.getJSON(search_url, searchNewClear);
        }
    }, 250);
}

function searchMore(){
    let search_url = sessionStorage.getItem('tenorUrl');
    let next = sessionStorage.getItem('next');
    if (next > 0) {
        search_url = search_url + "&pos=" + sessionStorage.getItem('next');
        $.getJSON(search_url, searchAppendCallback);
    }
}

function searchNewClear(json) {
    result_element.innerHTML = "";
    searchAppendCallback(json);
}

function searchAppendCallback(json) {
    //console.log(json);
    sessionStorage.setItem('next', json['next']);
    let elem = result_element;
    let results = json['results'];
    results.forEach(element => {
        let img = new Image;
        img.className = "tenor-gif";
        img.setAttribute('share-url', element['media'][0]['gif']['url']);
        img.setAttribute('share-id', element['id']);
        img.src = element['media'][0]['nanogif']['url'];
        img.onclick = function() {
            emoteClicked(this.getAttribute('share-url'), false);
            registerShare(this.getAttribute('share-id'));
        };
        elem.appendChild(img);
    });
}

function registerShare(id) {
    let register_url = `https://api.tenor.com/v1/registershare?key=${apikey}&anon_id=${anonid}&locale=${lang}&id=${id}`;
    $.getJSON(register_url, function(data) {
        console.log(data);
    });
}
