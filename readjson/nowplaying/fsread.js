
function getObjFromFile(fname) {
    var fs = require('fs');
    var obj = JSON.parse(fs.readFileSync(fname, 'utf8'));
    return obj;
}

function getObjFromString(objString) {
    var obj = JSON.parse(objString);
    return obj;
}

function getUrlFromObj(obj) {
    var arrlength = obj['items'].length;
    var idx = getRandomint(0, arrlength);
    return obj['items'][idx]['url'];
}

// between min (included) and max (excluded)
// using Math.round() will give you a non-uniform distribution
function getRandomint(min, max)  {
    return Math.floor(Math.random() * (max - min)) + min;
}

function getUrlFromJsonString(objString) {
    return getUrlFromObj( getObjFromString(objString) );
}

function isEmptyString(s) {
    return (s === "");
}



/*
function main() {
    // multi line string using backtick
    var huck = `
        {"items" : [
            {"name": "google", "url": "https://www.google.com/"},
            {"name": "yahoo", "url": "https://tw.yahoo.com/"},
            {"name": "twitter", "url": "https://www.twitter.com/"},
            {"name": "instagram", "url": "https://www.instagram.com/"},
            {"name": "apple", "url": "https://www.apple.com/"}
        ]}
    `;

    var myObj = getObjFromString(huck);
    for (var i = 0 ; i < 3 ; ++i) {
        console.log(getUrlFromObj(myObj));
    }
}

main();
*/