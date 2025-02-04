var Result;
(function (Result) {
    Result["Format"] = "Format invalid";
    Result["Key"] = "Key invalid";
    Result["Ok"] = "Ok";
})(Result || (Result = {}));
class N_INSEE {
    get result() {
        return this._result;
    }
    constructor(_n_insee, _clef) {
        this._n_insee = _n_insee;
        this._clef = _clef;
        // 'this._n_insee' is automatically inserted as private field
        // 'this._clef' is automatically inserted as private field
        if (this._n_insee.toString().match(N_INSEE._Format)) {
            if (this._calcul_clef())
                this._result = Result.Ok;
            else
                this._result = Result.Key;
        }
        else
            this._result = Result.Format;
    }
    _calcul_clef() {
        if ((97 - (this._n_insee % 97)) === this._clef)
            return true;
        else
            return false;
    }
}
N_INSEE._Format = new RegExp("^(?!000)(\\d{13}$)");
export default N_INSEE;
