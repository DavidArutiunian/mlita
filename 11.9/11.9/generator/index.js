const fs = require('fs');
const { grahamScan2: ch } = require('@thi.ng/geom-hull');
const first = require('lodash.first');
const last = require('lodash.last');

const ENDL = '\n';
const SPACE = ' ';
const MAX_N = Math.pow(10, 5);
const MAX_M = Math.pow(10, 4);
const N = rand(MAX_N);

const input = fs.createWriteStream("../input.txt");
const correct = fs.createWriteStream("../correct.txt");

let [add, finish] = output();
let points = [];

add(N.toString());
add(ENDL);

for (let i = 0; i < N; ++i) {
    const point = [rand(MAX_M), rand(MAX_M)];
    points.push(point);
}

for (let i = 0; i < N; ++i) {
    const point = points[i];
    add(first(point));
    add(SPACE);
    add(last(point));
    add(ENDL);
}

input.write(finish());

points = ch(points);
[add, finish] = output();

add(points.length.toString());
add(ENDL);

for (const point of points) {
    add(first(point));
    add(SPACE);
    add(last(point));
    add(ENDL);
}

correct.write(finish());

function rand(max) {
    return Math.floor(Math.random() * max);
}

function output() {
    let string = '';
    return [
        (str) => (string += str),
        () => string
    ]
}
