document.cookie = 'XDEBUG_SESSION=VSCODE';

function abre_nova_janela() {
    const oRotina = document.getElementById('rotina');
    loadAjax({
        rotina: oRotina.attributes['rotina'].value,
        acao: oRotina.attributes['acao'].value,
        completo: function(res) {
            if (res.tipo == 2) {
                montaManutencao(res.campos);
            }
        }
    });
}

function montaConsulta(dados) {
    const consulta = document.getElementById('consulta');
}

const montaManutencao = function(campos) {
    const janela = document.getElementById('janela');
    const content = janela.getElementsByClassName('content')[0];
    let html = '<table>'
    campos.forEach(function(campo) {
        let input = '';
        switch (campo.tipo) {
            case 'text':
                input = `<input name="${campo.nome}" type="text">`;
        }
        html += `<tr><td>${campo.titulo}:</td><td>${input}</td></tr>`
    });
    html += '</table>'
    content.innerHTML = html;
};

const confirma_submit = function() {
    const oRotina = document.getElementById('rotina');
    const values = {};
    document.getElementById('janela').getElementsByClassName('content')[0].querySelectorAll('*').forEach(function(el) {
        if (el.tagName == 'INPUT') {
//            values.push({[el.name]: el.value});
            values[el.name] = el.value;
        }
    });
    
    loadAjax({
        rotina: oRotina.attributes['rotina'].value,
        acao: oRotina.attributes['acao'].value,
        processo: 'processaDados',
        parametro: {dados: values},
        completo: function() {
            
        }
    });
};

const janela = document.getElementById('janela');
let isDragging = false;
let offSetX;
let offSetY;

janela.addEventListener('mousedown', (e) => {
    if (e.target.tagName === 'HEADER') {
        isDragging = true;
        offsetX = e.clientX - janela.offsetLeft;
        offsetY = e.clientY - janela.offsetTop;
    }
});

document.addEventListener('mousemove', (e) => {
    if (isDragging) {
        janela.style.left = `${e.clientX - offsetX}px`;
        janela.style.top = `${e.clientY - offsetY}px`;
    }
});

document.addEventListener('mouseup', () => {
    isDragging = false;
});

loadAjax = function(options) {
    const formData = new URLSearchParams();
    options.parametro = {rotina: options.rotina, acao: options.acao, ...options.parametro};
    formData.append('rotina', options.rotina);
    formData.append('acao', options.acao);
    formData.append('processo', options.processo);
    formData.append('parametro', JSON.stringify(options.parametro));
    formData.append('chave', options.chave);
    const busca = fetch('api/call_controller.php', {
        method: options.method || 'POST',
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded'
        },
        body: formData
    });
    busca.then(response => {
        if (!response.ok) {
            options.exception && options.exception.call();
        }
        return response.json();
    })
    .then(function(response) {
        options.completo && options.completo.call(null, response);
    });
}