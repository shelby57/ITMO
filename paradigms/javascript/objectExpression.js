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
/*
;Interface
(definterface Expression
  (evaluate [])
  (toString [])
  (diff []))

;Operation
(defn evaluate [expr vars] ((.evaluate expr) vars))
(defn toString [expr] (.toString expr))
(defn diff [expr var] ((.diff expr) var))

(deftype CommonPrototype [operation symbol diffRule])

(deftype CommonOperation [operation symbol diffRule args]
  Expression
  (evaluate [this] #(apply operation (map (fn [x] (evaluate x %)) args)))
  (toString [this] (str "(" symbol " " (clojure.string/join " " (map toString args)) ")"))
  (diff [this] #(apply diffRule (concat args (map (fn [x] (diff x %)) args)))))

;Constant
(declare Constant)

(deftype ConstantPrototype [value]
  Expression
  (evaluate [this] (fn [vars] value))
  (toString [this] (format "%.1f" (double value)))
  (diff [this] (fn [var] (Constant 0))))

(defn Constant [value] (ConstantPrototype. value))

;Variable
(declare Variable)

(defn getVar [name] (str (first (clojure.string/lower-case name))))

(deftype VariablePrototype [name]
  Expression
  (evaluate [this] (fn [vars] (get vars (getVar name))))
  (toString [this] name)
  (diff [this] (fn [var] (if (= var (getVar name)) (Constant 1) (Constant 0)))))

(defn Variable [name] (VariablePrototype. name))

(defn Add [& args] (CommonOperation. + "+" (fn [a b da db] (Add da db)) args))

(defn Subtract [& args] (CommonOperation. - "-" (fn [a b da db] (Subtract da db)) args))

(defn Multiply [& args] (CommonOperation. * "*" (fn [a b da db] (Add (Multiply da b) (Multiply db a))) args))

(defn Divide [& args] (CommonOperation. #(/ (double %1) (double %2)) "/"
                                          (fn [a b da db] (Divide (Subtract (Multiply da b) (Multiply db a)) (Multiply b b))) args))

(defn Negate [& args] (CommonOperation. - "negate" (fn [a da] (Negate da)) args))

(defn Exp [& args] (CommonOperation. #(Math/exp ^double %) "exp" (fn [a da] (Multiply da (Exp a))) args))

(defn Ln [& args] (CommonOperation. #(Math/log (Math/abs ^double %)) "ln" (fn [a da] (Divide da a)) args))

;Parsers

(def OPERATIONS {
                 '+ Add,
                 '- Subtract,
                 '* Multiply,
                 '/ Divide,
                 'negate Negate,
                 'exp Exp,
                 'ln Ln})

(declare parseObject)

(defn parseObject [expression]
  (cond
    (number? expression) (Constant expression)
    (symbol? expression) (Variable (str expression))
    (seq? expression) (apply (get OPERATIONS (first expression)) (map parseObject (rest expression)))
    (string? expression) (parseObject (read-string expression))))





    (defn constant [value] (constantly ^double value))
(defn variable [name] #(get % name))
(defn abstract [operations] (fn [& operands] (fn [args] (apply operations (mapv #(% args) operands)))))

(def add (abstract +))
(def subtract (abstract -))
(def multiply (abstract *))
(def divide (abstract #(/ ^double %1 ^double %2)))
(def negate subtract)
(def log (abstract #(/ (Math/log (Math/abs ^double %2)) (Math/log (Math/abs ^double %1)))))
(def pow (abstract #(Math/pow %1 %2)))
(def operations {'+ add, '- subtract, '* multiply, '/ divide, 'negate negate, 'pow pow, 'log log})

(defn parseFunction [expr] (cond
                             (list? expr) (apply (operations (nth expr 0)) (mapv parseFunction (rest expr)))
                             (number? expr) (constant expr)
                             (symbol? expr) (variable (str expr))
                             :else (parseFunction (read-string expr))))
 */