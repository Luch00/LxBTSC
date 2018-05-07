const express = require('express')
const request = require('request')
const extract = require('meta-extractor')
const path = require('path')
const fs = require('fs')

const app = express()

const templatePath = path.normalize(path.join(__dirname, '..', 'template'))

app.use(express.static(templatePath))

app.get('/', (req, res) => res.sendFile('chat.html', { root: templatePath }))

app.get('/config', (req, res) => res.sendFile('config.json', { root: templatePath }))

app.get('/emotes/local-list', (req, res) => {
    let files = []
    const emotePath = path.join(templatePath, 'Emotes')
    fs.readdirSync(emotePath).forEach((file) => {
        if (file.endsWith('.json')) {
            console.log(file);
            files.push(JSON.parse(fs.readFileSync(path.join(emotePath, file), 'utf8')))
        }
    })
    console.log(files);
    res.send(files);
})

app.get('/emotes/local/:file', (req, res) => res.sendFile(req.params.file, { root: path.join(templatePath, 'Emotes') }))

app.get('/emotes/remote/:url', function (req, res) {
    request(req.params.url, function(error, response, body) {
        res.send(body)
    })
})

app.get('/base64image/:url', function(req, res) {
    console.log(req.params.url)
    request(req.params.url, { encoding: null }, function(error, response, body) {
        if (!error && response.statusCode == 200) {
            data = "data:" + response.headers["content-type"] + ";base64," + new Buffer.from(body).toString('base64')
            res.send(data)
        }
    })
})

app.get('/extract/:url', function (req, res) {
    extract({ uri: req.params.url, limit: 5242880 }, (err, ext) => {
        res.send(ext)
    })
})

app.listen(8786, 'localhost', () => console.log('started: 8786'))