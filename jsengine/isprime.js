// is_prime.js
// a demo js to test a given number is prime number or not


// return true if prime, false if not
exports.is_prime = function(nn) {
    if (nn <= 1)
        return false;

    if (nn == 2 || nn == 3 || nn == 5 || nn == 7)
        return true;

    if (nn % 2 == 0 || nn % 3 == 0 || nn % 5 == 0 || nn % 7 == 0)
        return false;

    // first prime to test from 11
    for (pp = 11; pp*pp < nn; pp += 2)  {
        if (nn % pp == 0)
            return false;
    }

    return true;
}

exports.randint = function(_max) {
    return Math.floor(Math.random() * _max);
}

exports.pick_one = function(array) {
    var _n = Math.floor(Math.random() * array.length);
    return array[_n];
}

var jo = {
    "a": "apple",
    "b": "ball",
    "c": "cat",
    "d": "duck",
    "array": [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59,
        61, 67, 71, 73, 79, 83, 89, 97]
};

(function() {
    var n = 307;
    console.log(n + " is" + (is_prime(n) ? "" : " not") + " prime number");
    n = 408;
    console.log(n + " is" + (is_prime(n) ? "" : " not") + " prime number");

    var _sum = pick_one(jo["array"]) + pick_one(jo["array"]);
    console.log("_sum:" + _sum);

    return true;
}());
