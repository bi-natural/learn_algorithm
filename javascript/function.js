
console.log("Helo, javascript<p>");

var add = function sum(x, y) {
    return x+y;
};

console.log(add(3, 4));
// console.log(sum(3, 4));  --> error

var factorialVar = function factorial(n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n-1);
};

console.log(factorialVar(6));
console.log('<br>')
