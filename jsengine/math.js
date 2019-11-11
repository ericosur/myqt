export function sum(left, right)
{
    return left + right
}

export function randint(_max) {
    return Math.floor(Math.random() * _max);
}

export function pick_one(array) {
    var _n = Math.floor(Math.random() * array.length);
    return array[_n];
}

export function get_value(_str) {
    var j = JSON.parse(_str);

    if (j["Image"]["Width"] && j["Image"]["Height"]) {
        console.log("width: " + j["Image"]["Width"] + " height: " + j["Image"]["Height"]);
    }

    return j["value"];
}

export function hello_world() {
    var n = JSETest.getName();
    console.log("n = " + n);
    var r = JSETest.getMd5sum(n);
    return r;
}
