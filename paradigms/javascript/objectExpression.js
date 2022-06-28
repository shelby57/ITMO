"use strict";


function Variable(name) {
    this.name = name;
    this.evaluate = function () {
        return arguments["xyz".indexOf(this.name)];
    }
    this.toString = function () {
        return this.name;
    }
}

function Const(value) {
    this.value = value;
    this.toString = function () {
        return this.value.toString();
    }
    this.evaluate = function () {
        return this.value;
    }
}

const Operation = function (...arg) {
    this.evaluate = function (...args) {
        const result = arg.map(function (operand) {
            return operand.evaluate(...args);
        })
        return this.f(...result);
    }
    this.toString = function () {
        return arg.join(" ") + " " + this.operation;
    }
}

const newOperation = function (f, operation) {
    const result = function (...arg) {
        result.prototype = new Operation;
        this.f = f;
        this.operation = operation;
        Operation.apply(this, arg);
    }
    return result;
}

const Add = newOperation((left, right) => left + right, "+");
const Subtract = newOperation((left, right) => left - right, "-");
const Multiply = newOperation((left, right) => left * right, "*");
const Divide = newOperation((left, right) => left / right, "/");
const Negate = newOperation((value) => -value, "negate");
const Sinh = newOperation((value) => Math.sinh(value), "sinh");
const Cosh = newOperation((value) => Math.cosh(value), "cosh");

const parse = function (source) {
    let tokens = source.split(" ").filter(function (t) {
        return t.length > 0;
    });
    let result = [];
    const BINARY_OPERATION = {
        "+": (...arg) => new Add(arg[0], arg[1]),
        "-": (...arg) => new Subtract(arg[0], arg[1]),
        "*": (...arg) => new Multiply(arg[0], arg[1]),
        "/": (...arg) => new Divide(arg[0], arg[1])
    }
    const UNARY_OPERATION = {
        "negate": (...arg) => new Negate(arg[0]),
        "sinh": (...arg) => new Sinh(arg[0]),
        "cosh": (...arg) => new Cosh(arg[0])
    }
    for (const token of tokens) {
        if ("xyz".indexOf(token) !== -1) {
            result.push(new Variable(token));
        } else if (token in BINARY_OPERATION) {
            let right = result.pop()
            let left = result.pop()
            result.push(BINARY_OPERATION[token](left, right));
        } else if (token in UNARY_OPERATION) {
            result.push(UNARY_OPERATION[token](result.pop()));
        } else {
            result.push(new Const(Number(token)));
        }
    }
    return result.pop();
}
