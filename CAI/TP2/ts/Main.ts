import N_INSEE from './N_INSEE.js';

declare const Swal: any;

window.addEventListener("DOMContentLoaded", function () { // DOM just loaded...
    Swal.mixin({
        input: 'text',
        confirmButtonText: 'Next &rarr;',
        showCancelButton: true,
        progressSteps: ['1', '2']
    }).queue([
        {
            title: 'N°INSEE',
            text: '(type key next time)'
        },
        'Key'
    ]).then((result) => {
        if (result.value) {
            window.console.assert(result.value instanceof Array, "'result.value instanceof Array', untrue?");
            window.console.assert(result.value.length === 2, "'result.value.length === 2', untrue?");
            const n_INSEE = new N_INSEE(Number.parseInt(result.value[0]), Number.parseInt(result.value[1]));
            Swal.fire({
                title: 'Result',
                html: `${result.value[0]} (key: ${result.value[1]}):&nbsp;<pre><code>${n_INSEE.result}</code></pre>`,
                confirmButtonText: 'Bye...'
            })
        }
    })
});



