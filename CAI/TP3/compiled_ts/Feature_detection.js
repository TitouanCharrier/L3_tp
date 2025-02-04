/*
 * Feature_detection.js
 */
'use strict';
window.addEventListener('DOMContentLoaded', main);
function main(event) {
    chai.assert.isTrue(event instanceof Event, 'event instanceof Event');
    let Franck = new Image();
    Franck.onload = function () {
        new Character(Franck, "img/Franck.jpg");
    };
    Franck.src = "img/Franck.jpg";
    let Joseph = new Image();
    Joseph.onload = function () {
        new Character(Joseph, "img/Joseph.jpg");
    };
    Joseph.src = "img/Joseph.jpg";
    let Lena = new Image();
    Lena.onload = function () {
        new Character(Lena, "img/Lena.jpg");
    };
    Lena.src = "img/Lena.jpg";
    let Oscar = new Image();
    Oscar.onload = () => {
        new Character(Oscar, "img/Oscar.jpg");
    };
    Oscar.src = "img/Oscar.jpg";
    let Macron = new Image();
    Macron.onload = function () {
        new Character(Macron, "img/Macron.jpeg");
    };
    Macron.src = "img/Macron.jpeg";
    let Philippe = new Image();
    Philippe.onload = function () {
        new Character(Philippe, "img/Philippe.jpg");
    };
    Philippe.src = "img/Philippe.jpg";
    let Bayrou = new Image();
    Bayrou.onload = function () {
        new Character(Bayrou, "img/Bayrou.jpg");
    };
    Bayrou.src = "img/Bayrou.jpg";
    let LePen = new Image();
    LePen.onload = function () {
        new Character(LePen, "img/LePen.jpg");
    };
    LePen.src = "img/LePen.jpg";
    let Melanchon = new Image();
    Melanchon.onload = function () {
        new Character(Melanchon, "img/Melanchon.jpg");
    };
    Melanchon.src = "img/Melanchon.jpg";
}
;
