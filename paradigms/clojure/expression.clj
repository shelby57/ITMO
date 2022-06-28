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

;------------------------OBJECT------------------------

(definterface Expression
  (evaluate [args])
  (toString [])
  (diff [args]))

(defn evaluate [expr args] (.evaluate expr args))
(defn toString [expr] (.toString expr))
(defn diff [expr args] (.diff expr args))

(deftype Operation [operation symbol difference arg]
  Expression
  (evaluate [this args] (apply operation (mapv #(evaluate % args) arg)))
  (diff [this args] (difference args))
  Object
  (toString [this] (str "(" symbol " " (clojure.string/join " " (mapv toString arg)) ")")))

(defn Add [left right] (Operation.
                         +
                         '+
                         #(Add (diff left %)
                               (diff right %))
                         [left right]))
(defn Subtract [left right] (Operation.
                              -
                              '-
                              #(Subtract (diff left %) (diff right %))
                              [left right]))

(defn Multiply [left right] (Operation.
                              *
                              '*
                              #(Add (Multiply (diff left %) right) (Multiply left (diff right %)))
                              [left right]))
(defn Divide [left right] (Operation.
                            #(/ ^double %1 %2)
                            '/
                            #(Divide (Subtract (Multiply (diff left %) right)
                                               (Multiply (diff right %) left)) (Multiply right right))
                            [left right]))
(defn Negate [value] (Operation.
                       #(- %)
                       'negate
                       #(Negate (diff value %))
                       [value]))
(deftype Const [x]
  Expression
  (evaluate [this args] x)
  (diff [this args] (Const. 0))
  Object
  (toString [this] (str x)))

(defn Log [left right] (Operation.
                         #(/ (Math/log (Math/abs ^double %2)) (Math/log (Math/abs ^double %1)))
                         'log
                         #(Divide (Subtract (Multiply (Divide (diff right %) right) (Log (Const. Math/E) left))
                                            (Multiply (Divide (diff left %) left) (Log (Const. Math/E) right)))
                                  (Multiply (Log (Const. Math/E) left) (Log (Const. Math/E) left)))
                         [left right]))
(defn Pow [left right] (Operation.
                         #(Math/pow %1 %2)
                         'pow
                         #(Multiply (Pow left right) (Add (Multiply (diff right %) (Log (Const. Math/E) left))
                                                          (Multiply (Divide (diff left %) left) right)))
                         [left right]))
(deftype Var [x]
  Expression
  (evaluate [this args] (get args x))
  (diff [this args] (cond (= args x)
                          (Const. 1)
                          :else (Const. 0)))
  Object
  (toString [this] x))

(defn Variable [x] (Var. x))
(defn Constant [x] (Const. x))

(def OP {
         '+      Add,
         '-      Subtract,
         '*      Multiply,
         '/      Divide,
         'negate Negate
         'log    Log
         'pow    Pow
         })

(defn parseObject [expr]
  (cond
    (number? expr) (Constant expr)
    (symbol? expr) (Variable (str expr))
    (list? expr) (apply (get OP (nth expr 0)) (mapv parseObject (rest expr)))
    :else (parseObject (read-string expr))))

