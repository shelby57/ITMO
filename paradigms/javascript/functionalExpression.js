"use strict"

const VARIABLES = "xyz";

const operation = function (f) {
    return function () {
        let operands = arguments;
        return function () {
            let result = [];
            for (let i = 0; i < operands.length; i++) {
                result.push(operands[i].apply(null, arguments));
            }
            return f.apply(null, result);
        }
    }
};

const cnst = value => _ => value;

const variable = function (name) {
    return function () {
        const ind = VARIABLES.indexOf(name);
        return arguments[ind];
    }
};

// :NOTE: вот здесь для компактности записи можно было использовать стрелочную нотацию

const add = operation(function (x, y) {
    return x + y;
});

const subtract = operation(function (x, y) {
    return x - y;
});

const multiply = operation(function (x, y) {
    return x * y;
});

const divide = operation(function (x, y) {
    return x / y;
});

const negate = operation(function (x) {
    return -x;
});

const pi = cnst(Math.PI);
const e = cnst(Math.E);

const sinh = operation(function (x) {
    return Math.sinh(x);
});

const cosh = operation(function (x) {
    return Math.cosh(x);
});
