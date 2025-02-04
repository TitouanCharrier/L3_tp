import * as CRYPTOGRAPHY from "node:crypto";

export default class Lotto_ {
    private readonly _balls: Set<number> = new Set([
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
        21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
        31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
        41, 42, 43, 44, 45, 46, 47, 48, 49
    ]);
    // Alternative (array of "words", each word is 16-bit long)...
    // Note : le '500' est "quasi-robuste" pour obtenir 48 valeurs après le calcul '% 48' (<=> '% (this._balls.size - 1)') :
    private _balls_: Uint16Array = CRYPTOGRAPHY.getRandomValues(new Uint16Array(500)); // 500 valeurs tirées au hasard dans [0 - 65535]

    private _result: string = "";
    get result(): string {
        return this._result;
    }

    draw() {
        while (this._balls.size > 1) {
            const cursor = 1 + Math.floor(Math.random() * this._balls.size); // [1 - 49]
            let i = 1;
            for (const ball of this._balls) {
                if (i === cursor) {
                    this._balls.delete(ball);
                    this._result += '\t' + ball.toString();
                    break;
                }
                i++;
            }
        }
    }

    draw_() {
        this._balls_ = this._balls_
            // On ramène à [1 - 48] :
            .map(value => value % (this._balls.size - 1) + 1)
            // On enlève les doublons :
            .filter((value, index, array) => array.indexOf(value) === index);
        // On espère que '500' était au départ suffisant pour qu'il en reste 48 au final :
        console.assert(this._balls_.length === (this._balls.size - 1)); // Il en faut '48' !
        this._result = this._balls_.reduce((result, value) => { // Calcul de l'affichage...
            return result += '\t' + value.toString();
        }, this._result);
    }
}
