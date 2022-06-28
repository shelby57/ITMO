(defn abstract [f] (fn [a b] (cond
                                (and (vector? a) (vector? b)) (mapv (abstract f) a b)
                                :else (f a b))))
(def v+ (abstract +))
(def v- (abstract -))
(def v* (abstract *))
(def vd (abstract /))


(def s+ (abstract +))
(def s- (abstract -))
(def s* (abstract *))
(def sd (abstract /))

(def m+ (abstract v+))
(def m- (abstract v-))
(def m* (abstract v*))
(def md (abstract vd))

(defn v*s [a b] (mapv (fn [n] (* b n)) a))
(defn scalar [& a] (apply + (apply v* a)))
(defn m*v [a b] (mapv (fn [n] (scalar n b)) a))
(defn m*s [a b] (mapv (fn [n] (v*s n b)) a))
(defn transpose [a] (apply mapv vector a))
(defn m*m [a b] (mapv (fn [n] (mapv (fn [m] (scalar n m)) (transpose b))) a))
(defn vect [a b] (let [[a1 a2 a3] a [b1 b2 b3] b]
                   [(- (* a2 b3) (* a3 b2))
                    (- (* a3 b1) (* a1 b3))
                    (- (* a1 b2) (* a2 b1))]))