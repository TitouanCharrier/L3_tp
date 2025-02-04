export default class Lotto {
    static readonly MAXIMUM = 48;
    private readonly _result: Array<number> = new Array(Lotto.MAXIMUM);

    public result(): string {
        return this._result.join('\t');
    }

    public draw() {
        for (let i = 0; i < Lotto.MAXIMUM; i++)
            this._result[i] = this._draw_internal(i);
    }

    private _draw_internal(i: number) {
        let result = 1 + Math.floor(Math.random() * Lotto.MAXIMUM + 1); // [1 - 49]
        let already_drawn = false;
        for (let j = 0; j < i; j++) {
            if (result === this._result[j]) {
                // console.warn("Malheureusement déjà tiré... " + result);
                already_drawn = true;
                break;
            }
        }
        if (already_drawn)
            return this._draw_internal(i);
        return result;
    }
}
